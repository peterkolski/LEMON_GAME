//
//  GraphCreator_Test.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski on 13.07.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//
//-----------------------------------------------------------------------------



#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>
#include <lemon/random.h>
#include <lemon/Lp.h>

#include <lemon/time_measure.h>


using namespace lemon;
using namespace std;

void CreateNodeArc( ListDigraph* g, int NrA, int NrB);
void writeFile( ListDigraph *g);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


int main()
{
    
    //  Variablen
    ListDigraph MyGraph;
    Timer time;
    Lp  mLpSys;
    int NodesNrA = 10;
    int NodesNrB = 20;
    
    int sourceNode = 0;
    int drainNode;
    Random();
    
    cout << "Start-Zeit: " << time << endl;
    
    CreateNodeArc( &MyGraph, NodesNrA, NodesNrB );
    
    drainNode = countNodes( MyGraph ) + 1;

    
//  ----------------  ArcMap - Distance   ----------------
//  needed for the cost function
    
    ListDigraph::ArcMap<float> distanceArcMap( MyGraph );
    for (ListDigraph::ArcIt a( MyGraph )  ; a != INVALID ; ++a )
    {   
        distanceArcMap[a] = rnd(0.0, 5.0);
//        cout << "id: " << MyGraph.id( a ) << "  MapValue: " <<    distanceArcMap[a] << endl;
    }

    
//  ----------------  NodeMap - Capacity   ----------------
//  needed for the LinearContraints
    
    ListDigraph::NodeMap<float> capacityNodeMap( MyGraph );
    for (ListDigraph::NodeIt n( MyGraph ) ; n != INVALID; ++n) 
    {
        capacityNodeMap[n] = rnd(0.0, 100.0);
//        cout << "id: " << MyGraph.id( n ) << "  NodeValue: " <<    capacityNodeMap[n] << endl;        
    }


//  ----------------  LP: ArcMap Column   ----------------
//  Create Linear-Problem Variables
    
    ListDigraph::ArcMap<Lp::Col> flowColArcMap( MyGraph );
    mLpSys.addColSet( flowColArcMap );                       //Füge pro Kante eine Variable ein
    
    
//  ----------------  LP: Contraints / Randbed.   ----------------
/*  
    Für jeden Knoten sollen die Kanten behandelt werden. 
    Dabei gibt man den IN- & OUT-Kanten +/- Werte.
    Und sagt, dass die Capacity der Summe der Flüsse nicht 
    die RandBed überschreiten soll.
 */

    for (ListDigraph::NodeIt n( MyGraph ); n != INVALID;  ++n) {
        if ( n == MyGraph.nodeFromId( sourceNode ) || n == MyGraph.nodeFromId( drainNode ) ) continue;
        Lp::Expr zeilenFkt;
        // --- Flow out  ---
        for (ListDigraph::OutArcIt outA( MyGraph, n ); outA != INVALID; ++outA)    
            zeilenFkt -= flowColArcMap[outA];
        // --- Flow IN  ---
        for (ListDigraph::InArcIt inA( MyGraph, n ); inA != INVALID; ++inA)    
            zeilenFkt += flowColArcMap[inA];
        
        mLpSys.addRow( zeilenFkt <= capacityNodeMap[n] );       // Kapazität des Knotens als Randbed.
    }
    
    
//  ----------------  LP: Grenzen   ----------------    
    for (ListDigraph::ArcIt a( MyGraph ) ; a != INVALID; ++a) {
    mLpSys.colLowerBound( flowColArcMap[a], 0.0);
    }

    
//  ----------------  LP: Object Function / Kostenfkt   ----------------
    /*  
    
     
     */

    Lp::Expr kostenFkt;
    for (ListDigraph::ArcIt a( MyGraph ); a != INVALID; ++a)    {
        if ( MyGraph.source( a ) == MyGraph.nodeFromId( sourceNode ) || MyGraph.target( a ) == MyGraph.nodeFromId( drainNode ) ) continue;
            kostenFkt += distanceArcMap[a] * flowColArcMap[a];
    }
    mLpSys.min();
    mLpSys.obj( kostenFkt );
    

    
    
    cout << "Zeit nach KantenGeneration: " << time << endl;
    
    mLpSys.solve();
    
    cout << "Lösungs-Zeit: " << time << endl;    
    cout << "Kosten Lösung: "   << mLpSys.primal() << endl;
    cout << "nodes: "   << countNodes(MyGraph) << endl;
    cout << "arcs: "    << countArcs(MyGraph)  << endl;



    ofstream fileLGF;
    fileLGF.open( "/Users/sonneundasche/Desktop/PeterLEMON.lgf" );
    digraphWriter( MyGraph, fileLGF).
    arcMap(  "distance", distanceArcMap ).
//    arcMap( "flow",  flowColArcMap ).
    nodeMap( "capacity" , capacityNodeMap ).
    run();    
    fileLGF.close();
    
    //  Random
    /*
    Random();                           // Ohne Seed, also immer das selbe Ergebnis
    for ( int i = 0; i < 10;  ++i) 
    cout << "randomNr: "   << rnd() << endl; 
    cout << "integer: "<< rnd.integer() << endl; 
    cout << "boolean: "<< rnd.boolean() << endl; 
//  cout << seedFromTime() << endl; 
    */
    
    
    //  OutArcIt
    /*
    // --  Testen con OutArcIt 
    // --  Iterator über die Arcs an einem Knoten
    int count=0;
    for ( ListDigraph::OutArcIt a( MyGraph, MyGraph.nodeFromId( 5 ) ); a != INVALID; ++a) 
    {
//            cout << MyGraph.arcFromId(a) << endl;    
//            cout << MyGraph.runningNode(a) << endl;    
        ++count;
    }

    cout << "arcs at node 5: "  << endl;    
    cout << count << endl;    
     */
    

    return 0;
}


//-----------------------------------------------------------------------------



void CreateNodeArc( ListDigraph* g, int NrA, int NrB){

    //Adding the Nodes S & D.
    //Null wird zwar gezählt, aber for()-Abbruch benutzt '<'
    int NrNodes = NrA + NrB + 2;
    
    
    // Erstellung der Knoten
    for (int n = 0; n < NrNodes;  n++)   g->addNode();

    // Edges: S->A
    for (int a = 1; a < (NrA + 1); a++)  g->addArc( g->nodeFromId( 0 ), g->nodeFromId( a ) );
    
    // Edges: A->B
    for (int a = 1; a < (NrA + 1); a++)  
        for (int b = ( NrA + 1 ); b < ( NrNodes - 1 ); b++) 
            g->addArc( g->nodeFromId( a ), g->nodeFromId( b ) );

    // Edges: B->D
    for (int b = ( NrA + 1 ); b < ( NrNodes - 1 ); b++)  g->addArc( g->nodeFromId( b ), g->nodeFromId( NrNodes - 1 ) );
    
    
}



//void writeFile( ListDigraph *g){
//    ofstream fileLGF;
//    fileLGF.open( "PeterLEMON.lgf" );
//    digraphWriter( g, cout).
//    run();  
//    fileLGF.close();
//    
//}
