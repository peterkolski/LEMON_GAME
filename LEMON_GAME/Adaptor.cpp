//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 21.10.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//

#include <iostream>


#include <iostream>
#include <fstream>
#include <lemon/list_graph.h>
#include "lemon/adaptors.h"



using namespace lemon;
using namespace std;


int main(){

    ListDigraph myGraph;
    
    myGraph.addNode();
    
    SubDigraph< ListDigraph >::NodeFilterMap NFM( myGraph, true );
    SubDigraph< ListDigraph >::ArcFilterMap  AFM( myGraph, true );
    
    SubDigraph< ListDigraph > subMyGraph( myGraph, NFM, AFM );
    
    ListDigraph::Node a = subMyGraph.addNode();
    NFM[a] = true;
    subMyGraph.disable( a );
    
    ListDigraph::Node b = subMyGraph.addNode();
    subMyGraph.enable( b );
    subMyGraph.addArc( a, b );
    
    subMyGraph.enable( subMyGraph.addNode() );
    
    cout << "SubGraph arcs: " << countArcs( subMyGraph ) << endl;
    cout << "SubGraph nodes: " << countNodes( subMyGraph ) << endl;    
    
    cout << endl;    
    
    // Activate all nodes and arcs
    
    for (SubDigraph< ListDigraph >::ArcIt a( subMyGraph ); a != INVALID; ++a) {
        subMyGraph.enable( a );                     // does not work, because no arcs are iterated
        cout << subMyGraph.status( a ) << endl;
    }

    for (SubDigraph< ListDigraph >::NodeIt n( subMyGraph ); n != INVALID; ++n) {
        subMyGraph.erase( n );
        cout << subMyGraph.status( n ) << endl;
        subMyGraph.disable( n );
    }
    
    // Wenn ein Knoten im Adapter hinzugefügt wird, dann ist er AUS - WARUM????x

    cout << "SubGraph arcs: " << countArcs( subMyGraph ) << endl;
    cout << "SubGraph nodes: " << countNodes( subMyGraph ) << endl;    
    
    cout << endl;    
    cout << "myGraph arcs: " << countArcs( myGraph ) << endl;
    cout << "myGraph nodes: " << countNodes( myGraph ) << endl;
    
    
    return 0;


}