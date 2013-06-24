//
//  KlassenTemplate.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 16.11.12.
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


/* -------------------------------------------------------------------------------------
    Make a Class independen from Graph Class
 
 template < typename DGR>
 typename DGR::template NodeMap<int>
 typename DGR::NodeIt

 
 ------------------------------------------------------------------------------------- */

#include <lemon/full_graph.h>
#include <lemon/list_graph.h>

using namespace lemon;
using namespace std;

template < typename DGR>    class   outputClass {
public:
    const DGR                 &mGraph;
    typename DGR::template NodeMap<int>   mMap;
    
    outputClass( const DGR &graph )
    : mGraph(graph),
    mMap(graph)
    {};
    
    void output(){
        for (typename DGR::NodeIt n( mGraph ); n!=INVALID; ++n) {
            std::cout << "value: " << mMap[ n ] << endl;
        }
    }
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

int main( void ){
    ListDigraph     g;
    outputClass<ListDigraph>    out( g );
    
    g.addNode();
    
    out.output();
    
}


