//
//  IterableMaps.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 19.02.13.
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