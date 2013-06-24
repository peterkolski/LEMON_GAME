//
//  Dijkstra_test.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 23.02.13.
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

#include <iostream>
#include <lemon/dijkstra.h>
#include <lemon/smart_graph.h>
#include <lemon/maps.h>

using namespace std;
using namespace lemon;

int main(){

    SmartGraph            g;
    SmartGraph::Node      a,b,c,d;
    ConstMap<SmartGraph::Arc, int>   mLength( 1 );
    SmartGraph::NodeMap<int>         mDist(g);
    
    a = g.addNode();
    b = g.addNode();
    c = g.addNode();
    d = g.addNode();
    
    g.addEdge(a, b);
    g.addEdge(b, c);
    g.addEdge(c, d);
    
    
    dijkstra(g, mLength)
    .distMap(mDist)
    .run(c);
    
    for (SmartGraph::NodeIt n(g); n!=INVALID; ++n) {
        cout << g.id(n) << " : "<< mDist[ n ] << endl;
    }
    
}

