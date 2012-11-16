//
//  KlassenTemplate.cpp
//  LEMON_GAME
//
//  Created by Peter on 16.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//


/* -------------------------------------------------------------------------------------
    Make a Class independen from Graph Class
 
 template <typename Graph>
 inline int countNodes(const Graph& g) {
 return _core_bits::CountNodesSelector<Graph>::count(g);
 }
 
 ------------------------------------------------------------------------------------- */

#include <lemon/full_graph.h>
#include <lemon/list_graph.h>

using namespace lemon;
using namespace std;

template < typename DGR>    class   outputClass {
public:
    DGR                 &mGraph;
//    DGR::NodeMap<int>   mMap;
    
    outputClass( const DGR &graph)
    : mGraph(graph)
//    mMap(graph)
    {};
    
    void output(){
//        for (DGR::NodeIt n( mGraph ); n!=INVALID; ++n) {
//            std::cout << "value: " << mMap[ n ] << endl;
//        }
    }
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

int main( void ){
    ListDigraph     g;
    outputClass<ListDigraph>    out( g );
    out.output();
}


