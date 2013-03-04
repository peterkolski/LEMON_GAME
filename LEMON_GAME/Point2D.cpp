//
//  Point2D.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski on 22.02.13.
//  Copyright (c) 2013 Peter A. Kolski. All rights reserved.
//


#include <iostream>
#include <lemon/dim2.h>
#include <lemon/smart_graph.h>
#include <lemon/random.h>

using namespace lemon;
using namespace std;

int main(){

    SmartDigraph    g;
    SmartDigraph::NodeMap< dim2::Point<double > >   dist(g);
    rnd.seedFromTime();
    
    SmartDigraph::Node n =    g.addNode();
    
    dist[ n ] = dim2::Point<double>( 7, 23 );

    dist[ n ][ 0 ] = rnd();
    dist[ n ][ 1 ] = rnd();
    
    cout << dist[ n ] << endl;
    cout << dist[ n ][ 0 ] << endl;
    cout << dist[ n ][ 1 ] << endl;
}