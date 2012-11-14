//
//  main.cpp
//  EUREGIO_Analysis
//
//  Created by Peter A. Kolski on 25.11.11.
//  Copyright (c) 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>
#include <lemon/adaptors.h>

using namespace lemon;
using namespace std;

int main (int argc, const char * argv[])
{
    ListDigraph                                 myGraph, copiedGraph;
    ListDigraph::NodeMap< bool >                euregBoolNodeMap( myGraph );
    ListDigraph::NodeMap< int >                 sourceIDorig (myGraph );
    ListDigraph::NodeMap< int >                 sourceIDnew (copiedGraph );
    ListDigraph::NodeMap< int >                 inFluxOrig (myGraph );
    ListDigraph::NodeMap< int >                 inFluxNew (copiedGraph );
    ListDigraph::ArcMap< int >                  transpAmounOrig (myGraph);
    ListDigraph::ArcMap< int >                  transpAmountNew (copiedGraph );
    
    ListDigraph::NodeMap< ListDigraph::Node >   refMapOrigin( myGraph );
    
    digraphReader( myGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/ZuverlegungEuregio_comlete.lgf")
    .nodeMap( "EUREGIO_BOOL", euregBoolNodeMap )
    .nodeMap( "sourceID", sourceIDorig)
    .arcMap( "TransportAmount", transpAmounOrig)
    .run();
    
    for (ListDigraph::NodeIt n( myGraph ); n != INVALID; ++n) {
        int sumInFlux = 0;
        for (ListDigraph::InArcIt inArc(myGraph, n); inArc != INVALID; ++inArc) {
            sumInFlux += transpAmounOrig[ inArc ];
        }
        inFluxOrig[ n ] = sumInFlux;
    }
    
    
    digraphCopy( myGraph, copiedGraph)
    .nodeRef( refMapOrigin )
    .nodeMap(sourceIDorig, sourceIDnew)
    .nodeMap( inFluxOrig, inFluxNew)
    .arcMap(transpAmounOrig, transpAmountNew)
    .run();
    
    cout << "NodesNr: " << countNodes( myGraph ) << endl;
    
    int gang = 0;
    
    for (ListDigraph::NodeIt n( myGraph ); n != INVALID; ++n) {
        if ( ! euregBoolNodeMap[ n ] ) copiedGraph.erase( refMapOrigin[ n ] );
        gang++;
    }
    cout << "NodesNr after erasing: " << countNodes( copiedGraph ) << endl;  
    cout << "ArcsNr after erasing: " << countArcs( copiedGraph ) << endl;  
    cout << "Durchgänge: " << gang << endl;   
    
    digraphWriter( copiedGraph, "/Users/sonneundasche/Dropbox/FLI/30 MedVetStaph/01 Zuverleger/ZuverlegungEuregio_OnlyEUREGIO.lgf")
    .nodeMap( "sourceID", sourceIDnew)
    .nodeMap( "inFlux", inFluxNew)
    .arcMap( "TransportAmount", transpAmountNew)
    .run();
    
    
    return 0;
}

