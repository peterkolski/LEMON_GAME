//
//  Heap_tester.cpp
//  MinimalNetGet
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 13.02.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//

#include <iostream>

#include <lemon/bin_heap.h>
#include <lemon/fib_heap.h>

#include <lemon/full_graph.h>
#include <lemon/adaptors.h>
#include <lemon/maps.h>
#include <lemon/random.h>
#include <lemon/lgf_writer.h>
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

    f.resize( 100 );
    mapFill( f, adapNdMap, true);               // never forget! Arcs without nodes don't work
    cout << "Arcs: " << f.arcNum() << endl;
    cout << "Build Time: " << t.realTime() << endl;
    
    
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        cost[a] = rnd.integer( 100 );
        if ( cost[ a ] < 10 ) {
            fAdap.enable( a );
        }
    }
    
    cout << "Fill Time: " << t.realTime() << endl;
    cout << "active arcs: " << countArcs( fAdap ) << endl;

    
    // --- Create the heap ---------------------
    
    FullGraph::ArcMap< int >    binHeapMap( f );
    FullGraph::ArcMap< int >    fibHeapMap( f );
    BinHeap< int, FullGraph::ArcMap< int > >    myBinHeap( binHeapMap );
    FibHeap< int, FullGraph::ArcMap< int > >    myFibHeap( fibHeapMap );

    
    t.restart();
    for (SubDigraph<FullGraph>::ArcIt a( fAdap ); a!=INVALID; ++a) {
        myBinHeap.push( a, cost[ a ]);
    }
    cout << "binHeap fill time: " << t.realTime() << " items: " << myBinHeap.size() << endl;

    sleep(5);
    
//    // ------  Fibonacci Heap  ------
//    t.restart();
//    int i = 0;
//    for (SubDigraph<FullGraph>::ArcIt a( fAdap ); a!=INVALID; ++a){
//        cout << i++ << endl;
//        myFibHeap.push( a, cost[ a ]);
//    }
//    cout << "fibHeap fill time: " << t.realTime() << endl;

    
    
    
/*
    while ( myBinHeap.size() != 0 ) {
        cout << "item ID: " << f.id( myBinHeap.top() )
             << "\t value: " << cost[ myBinHeap.top() ] << endl;
        somethingToDo.push_back( cost[ myBinHeap.top() ] );
        fAdap.disable( fAdap.source( myBinHeap.top() ) );
        fAdap.disable( fAdap.target( myBinHeap.top() ) );
//        fAdap.disable( myBinHeap.top() );
        myBinHeap.pop();
    }
    cout << "HeapTime: " << t.realTime() << endl;
    cout << "active arcs: " << countArcs( fAdap ) << endl;
    cout << "size: " << myBinHeap.size() << endl;
 */
}
