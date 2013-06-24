//
//  IterableMaps.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 19.02.13.
//  Copyright (c) 2013 Peter A. Kolski. All rights reserved.
//

#include <lemon/full_graph.h>
#include <lemon/maps.h>

using namespace lemon;
using namespace std;

typedef IterableBoolMap<FullDigraph, FullDigraph::Node> itBool;

int main(){

    FullDigraph g(10);
    
    itBool myIterMap( g );
    
    // --------------------
    // --- set node 2 true
    // --------------------
    myIterMap.set( g.nodeFromId(2), true);
    cout <<"state: " <<  myIterMap[ g.nodeFromId( 2 ) ] << endl<<endl;
    
    // --------------------
    // --- iterate only over the false nodes
    // --------------------
    for (itBool::FalseIt f(myIterMap); f!=INVALID; ++f) {
        cout << "node: "<< g.id( f )  << endl;
    }
    
    // --------------------
    // --------------------
    typedef IterableIntMap<FullDigraph, FullDigraph::Node> secondType;
    secondType  mIntMap( g );
    cout << mIntMap[ g.nodeFromId( 2 ) ] << endl;
    
    mIntMap[ g.nodeFromId( 3 ) ] = 4;
    mIntMap[ g.nodeFromId( 7 ) ] = 4;
    mIntMap[ g.nodeFromId( 9 ) ] = 4;
    
    // --- show all node with value 4
    for ( secondType::ItemIt item( mIntMap, 4); item!=INVALID; ++item) {
        cout << "node: " << g.id( item ) << endl;
    }
}