//
//  MarkusBeispiel.cpp
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

#include <lemon/list_graph.h>
#include <lemon/random.h>

using namespace std;
using namespace lemon;

int main(){
    
    // ----------------------
    // --- GRAPH ERSTELLUNG
    ListDigraph  dirGraph;
    ListGraph    undirGraph;

    int GraphSize = 10000;
    
    // -- Gib beiden 10000 Knoten
    for (int i = 0; i< GraphSize; i++) {
        dirGraph.addNode();
        undirGraph.addNode();
    }
    
    // -- Gib einem 20000 Kanten
    for (int i = 0; i<20000; i++) {
        ListDigraph::Node  a,b;
        a = dirGraph.nodeFromId( lemon::rnd.integer( GraphSize - 1 ) );
        b = dirGraph.nodeFromId( lemon::rnd.integer( GraphSize - 1 ) );
        dirGraph.addArc(a, b);
    }
    
    cout << "directed nodes: \t"<< countNodes( dirGraph )  << " arcs: \t" << countArcs( dirGraph ) << endl;
    cout << "undirected nodes: \t"<< countNodes( undirGraph) << " arcs: \t" << countArcs( undirGraph ) << endl;
    
    
    // ----------------------
    // --- ITERATION durch einen speziellen Iterator, der nicht dereferenziert werden muss
    // --- ich gehe durch alle Kanten und gebe der Map einen zufälligen Wert
    ListDigraph::ArcMap< int >     arcValues( dirGraph );
    
    for (ListDigraph::ArcIt arc( dirGraph ); arc!=INVALID; ++arc) {
        arcValues[ arc ] = rnd.integer( 100 );
    }
    
    int sum = 0;
    for (ListDigraph::ArcIt arc( dirGraph ); arc!=INVALID; ++arc) {
        sum += arcValues[ arc ];
    }
    
    cout << "Sum: " << sum << endl;
}