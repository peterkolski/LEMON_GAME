//
//  MemorySize.cpp
//  LEMON_GAME
//
//  Created by Peter on 02.03.13.
//  Copyright (c) 2013 Peter A. Kolski. All rights reserved.
//

#include <iostream>
#include <mach/mach.h>
#include <lemon/smart_graph.h>
#include <lemon/time_measure.h>

using namespace std;
using namespace lemon;

int main(){

    SmartDigraph    g;
    g.reserveNode(   8000000 );
    g.reserveArc( 2000000000 );
    
    Timer   T(true);
    for (int i = 0; i<8000000; i++) {
        g.addNode();
    }
    
    for (int i = 0; i<30; i++) {
        SmartDigraph::Node src = g.nodeFromId( i );
        for (SmartDigraph::NodeIt n(g); n!=INVALID; ++n) {
            g.addArc(src, n);
        }
    }
    
    cout << "time: " << T.realTime() << endl;
//    cout << countArcs( g ) << endl;
    
    // STATIC GRAPH
    
    vector< pair< int, int > >  arcList;
    for (int i = 0; i<250; i++) {
        for (int k = 0; k < 8000000; k++) {
            arcList.push_back( make_pair( i, k) );
        }
    }
    
    cout << "time: " << T.realTime() << endl;
    usleep( 20000000 );
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    task_info(mach_task_self(),
              TASK_BASIC_INFO, (task_info_t)&t_info,
              &t_info_count);
    cout << "Speicher: " << t_info.resident_size / 1000000 << "MB" << endl;

}