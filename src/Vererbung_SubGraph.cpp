//
//  Vererbung_SubGraph.cpp
//  LEMON_GAME
//
//  Created by Peter on 16.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//


/* -------------------------------------------------------------------------------------
        Test for NetGen
    - Inherit a Graph class
    - create a Subgraph of the Graph as member instance
 ------------------------------------------------------------------------------------- */


#include <lemon/full_graph.h>
#include <lemon/adaptors.h>

using namespace lemon;
using namespace std;



class SystemONE : public FullDigraph{
public:
    FullDigraph::NodeMap< bool >    activeNodes;
    FullDigraph::ArcMap< bool >     activeArcs;
    SubDigraph< FullDigraph >       mSubGraph;
    
    
    SystemONE() :
    activeArcs( *this),
    activeNodes( * this),
    mSubGraph( *this, activeNodes, activeArcs )
    {}
    
};


class SystemTWO : public FullDigraph{
public:
    FullDigraph::NodeMap< bool >    *activeNodes;
    FullDigraph::ArcMap< bool >     *activeArcs;
    SubDigraph< FullDigraph >       *mSubGraph;
    
    
    SystemTWO()
    {
        activeNodes = new FullDigraph::NodeMap<bool>(*this);
        activeArcs  = new FullDigraph::ArcMap<bool>(*this);
        mSubGraph   = new SubDigraph< FullDigraph>(*this, *activeNodes, *activeArcs);
    
    }
    
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

int main( void ){

    SystemONE   g;
    SystemTWO   f;

    g.resize( 100 );
    cout << "size: " << g.nodeNum() << endl;
    cout << "size: " << countNodes( g.mSubGraph ) << endl;
    g.activeNodes[ g.nodeFromId( 10 ) ] = true;
    cout << "size: " << countNodes( g.mSubGraph ) << endl;
    
    f.resize( 100 );
    cout << "size: " << f.nodeNum() << endl;
    cout << "size: " << countNodes( (*f.mSubGraph) ) << endl;
    (*f.activeNodes)[ f.nodeFromId( 10 ) ] = true;
    cout << "size: " << countNodes( g.mSubGraph ) << endl;
}

