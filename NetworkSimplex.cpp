//
//  NetworkSimplex.cpp
//  MinimalNetGet
//
//  Created by BildPeter Visuals on 11.02.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/network_simplex.h>
#include <lemon/full_graph.h>
#include <lemon/adaptors.h>
#include <lemon/maps.h>
#include <lemon/lgf_writer.h>

using namespace lemon;
using namespace std;

typedef SubDigraph< FullGraph > tSubFull;

int main(){
    FullGraph f;
    FullGraph::NodeMap< bool >  nodeAdapMap( f, true );
    FullGraph::ArcMap< bool >   arcAdapMap( f, true );

    tSubFull                    mySubGraph( f, nodeAdapMap, arcAdapMap );
    tSubFull::ArcMap< int >     cost(   mySubGraph );
    tSubFull::NodeMap< int >    supply( mySubGraph );
    tSubFull::ArcMap< double >  flow(   mySubGraph );
    
    
    NetworkSimplex< SubDigraph< FullGraph > >   NetPlex ( mySubGraph );
    f.resize( 3 );
    // maps have to be activated afterwards
    mapFill( f, nodeAdapMap, true );
    mapFill( f, arcAdapMap,  true );
    mapFill( f, cost, 20);
    mapFill( f, supply, 3);

    NetPlex
//    .costMap( cost )
//    .supplyMap( supply )
    .run();
    
//    NetPlex
//    .flowMap( flow );
    
    digraphWriter( mySubGraph )
    .arcMap( "arcAdapMap", arcAdapMap )
    .nodeMap( "nodeAdapMap", nodeAdapMap )
    .run();
}