//
//  NetworkSimplex.cpp
//  MinimalNetGet
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 11.02.12.
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