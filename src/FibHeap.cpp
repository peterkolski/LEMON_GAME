//
//  FibHeap.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 27.11.12.
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

#include <lemon/fib_heap.h>

#include <lemon/full_graph.h>
#include <lemon/list_graph.h>
#include <lemon/adaptors.h>
#include <lemon/maps.h>
#include <lemon/random.h>
#include <lemon/time_measure.h>

/*  ------------------------------------
 AIM:
 - To implement a graphHeap structure
 - speed up priority search for the selection mechanism
 - use it on a graph structure
 - turn off the activated arcs
 ------------------------------------
 */

using namespace lemon;
using namespace std;

int main(){
    FullGraph                   f(1000);
    FullGraph::ArcMap< int >    cost( f );
    FullGraph::ArcMap< int >    fibHeapMap( f, -1 );
    FibHeap< int, FullGraph::ArcMap<int> >    myFibHeap( fibHeapMap );
    
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        cost[a] = rnd.integer( 100 );
    }
    
    // --- first
    myFibHeap.push( f.arcFromId( 0 ), 3 );
    
//    // --- second
//    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a){
//        myFibHeap.push( a, cost[ a ]);
//    }
}
