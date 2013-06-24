//  Copyright (c) 2013 Peter A. Kolski.
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

#include <iostream>

#include <lemon/full_graph.h>
#include <lemon/bin_heap.h>
#include <lemon/quad_heap.h>
#include <lemon/dheap.h>
#include <lemon/fib_heap.h>
#include <lemon/radix_heap.h>
#include <lemon/bucket_heap.h>
#include <lemon/random.h>
#include <lemon/time_measure.h>

using namespace std;
using namespace lemon;

/*
 Seems for INTs the BucketHeap is the fastest for pop()
 */


int main(){
    FullGraph                   f( 10 );
    FullGraph::ArcMap< int >    cost( f );
    
    FullGraph::ArcMap< int >    binHeapMap( f, -1 );
    FullGraph::ArcMap< int >    quadHeapMap( f, -1 );
    FullGraph::ArcMap< int >    dHeapMap( f, -1 );
    FullGraph::ArcMap< int >    fibHeapMap( f, -1 );
    FullGraph::ArcMap< int >    radixHeapMap( f, -1 );
    FullGraph::ArcMap< int >    bucketHeapMap( f, -1 );

    // General heap structures
    BinHeap< int, FullGraph::ArcMap<int> >      binHeap( binHeapMap );
    QuadHeap< int, FullGraph::ArcMap<int> >     quadHeap( quadHeapMap );
    DHeap< int, FullGraph::ArcMap<int>, 16 >    dHeap( dHeapMap );
    FibHeap< int, FullGraph::ArcMap<int> >      fibHeap( fibHeapMap );

    // Special heap structures for int priorities
    RadixHeap< FullGraph::ArcMap<int> >         radixHeap( radixHeapMap );
    BucketHeap< FullGraph::ArcMap<int> >        bucketHeap( bucketHeapMap );
    
    Timer T;


    cout << "Arcs: " << f.arcNum()  << endl;
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        cost[ a ] = rnd.integer( 100000 );
    }

    cout << "PUSH" << endl;
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        binHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        binHeap.pop();
    }
    cout << T.realTime() << "\n";
    

    
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        quadHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        quadHeap.pop();
    }
    cout << T.realTime() << "\n";

    
    
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        dHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        dHeap.pop();
    }
    cout << T.realTime() << "\n";
    
    
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        fibHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        fibHeap.pop();
    }
    cout << T.realTime() << "\n";
    
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        radixHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        radixHeap.pop();
    }
    cout << T.realTime() << "\n";

    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        bucketHeap.push( a, cost[ a ] );
    }
    cout << T.realTime() << "\t\t";
    T.restart();
    for (FullGraph::ArcIt a( f ); a!=INVALID; ++a) {
        bucketHeap.pop();
    }
    cout << T.realTime() << "\n";
    
//    cout << "size: " << binHeap.size() << ", "
//    << "min priority: " << binHeap.prio() << "\n";
//    cout << "size: " << quadHeap.size() << ", "
//    << "min priority: " << quadHeap.prio() << "\n";
//    cout << "size: " << dHeap.size() << ", "
//    << "min priority: " << dHeap.prio() << "\n";
//    cout << "size: " << fibHeap.size() << ", "
//    << "min priority: " << fibHeap.prio() << "\n";
//    cout << "size: " << radixHeap.size() << ", "
//    << "min priority: " << radixHeap.prio() << "\n";
//    cout << "size: " << bucketHeap.size() << ", "
//    << "min priority: " << bucketHeap.prio() << "\n";
//    
//
//    
//    cout << "POP" << endl;
//    
//    cout << "size: " << binHeap.size() << ", "
//         << "min priority: " << binHeap.prio() << "\n";
//    cout << "size: " << quadHeap.size() << ", "
//         << "min priority: " << quadHeap.prio() << "\n";
//    cout << "size: " << dHeap.size() << ", "
//         << "min priority: " << dHeap.prio() << "\n";
//    cout << "size: " << fibHeap.size() << ", "
//         << "min priority: " << fibHeap.prio() << "\n";
//    cout << "size: " << radixHeap.size() << ", "
//         << "min priority: " << radixHeap.prio() << "\n";
//    cout << "size: " << bucketHeap.size() << ", "
//         << "min priority: " << bucketHeap.prio() << "\n";

    cout << "done";
}