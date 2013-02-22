//
//  Multiple_Arcs.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski on 22.02.13.
//  Copyright (c) 2013 Peter A. Kolski. All rights reserved.
//

/*
    TEST if I perform addArc between nodes multiple time, if there will be multiple arcs.
 
    --> there will be multiple arcs
 
 */

#include <lemon/smart_graph.h>

using namespace lemon;
using namespace std;

int main(){

    SmartDigraph    g;
    
    auto a = g.addNode();
    auto b = g.addNode();
    
    for (int i = 0; i<20; i++) {
        g.addArc(a, b);
    }
    
    cout << countArcs( g );

}