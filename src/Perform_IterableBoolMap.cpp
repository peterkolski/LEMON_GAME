//
//  Perform_IterableBoolMap.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 27.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//

#include <lemon/maps.h>
#include <lemon/adaptors.h>
#include <lemon/full_graph.h>
#include <lemon/time_measure.h>

using namespace lemon;
using namespace std;

/*
    Result:
    - IterableBoolMap does not give any advanced in the speed!!!! (But it consumes a lot of memory)
    - If statement is about 3 times faster
    - In case I only check the nodes (there are less) it is 6 times faster
    - SubGraph code is nicer

 
 */


int main(void){

    FullDigraph g(10000);
    FullDigraph::NodeMap<bool>                          activeNodes( g );
    FullDigraph::ArcMap<bool>                           activeArcs( g );
    SubDigraph<FullDigraph>     mSubNormal( g, activeNodes, activeArcs );
    
    double sum = 0.5;
    mSubNormal.enable( mSubNormal.arcFromId( 10 ) );
    mSubNormal.enable( mSubNormal.source( mSubNormal.arcFromId( 10 ) ) );
    mSubNormal.enable( mSubNormal.target( mSubNormal.arcFromId( 10 ) ) );

    Timer T;
    // --- FullGraph Iteration
    for (FullDigraph::ArcIt a( g ); a!=INVALID; ++a) {
        sum+=3*sum;
    }
    cout << g.arcNum() << " Arcs Fullgraph Iteration: "<< T.realTime() << endl;
    
    // --- FullGraph with If statement
    T.restart();
    for (FullDigraph::ArcIt a( g ); a!=INVALID; ++a) {
        if (
//                (activeArcs[ a ] == true) &&
                activeNodes[ g.source( g.arcFromId( 10 ) ) ]  &&
                activeNodes[ g.target( g.arcFromId( 10 ) ) ]  ){
//            cout << "peng" << endl;
            sum+=3*sum;
        }

    }
    cout << "Fullgraph If Statement: \t\t\t"<< T.realTime() << endl;

    
    T.restart();
    for (SubDigraph<FullDigraph>::ArcIt a( mSubNormal ); a!=INVALID; ++a) {
//        cout << "peng" << endl;
        sum+=3*sum;
    }
    cout << countArcs( mSubNormal) << " arcs SubGraph Iteration: \t\t\t"<< T.realTime() << endl;

/*
    IterableBoolMap<FullDigraph, FullDigraph::Arc >     mIterMap( g );
    SubDigraph<FullDigraph, FullDigraph::NodeMap<bool>, IterableBoolMap<FullDigraph, FullDigraph::Arc > >   mSubIterMap( g, activeNodes, mIterMap );
    mSubIterMap.enable( mSubIterMap.arcFromId( 10 ) );
    mSubIterMap.enable( mSubIterMap.source( mSubIterMap.arcFromId( 10 ) ) );
    mSubIterMap.enable( mSubIterMap.target( mSubIterMap.arcFromId( 10 ) ) );
    
    T.restart();
    for ( decltype( mSubIterMap)::ArcIt a( mSubIterMap ); a!=INVALID; ++a) {
        sum += 3 *sum;
    }
    cout << countArcs( mSubIterMap)  << " arcs SubGraph with Iterable Map: \t"<< T.realTime() << endl;
 */


    sleep(5);
    cout << "done";
}