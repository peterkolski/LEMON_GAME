//
//  Multiple_Arcs.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 22.02.13.
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