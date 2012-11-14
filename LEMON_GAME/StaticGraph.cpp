//
//  StaticGraph.cpp
//  LemonGame
//
//  Created by BildPeter Visuals on 09.11.11.
//  Copyright (c) 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/static_graph.h>

#include <lemon/lgf_reader.h>
#include <lemon/connectivity.h>
#include <lemon/euler.h>
#include <lemon/time_measure.h>
#include <lemon/concepts/maps.h>


using namespace lemon;
using namespace std;

int main( void ){
    
    ListDigraph     myGraph;
    StaticDigraph   myStaticGraph;
    
    ListDigraph::NodeMap< int >         readID          ( myGraph );
    ListDigraph::NodeMap< string >      euRegioTag      ( myGraph );
    ListDigraph::NodeMap< bool >        euRegioBool     ( myGraph );
    
    ListDigraph::ArcMap< int >          transpAmount    ( myGraph );
    ListDigraph::ArcMap< string >       egdeList        ( myGraph );
    
    lemon::concepts::ReferenceMap < ListDigraph, StaticDigraph, ListDigraph::Node, StaticDigraph::Node >    myRefNodeMap;
    lemon::concepts::ReferenceMap < ListDigraph, StaticDigraph, ListDigraph::Arc, StaticDigraph::Arc >      myRefArcMap;
//    ListDigraph::NodeMap< ListDigraph::Node >   
//    ListDigraph::ArcMap<  ListDigraph::Arc  >   myRefArcMap     ( myGraph );
    
    
    try {
        digraphReader( myGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/ZuverlegungEuregio_comlete.lgf")
        .nodeMap( "sourceID", readID)
        .nodeMap( "TypeName", euRegioTag )
        .nodeMap( "EUREGIO_BOOL", euRegioBool )
        .arcMap( "TransportAmount", transpAmount)
        .arcMap( "Edgelist", egdeList )
        .run();
    } catch (lemon::Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
    }
    
    myStaticGraph.build( myGraph, myRefNodeMap, myRefArcMap );
    
    
    
    cout << "Nodes: " << countNodes( myGraph ) << endl;
    cout << "countStronglyConnectedComponents: " << countStronglyConnectedComponents( myGraph ) << endl;
    cout << "loopFree: " << loopFree( myGraph ) << endl;
    cout << "parallelFree: " << parallelFree( myGraph ) << endl;
    cout << "simpleGraph: " << simpleGraph( myGraph ) << endl;
    cout << "eulerian: " << eulerian( myGraph ) << endl;
    
    
}