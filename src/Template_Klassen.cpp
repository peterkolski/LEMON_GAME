//
//  KlassenTemplate.cpp
//  LEMON_GAME
//
//  Created by Peter on 16.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//


/* -------------------------------------------------------------------------------------
    Make a Class independen from Graph Class
 
 use: 
 template < typename DGR>
 typename DGR
 typename DGR::template NodeMap < >
 typename DGR::NodeIt
 }
 
 ------------------------------------------------------------------------------------- */

#include <lemon/full_graph.h>
#include <lemon/list_graph.h>

using namespace lemon;
using namespace std;

template < typename DGR>    class   outputClass {
public:
    const DGR                             &mGraph;
    /*  I want to use a type of my template type DGR. 
        C++ requires to specify that DGR is a template type!
     */
    typename DGR::template NodeMap<int>   mMap;

    
    outputClass(const DGR &graph )
    : mGraph(graph),
    mMap(graph)
    {};
    
    void output(){
        for (typename DGR::NodeIt n( mGraph ); n!=INVALID; ++n) {
            std::cout << mGraph.id( n ) << " value: " << mMap[ n ] << endl;
        }
    }
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

int main( void ){
    ListDigraph     g;
    FullDigraph     f(5);
    
    outputClass<ListDigraph>    outL( g );
    outputClass<FullDigraph>    outF( f );
    
    g.addNode();
    
    outL.output();
    cout << "Next Graph" << endl << endl;
    outF.output();
}


