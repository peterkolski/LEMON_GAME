//
//  Dijkstra_test.cpp
//  LEMON_GAME
//
//  Created by Peter on 23.02.13.
//  Copyright (c) 2013 Peter A. Kolski. All rights reserved.
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

