//
//  LEMON_GCD.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 14.01.13.
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

#include "LEMON_GCD.h"

#include <stdio.h>
#include <dispatch/dispatch.h>
#include <lemon/smart_graph.h>
#include <lemon/adaptors.h>
#include <lemon/time_measure.h>

using namespace lemon;
using namespace std;

/*
        ------------------------  INFO --------------------------------
 GCD läuft mit einigen Umwegen.

 UMWEGE:
 -	   SubGraph, Pointer zum Graphen und Node Erzeugung in der Dispatch-Schleife

 FAZIT
 - Noch ist es um einiges langsamer als der einfach For-Loop.
 - Das kann sich ändern, wenn jede Operation viel Power braucht. Der Wechsel ist nicht effizient
 - Vielleicht können sich die Umwege durch eine andere LEMON version verbessern (Thread-saveer Zugriff auf eine NodeMap)
 */


int main(){

    SmartDigraph  g1;
    g1.nodeFromId( 0 );

    
    SmartDigraph    g;
    for (int i = 0; i<100000000; i++)      g.addNode();
    int loopCount = countNodes( g );
//    loopCount = 21;
    
    SmartDigraph::NodeMap<bool>     nMap( g, true );
    SmartDigraph::ArcMap<bool>      aMap( g, true );
    SubDigraph<SmartDigraph>        subG( g, nMap, aMap );
    SubDigraph<SmartDigraph>::NodeMap<int>      nValue( subG );
    SubDigraph<SmartDigraph>::NodeMap<int>      *nValue2;
    nValue2 = &nValue;
    
    Timer   T(true);
    dispatch_apply(loopCount, dispatch_get_global_queue(0, 0), ^(size_t i) {
        SmartDigraph::Node n = subG.nodeFromId( (int)i );
        (*nValue2)[ n ] = i*i;
//        cout << subG.id(n) << endl;
    });
    cout << "GCD: \t\t" << T.realTime() << endl;

    T.restart();
    for (SmartDigraph::NodeIt n(g); n!=INVALID; ++n) {
        int i = g.id(n);
        (*nValue2)[ n ] = i * i;
    }
    cout << "For-Loop: \t" << T.realTime() << endl;    
        
//    for (SmartDigraph::NodeIt n(g); n!=INVALID; ++n) {
//        cout << "Node: " << g.id(n) << " : " << nValue[ n ] << endl;
//    }
    
}