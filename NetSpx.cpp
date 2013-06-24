//
//  NetSpx.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 27.07.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>
#include <lemon/lgf_reader.h>
#include <lemon/random.h>
#include <lemon/time_measure.h>
#include <lemon/network_simplex.h>
#include "lemon/adaptors.h"

using namespace lemon;
using namespace std;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*
                TO DO 
                Lieber Peter
 
+   ich sollte mal schauen, wie es um um die ArcMaps steht, 
    die auf MyGraph definiert wurden, anstatt resultGraph (cost & capacityRestriction)

Optimierung:
 - Vielleicht brauche ich nicht überalle long long int in den Maps, sondern nur im Simplex...

 
 */

int main()
{

    //  ----------------------------------------------------------------
    //  Variablen
    //  ----------------------------------------------------------------
    Timer time;
    
    int supplyNodesNr = 0;
    int demandNodesNr = 0;
    
    int minArcNrDemand = 4;
    float capacityDegreeGaussDeviation = 0.3f;
    long double sumSup = 0.0 ;
    long double sumDem = 0.0 ;
//    int glattArcNr = 2 * supplyNodesNr * supplyNodesNr;
    float ratioSupDem;
    int maxDemID = 0;
    int maxSupID = 0;
    long maxDemValue = 0;
    long maxSupValue = 0;
    
    // Für die Kostenfunktion
    
    long double scaleDistToCap  = 15.0 ;    // Entspricht A Parameter
    long double scaleCostOffset = 0.0001 ;      // Entspricht B

    /// Verh. um bei anderen Zahlenwerten Zufallszahlen zu erzeugen, 
    /// welche immer die SupplyType EQUAL Bedingung erfüllen.
    
    Random();
    
    cout << "Start-Zeit: " << time.realTime() << endl;
    
    
    //  ----------------  Graphen & Maps erstellen   ----------------  
    
    ListDigraph MyGraph;
    
    ListDigraph::NodeMap< long long int >   idNodeMap ( MyGraph );
    ListDigraph::NodeMap< double >          xKoordNodeMap (MyGraph );
    ListDigraph::NodeMap< double >          yKoordNodeMap (MyGraph );
    ListDigraph::NodeMap< long double >     capacityNodeMap( MyGraph );
    ListDigraph::NodeMap< bool >            typeNodeMap( MyGraph );    
    
    ListDigraph::ArcMap< long double >      distanceArcMap( MyGraph );
    ListDigraph::ArcMap< long double >      costArcMap( MyGraph );
    ListDigraph::ArcMap< long double >      flowResultArcMap( MyGraph );
    ListDigraph::ArcMap< long double >      capacityRestrictionArcMap( MyGraph );
    
    ListDigraph::ArcMap< bool >             switchArcMap( MyGraph );
    
    

    //  ----------------  Knoten mit Daten einlesen   ----------------  
    
    try {
        digraphReader( MyGraph, "/Users/sonneundasche/Desktop/MilkyWayDaten/PetersDaten.csv")
        .nodeMap( "ID",     idNodeMap )
        .nodeMap( "x",      xKoordNodeMap )        
        .nodeMap( "y",      yKoordNodeMap )
        .nodeMap( "cap",    capacityNodeMap )
        .nodeMap( "type",   typeNodeMap )
        .skipArcs()
        .run();
    } catch (Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
        return -1;
    }
    
    
    //  ----------------  Demand zu negativen Suppies umschalten   ----------------      
    
    for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
        if ( typeNodeMap[ n ] == 1 ) {
            sumDem += capacityNodeMap[ n ];
            capacityNodeMap[ n ] = (-1) *  capacityNodeMap [ n ]; // neg damit es demand ist
            demandNodesNr++;
            
            // Suche der größten Demand Knoten
            // Kleiner, weil Demand negativ ist!!!
            if ( capacityNodeMap[ n ] < maxDemValue  ) {
                maxDemValue = capacityNodeMap[ n ];
                maxDemID = MyGraph.id( n );
            }
            
        }
        else    {
            sumSup += capacityNodeMap[ n ];
            supplyNodesNr ++;
            
            // Suche der größten Supply Knoten
            if ( capacityNodeMap[ n ] > maxSupValue ) {
                maxSupValue = capacityNodeMap[ n ];
                maxSupID = MyGraph.id( n );
            }
        }
    }
  

    //  ----------------  Demand & Supply auf NULL skalieren   ----------------      

    if ( sumSup > sumDem) {
        long double diff = 0;
        ratioSupDem = (float)sumSup / (float)sumDem;  
        
        cout << "Supply größer als Demand " << endl << "D: " << sumDem << endl << " S: " << sumSup <<  endl;
        cout << "Verhältnis Supply/Demand VOR Skalierung: " << ratioSupDem << endl;
    
        //Skaliere den Demand um
        for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
            if ( typeNodeMap[ n ] == 1 )      // 1 für Demand
                capacityNodeMap[ n ] = floor( capacityNodeMap[ n ] * abs(ratioSupDem) );
        }
        
        //Nochmal zählen - sicherheitshalber
        sumDem = 0;
        for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
            if ( typeNodeMap[ n ] == 1 )
                sumDem += capacityNodeMap[ n ];
        }
        
        diff = abs(sumDem) - abs(sumSup);
        
        cout << "D: " <<  sumDem << endl << " S: " << sumSup << endl << "Diff D-S : " << diff <<  endl;
        
        // +++ Lösche den Überschuss vom größten SUPPLY-Knoten
        capacityNodeMap[ MyGraph.nodeFromId( maxSupID ) ] +=  (int)diff;
    }
    
    
    if ( sumDem > sumSup){
        long double diff = 0.0;
        ratioSupDem = (float)sumDem / (float)sumSup;
        
        cout << "Demand größer als Supply " << endl << "D: " << endl << sumDem << endl << " S: " << sumSup <<  endl;        
        cout << "Verhältnis Demand/Supply VOR Skalierung: " << ratioSupDem << endl;

        //Skaliere den Supply um
        for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
            if ( typeNodeMap[ n ] == 0 )      // 0 für Supply
                capacityNodeMap[ n ] = floor( capacityNodeMap[ n ] * abs(ratioSupDem) );
        }
        
        //Nochmal zählen - sicherheitshalber
        sumSup = 0;
        for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
            if ( typeNodeMap[ n ] == 0 )
                sumSup += capacityNodeMap[ n ];
        }
        
        diff = abs(sumSup) - abs(sumDem);
        
        cout << "D: " <<  sumDem << endl << " S: " << sumSup << endl << "Diff D-S : " << diff <<  endl;
        
        // +++ Lösche den Überschuss vom größten DEMAND-Knoten
        capacityNodeMap[ MyGraph.nodeFromId( maxDemID ) ] -=  (int)diff;
        
        
    // Skaliere den Supply um
    // Lösche den Überschuss vom größten DEMAND-Knoten
    }
    
    
    // ------------ Zähle nochmal um den Wert zu überprüfen  ------------ 
    sumDem = 0;
    sumSup = 0;
    for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) {
        if ( typeNodeMap[ n ] == 1 ) 
                sumDem += capacityNodeMap[ n ];
        else    sumSup += capacityNodeMap[ n ];
    }
        
    ratioSupDem = (float)sumSup / (float)sumDem;  
    cout << "Verhältnis Supply/Demand NACH der Skalierung: " << ratioSupDem << endl;
    cout << "D: " << sumDem << endl << " S: " << sumSup <<  endl << endl;  
    
 
    //  ----------------------------------------------------------------
    //  ----------------   Kanten erstellen    ---------------- 
    //  ----------------------------------------------------------------
    //  -- Dafür da, damit ich nach der Optimierung vom frischen Graphen die
    //  -- Kanten abschneiden kann. Die Optimierung schneidet umgekehrt Kanten ab


    for (ListDigraph::NodeIt supplyNode( MyGraph ) ; supplyNode != INVALID; ++supplyNode) {
        if ( typeNodeMap[ supplyNode ] == 0 ) // Supply Node
        {
            for (ListDigraph::NodeIt demandNode( MyGraph ) ; demandNode != INVALID; ++demandNode) {
                if ( typeNodeMap[ demandNode ] == 1 )
                MyGraph.addArc( supplyNode , demandNode );
            }
        }
    }
    

    //  ----------------------------------------------------------------    
    //  ----------------  ArcMap - Distances   ----------------
    //  ----------------------------------------------------------------        
    
    for (ListDigraph::ArcIt a( MyGraph ) ; a != INVALID; ++a) 
    {
        long double x1, x2, y1, y2;
        
        x1 = xKoordNodeMap[ MyGraph.source( a ) ];      // X !  Quelle
        y1 = yKoordNodeMap[ MyGraph.source( a ) ];      // Y !  Quelle  
        x2 = xKoordNodeMap[ MyGraph.target( a ) ];      // Ziel
        y2 = yKoordNodeMap[ MyGraph.target( a ) ];        
        
        distanceArcMap[ a ] = sqrt( ( x1 - x2 )*( x1 - x2 ) + ( y1 - y2 )*( y1 - y2 ) );
    }
   
    //  ----------------------------------------------------------------    
    //  ----------------  ArcMap - Cost Values   ----------------
    //  ----------------------------------------------------------------    
    
    for (ListDigraph::ArcIt a( MyGraph ) ; a != INVALID; ++a) 
    {
        long double d = distanceArcMap[a];
        long double c = capacityNodeMap[ MyGraph.source(a) ];
        long double A = scaleDistToCap;
        long double B = scaleCostOffset;
        
        costArcMap[a] = A * ( d / c ) + B * c;
    }

    //  ----------------------------------------------------------------
    //  ----------------  UpperMap   ----------------     
    //  ----------------------------------------------------------------
    //  +++ Teile den Möglichen Zufluss in die Menge, dass mehrere Kanten zu einem Discounter gezogen werden müssen

    for (ListDigraph::ArcIt a( MyGraph ) ; a != INVALID; ++a) {
        capacityRestrictionArcMap[ a ] = (long double)rnd.gauss( 1, capacityDegreeGaussDeviation ) * abs( capacityNodeMap[ MyGraph.target( a ) ] / ( long double )minArcNrDemand );
    }
    
    //  ----------------------------------------------------------------
    //  ----------------  Ausgabe auf Console   ----------------     
    //  ----------------------------------------------------------------
    
    
    cout << endl;
    cout << "Nodes: " << countNodes( MyGraph ) << endl;
    cout << "Arcs: " << countArcs( MyGraph ) << endl;
    cout << "Supply Nodes: " << supplyNodesNr << endl;
    cout << "Demand Nodes: " << demandNodesNr << endl;

    cout << endl;
    cout << "Summe der Supplies: " << sumSup << endl;
    cout << "Summe der Demands: " << sumDem << endl;
    cout << "Verhältnis: " << ratioSupDem << endl;
    cout << "Differenz (Überschuss) Sup-Dem: " << abs(sumSup) - abs(sumDem) << endl;
    cout << "Maximaler Supply | ID: " << maxSupID << " Value: " << maxSupValue << endl;
    cout << "Maximaler Demand | ID: " << maxDemID << " Value: " << maxDemValue << endl;    
    
    cout << endl;
    cout << "Knoten: "   << countNodes(MyGraph) << endl;
    cout << "Kanten VOR dem Simplex: " << countArcs( MyGraph ) << endl;
    cout << endl << "Zeit vor dem Simplex: " << time.realTime() << endl;

    digraphWriter( MyGraph, cout )
    .skipNodes()
    .nodeMap( "ID", idNodeMap )
    .nodeMap( "X", xKoordNodeMap )        
    .nodeMap( "Y", yKoordNodeMap )
    .nodeMap( "Capacity", capacityNodeMap )
    .nodeMap( "Type", typeNodeMap )
    .skipArcs()
    .arcMap( "Cost", costArcMap )
    .arcMap( "Distance", distanceArcMap )
    .run();
    
    //  ----------------------------------------------------------------
    //  ----------------  Network Simplex   ----------------
    //  ----------------------------------------------------------------
    
    NetworkSimplex< ListDigraph, long double, long double >  NetSpx( MyGraph );         // Create NetSplx System Class Instance
    
    //  Assign maps to problem values und solve it
    NetSpx.costMap( costArcMap ).supplyMap( capacityNodeMap ).upperMap( capacityRestrictionArcMap ).run();                                    
    NetSpx.flowMap( flowResultArcMap );
    cout << "Kosten Lösung " << ": "   << NetSpx.totalCost() << "  ||  ";
    
    //  ----------------  Kanten ohne Flow löschen  ----------------
    
    for (ListDigraph::ArcIt a( MyGraph )  ; a != INVALID ; ++a )
        if ( flowResultArcMap[a] == 0) MyGraph.erase(a);

    
    //  ----------------------------------------------------------------
    //  ----------------  Ausgabe in Datei   ----------------     
    //  ----------------------------------------------------------------
    
    cout << " Kanten nach dem Simplex: " << countArcs( MyGraph ) << endl;
    
    cout << endl << "Lösungs-Zeitpunkt: " << time.realTime() << endl;    
    
    // Ausgabe auf die Console, damit man alles überprüfen kann.
    digraphWriter( MyGraph, cout )
    .skipNodes()
    .nodeMap( "ID", idNodeMap )
    .nodeMap( "X", xKoordNodeMap )        
    .nodeMap( "Y", yKoordNodeMap )
    .nodeMap( "Capacity", capacityNodeMap )
    .nodeMap( "Type", typeNodeMap )
    .skipArcs()
    .arcMap( "Cost", costArcMap )
    .arcMap( "Distance", distanceArcMap )
    .arcMap( "Flow", flowResultArcMap )
    .run();
    
    //  ----------------  Den LEMON Label der Nodes in die BNR/ID umwandeln   ----------------   
    
    ofstream fileLFG, fileResult;
    stringstream fileEdgeList( stringstream::in | stringstream::out );  // Stream kann gelesen UND geschrieben werden
    
    fileLFG.open( "/Users/sonneundasche/Desktop/MilkyWay_Solution.lgf" );
    digraphWriter(MyGraph, fileLFG)
    .attribute( "Mean Nr of arcs", minArcNrDemand )
    .attribute( "Gaussian derivation of arc capacity", capacityDegreeGaussDeviation )
    .attribute( "CostScale Distance", scaleDistToCap )
    .attribute( "CostScale Offset", scaleCostOffset )
    .nodeMap( "ID", idNodeMap )
    .nodeMap( "X", xKoordNodeMap )        
    .nodeMap( "Y", yKoordNodeMap )
    .nodeMap( "Capacity", capacityNodeMap )
    .nodeMap( "Type", typeNodeMap )
    .arcMap( "Cost", costArcMap )
    .arcMap( "Distance", distanceArcMap )
    .arcMap( "Arc Capacity", capacityRestrictionArcMap )
    .arcMap( "Flow", flowResultArcMap )
    .run();
    fileLFG.close();
    
    fileResult.open( "/Users/sonneundasche/Desktop/MilkyWay_Solution_NEW.txt" );
    digraphWriter( MyGraph, fileEdgeList).skipNodes().run();   
    int labelNode1, labelNode2, labelEdgeUseless;
    
    // Skip first two lines
    char buffer[ 256 ];
    fileEdgeList.getline( buffer , 256 );
    fileEdgeList.getline( buffer , 256 );
    
    // Die Daten aus dem Stream (labeNode1/2) werden automatisch ins richtige Format geschrieben
    // Bed.: Solange Infos fließen und kein Ende
    while ( fileEdgeList >> labelNode1 &&
            fileEdgeList >> labelNode2 &&
            fileEdgeList >> labelEdgeUseless &&
            !fileEdgeList.eof()) 
    {
        fileResult << idNodeMap[ MyGraph.nodeFromId( labelNode1 ) ] << "\t";    // BNR und Tab
        fileResult << idNodeMap[ MyGraph.nodeFromId( labelNode2 ) ] << "\n";    // BNR und NewLine
    }
    fileResult.close();
    
    cout << "BUM!";         // Das ist die ultimative Bestätigung, dass alles zur allgemeinen Zufriedenheit verlief
    
    return 0;
}

