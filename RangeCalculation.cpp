//
//  RangeCalculation.cpp
//  MinCostFlow_Milk
//
//  Created by Peter A. Kolski on 13.08.11.
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

/*
                        To Do
                        Pete Man

 - Range Array an Größe der types anpassen
 - Abbruchbedingung anpassen an schnellere Laufzeit
 - Einlesen der KnotenArten (E, M, D)
 - Erzeugen von einem Gesamt-Graphen (E, M, D)
 - Zwei Zähler für die Ranges abhängig von der Knotenart
 - Loop um alle Knoten einmal zu infizieren
 - Herausschreiben der Ranges (Array und Datei)
 
 Optimierung:
 - CheckArcs: Muss die Abfrage sein, ob eine Arc an ist?
    -> Adaptor kann den Arc einfach löschen, dann brauche ich keine Abfrage
    -> Die Simulation muss dann über einen anderen Adapter laufen
 
 
 
 
 */


int main(){

    ListDigraph MyGraph;
    
    ListDigraph::NodeMap< long long int >   idNodeMap ( MyGraph );
    ListDigraph::NodeMap< double >          xKoordNodeMap (MyGraph );
    ListDigraph::NodeMap< double >          yKoordNodeMap (MyGraph );
    ListDigraph::NodeMap< long double >     capacityNodeMap( MyGraph );
    ListDigraph::NodeMap< bool >            typeNodeMap( MyGraph );    
    ListDigraph::ArcMap< long double >      distanceArcMap( MyGraph );
        
    ListDigraph::ArcMap < bool >            switchArcMap( MyGraph, true );  // Alle Kanten sollen an / true sein
    ListDigraph::ArcMap < bool >            stateArcMap(  MyGraph, false ); // Keine Infraktion (false) am Anfang
    ListDigraph::NodeMap< bool >            stateNodeMap( MyGraph, false );
    
    try {
        digraphReader( MyGraph, "/Users/sonneundasche/Desktop/MilkyWayDaten/MilkyWay_Solution.lgf")
        .nodeMap( "Type", typeNodeMap )
        .run();
    } catch (Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
        return -1;
    }    
    
    //  -------------------------------------------------------------------
    //  ----------------  Erzeuge die Glättungs Kanten    -----------------
    //  -------------------------------------------------------------------    
    
    // Zur Abspeicherung der IDs der Glättungs Arcs
    //    int glattArcID[ glattArcNr ];    
    //    int m = 0;
    //    
    //    for ( int in = 0; in < supplyNodesNr; in++ ) 
    //        for ( int out = 0; out < supplyNodesNr ; out++ ) {
    //            glattArcID[ m ] = MyGraph.id( MyGraph.addArc( MyGraph.nodeFromId( in ), MyGraph.nodeFromId( out ) ));
    //            m++;
    //            
    //            //vice versa "in/out"
    //            glattArcID[ m ] = MyGraph.id( MyGraph.addArc( MyGraph.nodeFromId( out ), MyGraph.nodeFromId( in ) )); 
    //            m++;
    //        }
    
    //  -------------------------------------------------------------------
    //  ----------------  Erzeuge eine FilterMap und Init -----------------
    //  -------------------------------------------------------------------    
    //  ----------------  um Glättung umzuschalten   ----------------------
    //  -------------------------------------------------------------------
    
    
    //    FilterArcs< ListDigraph >::ArcFilterMap   glattArcFilterMap( MyGraph  );
    //    FilterArcs< ListDigraph >::FilterArcs     glattFilterGraph( MyGraph, glattArcFilterMap  );
    //
    //        // Alle auf TRUE setzen
    //    for ( FilterArcs< ListDigraph >::ArcIt a( glattFilterGraph ) ; a != INVALID ; ++a )
    //        glattArcFilterMap[ a ] = 1;
    //        
    //        // Glättungskanten auf FALSE setzen
    //    for ( int i = 0; i < glattArcNr; i++ ) 
    //        glattArcFilterMap[ glattFilterGraph.arcFromId( glattArcID[ i ] ) ] = 0;
    //
    
    
    
    //  -------------------------------------------------------------------
    //  ----------------  Zufalls Glättungskanten umschalten  -------------
    //  -------------------------------------------------------------------    
    
    
    
    
    
    
    
    //  -------------------------------------------------------------------
    //  ----------------  Infectious Dynamics Calculation (Range) ----------
    //  -------------------------------------------------------------------    
    // +++++ Hier sollte noch ein SubGraph / FilterMap erstellt werden für die Glättung
    // ++++  Gesamtschleife mit Abbruch kommt noch
    

    
    int infStartAmount = 1;                 // Anzahl der Molkerei-Knoten die am Anfang infiziert sind
    int infSumInfected = infStartAmount;    // StartRange: Anzahl infizierten Knoten + Anfangswert
//    int ctrlRange[ ];                      // Range die über die Out Arcs gezählt wird
    int ctrlRangeALL = 0;
    
    int infSumArry[ 3 ];                    // AbbruchBed.: Falls nach drei Rechen-Schritten "Range" gleich, dann brich ab.
    infSumArry[ 0 ] =  infStartAmount;      // Zwangsbed., damit der Loop anfängt
    
    
    //  ----------------  Zufällig eine Molkerei/Node infizieren  -------------    
    
//    for ( int i = 0; i < infStartAmount; i++)
//        stateNodeMap[ MyGraph.nodeFromId( rnd( 0, ( supplyNodesNr - 1 ) ) ) ] = 1;
    
    //    for ( int i = 0; i < sumSup; i++)
    //        stateNodeMap[ MyGraph.nodeFromId( i ) ] = 1;
    
    
    //  -------------------------------------------------------------------   
    //  -----------------  Durchlauf durch den Graphen     ----------------
    //  -------------------------------------------------------------------   
    //  ++++  Man kann entweder zuerst Nodes oder Arcs durchschauen
    //  ++++  Falls Arcs zuerst gezählt werden, breitet sich die Krankheit in weniger
    //  ++++    Rechenschritten aus, da in anschließenden Schritt infizierte Kanten Knoten infinzieren.
    //  ++++  Dieser Weg wird hier aus Performance-Gründen gegangen. Uns interessiert nicht die Ausbreitungsgeschw.
    
    do {
        //  ----------------  Arc Infectious States ----------------    
        
        for ( ListDigraph::ArcIt a( MyGraph ) ; a != INVALID; ++a ) {
//            if ( stateArcMap[ a ] == 0 )  //Falls noch nicht infiziert
                if ( stateNodeMap[ MyGraph.source( a ) ] == 1 )     // Falls der QuellKnoten Infiziert, Kante auch
                    stateArcMap[ a ] = 1;
        }
        
        //  ----------------  Node Infectious States ----------------    
        
        for ( ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n ) {
            if ( stateNodeMap[ n ] == 0 )       // Optimierung: Nur abfragen falls es noch nicht infiziert ist
                for (ListDigraph::InArcIt in( MyGraph, n ) ; in != INVALID; ++in )
                    if ( stateArcMap[ in ] ) {
                        stateNodeMap[ n ] = 1;
                        infSumInfected++;   // Zähle die Neuinfektion falls Knoten an ist
                        continue;           // Schleife verlassen, falls eine Kante an ist
                    }
        }
        
        // Billiges Aufschieben der Werte. Damit man schauen kann, ob dreimal nichts geschah
        infSumArry[ 2 ] = infSumArry [ 1 ];
        infSumArry[ 1 ] = infSumArry [ 0 ];
        infSumArry[ 0 ] = infSumInfected;
        
    }    while ( ( infSumArry[ 0 ] != infSumArry[ 1 ] ) || ( infSumArry[ 1 ] != infSumArry [ 2 ] ) );
 
    
    //  -------------------------------------------------------------------   
    //  -----------------  Test Funktion zur Überprüfung der Werte  ----------------
    //  -------------------------------------------------------------------  
    //  +++ Einfache Berechnung des AUS-Grades
    
    // GesamtRange
    for ( ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n)
        for ( ListDigraph::OutArcIt o( MyGraph, n ) ; o != INVALID;  ++o ){
            ctrlRangeALL++;
            // ++++>> hier den Range Array einfügen
        }
    
    
    //  -----------------  Graph schreiben  ----------------
    
    digraphWriter( MyGraph, cout )
    .nodeMap( "NodeStates", stateNodeMap )
    .skipArcs()
    .run();
    
    cout << endl << "Range-Berechnungs-Zeit: " << time.realTime() << endl;  
    cout << endl << "Range-Wert: " << infSumInfected << endl;      

    return 0;

}