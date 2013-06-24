//
//  main.cpp
//  MinimalNetGet
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 01.02.12.
//  Copyright (c) 2012 Peter A. Kolski.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  For the GNU General Public License see <http://www.gnu.org/licenses/>.
//
//
//

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/full_graph.h>
#include <lemon/adaptors.h>
#include <lemon/maps.h>
#include <lemon/time_measure.h>

using namespace lemon;
using namespace std;

typedef FullDigraph::ArcIt fullArcIt;
typedef IterableBoolMap< FullDigraph, FullDigraph::Arc > IterMapArc;
typedef IterableBoolMap< FullDigraph, FullDigraph::Node > IterMapNode;

int main (int argc, const char * argv[])
{

    FullDigraph myFullGraph;
    FullDigraph::NodeMap< bool >    activeNodesMap  ( myFullGraph, true );
    FullDigraph::ArcMap<  bool >    activeArcMap    ( myFullGraph, true );
//    SubDigraph< FullDigraph >       myAdaptor( myFullGraph, activeNodesMap, activeArcMap );
    Timer t( false );    
    
    t.restart();
    myFullGraph.resize( 40000 );
    cout << "Graph generation time: " << t.realTime() << endl;
    t.restart();
//    IterMapArc     boolMap1 ( myFullGraph );
    IterMapNode     boolNodeMap ( myFullGraph );
    cout << "IterMap generation time: " << t.realTime() << endl;
    cout << "Nodes of FullGraph: " << myFullGraph.nodeNum() << endl;
    cout << "Arcs of FullGraph: " << myFullGraph.arcNum() << endl << endl;

//    myFullGraph.resize( 20000 );
//    t.restart();
//    IterMapArc     boolMap2 ( myFullGraph );
//    cout << "IterMap generation time: " << t.realTime() << endl;
//    cout << "Nodes of FullGraph: " << myFullGraph.nodeNum() << endl;
//    cout << "Arcs of FullGraph: " << myFullGraph.arcNum() << endl << endl;
//
//    myFullGraph.resize( 30000 );
//    t.restart();
//    IterMapArc     boolMap3 ( myFullGraph );
//    cout << "IterMap generation time: " << t.realTime() << endl;
//    cout << "Nodes of FullGraph: " << myFullGraph.nodeNum() << endl;
//    cout << "Arcs of FullGraph: " << myFullGraph.arcNum() << endl << endl;

    

    
//    cout << "Nodes of adaptor: " << countNodes( myAdaptor ) << endl;
//    cout << "Arcs  of adaptor: " << countArcs( myAdaptor ) << endl;
//    myAdaptor.enable( myFullGraph.nodeFromId( 1 ) );
//    myAdaptor.enable( myFullGraph.arcFromId(  2 ) );
//    myAdaptor.status( myFullGraph.arcFromId( 4 ), 1 );
//    myAdaptor.enable( myAdaptor.arcFromId(  0 ) );    // Here accessing the adapter
    
//    boolMap[ myFullGraph.arcFromId( 100 ) ] = true;
    
//    cout << "Nodes of adaptor: " << countNodes( myAdaptor ) << endl;
//   cout << "Arcs  of adaptor: " << countArcs(  myAdaptor ) << endl;

//    for (fullArcIt a (myFullGraph); a != INVALID; ++a) {
//        if (activeArcMap[ a ])
//            cout << myFullGraph.id( a ) << " Arc MapValue: " << activeArcMap[ a ] << " Status: " << myAdaptor.status( a ) << endl;
//    }
    
//    t.restart();
//    for (SubDigraph< FullDigraph >::ArcIt a( myAdaptor ); a != INVALID; ++a) {
//        cout << "activeArc: " << myAdaptor.id ( a ) << endl;
//    }
//    cout << "Time AdaptorIteration: " << t.realTime() << endl;
    
    t.restart();
    for (fullArcIt a( myFullGraph ); a != INVALID; ++a) {
    }
    cout << "Time FullGraphIteration: " << t.realTime() << endl;

//    for (IterMapArc::TrueIt a( boolMap ); a != INVALID; ++a) {
//        cout << "IterableMap active: " << boolMap[ a ]  << " | ID: " << myFullGraph.id( a ) << endl;
//    }
    
 
 
    cout << "Time: " << t.realTime() << endl;
    /*
        PROBLEM
     - no iteration of the active arcs
     - no cout of the active arcs
     - the iterableBoolMap takes a lot of memory
     
     It takes long to:
     - create of a IterableBoolMap
     - counting in an adaptor
     - iterating in a SubGraph -> so he still goes through all the arcs!!!!!
     
     */
    
}

