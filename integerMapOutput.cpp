//
//  File.cpp
//  MinimalNetGet
//
//  Created by BildPeter Visuals on 01.02.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//

#include <iostream>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>

using namespace lemon;
using namespace std;

int main(){

    ListDigraph g;
    ListDigraph::NodeMap< vector < int > >  myVecMap (g);
    ListDigraph::NodeMap< int >             myIntMap (g);
    
    g.addNode();
    
    (myVecMap[ g.nodeFromId( 0 ) ]).push_back( 333 );
//    (myVecMap[ g.nodeFromId( 0 ) ]).push_back( 333 );
//    (myVecMap[ g.nodeFromId( 0 ) ]).push_back( 333 );
    
    myIntMap[ g.nodeFromId( 0 )] = 444;
    
    digraphWriter( g )
//    .nodeMap( "vector", myVecMap )
    .nodeMap( "int", myIntMap)
    .run();
    
}