//
//  StaticGraph.cpp
//  LemonGame
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 09.11.11.
//  Copyright (c) 2011 Peter A. Kolski.
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