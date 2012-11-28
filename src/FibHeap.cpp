//
//  FibHeap.cpp
//  LEMON_GAME
//
//  Created by Peter on 27.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//


#include <iostream>

#include <lemon/fib_heap.h>

#include <lemon/full_graph.h>
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
    
    FullGraph f;
    FullGraph::ArcMap< int >    cost( f );
    vector< int >               somethingToDo;
    
    FullGraph::NodeMap< bool >  adapNdMap( f, true );
    FullGraph::ArcMap< bool >   adapArcMap ( f );
    SubDigraph<FullGraph>       fAdap (f , adapNdMap, adapArcMap);
    
    Timer t(true);
    
    f.resize( 1000 );
    mapFill( f, adapNdMap, true);               // never forget! Arcs without nodes don't work
    cout << "Arcs: " << f.arcNum() << endl;
    cout << "Build Time: " << t.realTime() << endl;
    
    
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        cost[a] = rnd.integer( 100 );
        if ( cost[ a ] < 1 ) {
            fAdap.enable( a );
        }
    }
    
    cout << "Fill Time: " << t.realTime() << endl;
    cout << "active arcs: " << countArcs( fAdap ) << endl;
    
    
    // --- Create the heap ---------------------
    
    FullGraph::ArcMap< int >    fibHeapMap( f );
    FibHeap< int, FullGraph::ArcMap< int > >    myFibHeap( fibHeapMap );
    
    // ------  Fibonacci Heap  ------
    t.restart();
    int i = 0;
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a){
        cout << i++ << endl;
        myFibHeap.push( a, cost[ a ]);
    }
    cout << "fibHeap fill time: " << t.realTime() << endl;
  }
