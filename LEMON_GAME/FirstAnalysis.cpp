//
//  FirstAnalysis.cpp
//  LemonGame
//
//  Created by BildPeter Visuals on 09.11.11.
//  Copyright (c) 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/list_graph.h>

#include <lemon/lgf_reader.h>
#include <lemon/connectivity.h>
#include <lemon/euler.h>
#include <lemon/time_measure.h>
#include <lemon/adaptors.h>





using namespace lemon;
using namespace std;

int eraseLoopArcs( ListDigraph &graph );
int parallelArcs( ListDigraph &myGraph );



int main( void ){

    ListDigraph     myGraph;
    
    ListDigraph::NodeMap< int >         readID          ( myGraph );
    ListDigraph::NodeMap< string >      euRegioTag      ( myGraph );
    ListDigraph::NodeMap< bool >        euRegioBool     ( myGraph );
    
    ListDigraph::ArcMap< int >          transpAmount    ( myGraph );
    ListDigraph::ArcMap< string >       edgeList        ( myGraph );
    
    
    try {
        digraphReader( myGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/ZuverlegungEuregio_comlete.lgf")
        .nodeMap( "sourceID", readID)
        .nodeMap( "TypeName", euRegioTag )
        .nodeMap( "EUREGIO_BOOL", euRegioBool )
        .arcMap( "TransportAmount", transpAmount)
        .arcMap( "Edgelist", edgeList )
        .run();
    } catch (lemon::Exception& error) { // check if there was any error
        std::cerr << "Error: " << error.what() << std::endl;
    }
    
    
    // ----- NodeFilter, der nur das EUREGIO Netz umfasst -----
    
    FilterNodes< ListDigraph, ListDigraph::NodeMap< bool >  > eurGraph( myGraph, euRegioBool );
    
    
    
    cout << "Nodes: " << countNodes( myGraph ) << endl;
    cout << "Arcs: " << countArcs( myGraph ) << endl;
    cout << "countStronglyConnectedComponents: " << countStronglyConnectedComponents( myGraph ) << endl;
    cout << "countStronglyConnectedComponents EUREGIO: " << countStronglyConnectedComponents( eurGraph ) << endl;
    cout << "loopFree: " << loopFree( myGraph ) << endl;
    cout << "parallelFree: " << parallelFree( myGraph ) << endl;
    cout << "simpleGraph: " << simpleGraph( myGraph ) << endl;
    cout << "eulerian: " << eulerian( myGraph ) << endl;
    
    
    // ====================================================================================
    // ----- Check for SelfLoops -----
    cout << endl;
    
    int loopArcs = 0;
    cout << "ArcID with loop: " << endl << "ID\tEdges\tamount" << endl;
    for (FilterNodes< ListDigraph >::ArcIt a( eurGraph ); a != INVALID; ++a){
        
        if (eurGraph.source( a ) == eurGraph.target( a ) ){
            cout << eurGraph.id( a ) << "\t" << edgeList[ a ] << "\t" << transpAmount[ a ] << endl;
            loopArcs++;
        }
    }

    cout << endl << eraseLoopArcs( myGraph ) << " arcs erased" << endl << endl;
    cout << "loopFree: " << loopFree( myGraph ) << endl;
    cout << "parallelFree: " << parallelFree( myGraph ) << endl;
    cout << "simpleGraph: " << simpleGraph( myGraph ) << endl;
    
    // ===================================================================================

//    eraseLoopArcs( myGraph );
    
    // ----- Check for parallel Arcs -----

    cout << "Parallele QuellKnoten: " << parallelArcs( myGraph ) << endl;
 
    digraphWriter( eurGraph, cout)
    .arcMap("amount", transpAmount )
    .run();
 }


// ====================================================================================
// ====================================================================================

// ----- Return the nr of erased arcs -----

int eraseLoopArcs( ListDigraph &graph ){
    int loopArcs = 0;
    for (ListDigraph::ArcIt a( graph ); a != INVALID; ++a){
        
        if (graph.source( a ) == graph.target( a ) ){
            graph.erase( a );
            loopArcs++;
        }
    }
    return loopArcs;   
}

// ---- Parallele Kanten -----
int parallelArcs( ListDigraph &myGraph ){

//    cout << "Parallele QuellKnoten: " << endl;
    
    vector< int > parallelArcID;
    int paraCount = 0;
    for ( ListDigraph::NodeIt n( myGraph ); n != INVALID; ++n ){
        parallelArcID.clear();
        for (ListDigraph::InArcIt ia( myGraph, n) ; ia != INVALID; ++ia) {
            parallelArcID.push_back( myGraph.id( myGraph.source( ia ) ) );
        }
        sort( parallelArcID.begin(), parallelArcID.end() );
        for (int i = 0; i < (parallelArcID.size() - 1); i++) {
            if ( parallelArcID[ i ] == parallelArcID[ i+1 ] ){
//                cout << "ID: "<< parallelArcID[ i ] << endl;
                paraCount++;
            }
        }
        //        cout << "--" << endl;
    }
    return  paraCount;
}
