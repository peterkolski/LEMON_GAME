//
//  IDsAndMaps.cpp
//  LemonGame
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 09.11.11.
//  Copyright (c) 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>
#include <lemon/maps.h>

#include <lemon/adaptors.h>

using namespace lemon;
using namespace std;

int main( void ){


    ListDigraph myGraph;
    
    ListDigraph::NodeMap< int >         readID          ( myGraph );
    ListDigraph::NodeMap< string >      euRegioTag      ( myGraph );
    ListDigraph::NodeMap< bool >        euRegioBool     ( myGraph );
    
    ListDigraph::ArcMap< int >          transpAmount    ( myGraph );
    ListDigraph::ArcMap< string >       egdeList        ( myGraph );
    
    // -----  ReadGraph -----
    
    try {
        digraphReader( myGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/DatenVerarbeitet/euregio.lgf")
        .nodeMap( "label", readID)
        .arcMap( "amount", transpAmount)
        .run();
    } catch (lemon::Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
    }
    
    // ----- Eruregio Bools zuordnen ----
    for (ListDigraph::NodeIt n( myGraph ); n != INVALID; ++n) {
        if ( readID[ n ] > 200000) {
            // Nicht Euregio
            euRegioBool[ n ] = 0;   
            euRegioTag[ n ] = "Nicht-EUREGIO";
        }
        else{
            euRegioBool[ n ] = 1;   
            euRegioTag[ n ] = "EUREGIO";    
        }
    }
  
    // ----- Edgelist erstellen als String -----
    for (ListDigraph::ArcIt arc( myGraph ); arc != INVALID; ++arc) {
        stringstream ss;
        ss << readID[ myGraph.source( arc )];
        ss << " ";
        ss << readID[ myGraph.target( arc ) ];
        egdeList[ arc ] = ss.str();
    }

    
    cout << "Nodes: " << countNodes( myGraph ) << " \t Arcs: " << countArcs( myGraph ) << endl;
    
    digraphWriter( myGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/ZuverlegungEuregio_comlete.lgf")
    .nodeMap( "EUREGIO_BOOL", euRegioBool)
    .nodeMap( "sourceID", readID)
    .nodeMap( "TypeName", euRegioTag)
    .arcMap( "TransportAmount",  transpAmount)
    .arcMap( "Edgelist", egdeList)
    .run();
    
  
}