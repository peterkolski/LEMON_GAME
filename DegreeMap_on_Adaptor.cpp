//
//  DegreeMap_on_Adaptor.cpp
//  MinimalNetGet
//
//  Created by BildPeter Visuals on 13.02.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
//

#include <iostream>

#include <lemon/full_graph.h>
#include <lemon/maps.h>
#include <lemon/lgf_writer.h>
#include <lemon/adaptors.h>

/*
    The aim is to test, if the degreeMap on a adaptor tells me the changed
    degrees.
 
    -> Works!
 */

using namespace std;
using namespace lemon;

typedef SubDigraph< FullGraph> tpSubFull;

int main(){

    FullGraph f;
    f.resize( 4 );
    
    FullGraph::NodeMap< bool >  ndMapBool( f );
    FullGraph::ArcMap< bool >   arcMapBool( f );
    SubDigraph< FullGraph >     fAdap( f, ndMapBool, arcMapBool );
    
    mapFill( f, ndMapBool, true );
//    mapFill( f, arcMapBool, true);
    
    fAdap.enable( f.arcFromId( 1 ));
    
    cout << "status? " << fAdap.status( f.arcFromId(1)) << endl;
    cout << "status? " << fAdap.status( f.arcFromId(2)) << endl;
    
    InDegMap< tpSubFull > inMap( fAdap );
    OutDegMap< tpSubFull> outMap( fAdap );
    
    digraphWriter( f )
    .nodeMap("InDegrees", inMap )
    .nodeMap("OutDegrees", outMap)
//    .nodeMap("Degree", degMap)
    .run();

    cout << "finished";
}