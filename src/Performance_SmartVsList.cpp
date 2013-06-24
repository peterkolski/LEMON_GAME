//
//  Performance_SmartVsList.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 20.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//

#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/full_graph.h>
#include <lemon/adaptors.h>
#include <lemon/time_measure.h>
#include <lemon/random.h>

#include <mach/mach.h>

using namespace std;
using namespace lemon;

int main( void ){

    int                         sysSize = 100000;
    ListDigraph                 LG;
    SmartDigraph                SG;
    SmartDigraph::NodeMap<bool>     actNodes( SG, true );
    SmartDigraph::ArcMap<bool>      actArcs( SG, true );
    int sum;
    
    Timer   t;
    FullDigraph     FG(sysSize);
    cout << "FullGraph built in \t\t" << t.realTime() << endl;    

    t.restart();
    for (int i = 0; i<sysSize; i++) {
        LG.addNode();
    }
    cout << "ListGraph built in \t\t" << t.realTime() << endl;
    t.restart();

    for (int i = 0; i<sysSize; i++) {
        SG.addNode();
    }
    cout << "SmartGraph built in \t" << t.realTime() << endl;

    t.restart();
    SubDigraph<SmartDigraph>    SubSG( SG, actNodes, actArcs ) ;
    cout << "SubGraph built in \t\t" << t.realTime() << endl << endl;
    
    
    mapFill(SG, actNodes, true );
    
    // -------------------------------------
    // --- Test of iteration speed
    

    t.restart();
    for (ListDigraph::NodeIt n(LG); n!=INVALID; ++n) {
        sum += LG.id( n );
    }
    cout << "ListGraph iterations \t" << t.realTime() << endl;

    // --- Checking a map value
    ListDigraph::NodeMap<bool>          mBoolMapNd(LG, true);
    ListDigraph::NodeMap<int>           mValueMap(LG, 1);
    
    t.restart();
    for (ListDigraph::NodeIt n(LG); n!=INVALID; ++n) {
        if (mValueMap[ n ] < 3){
            mBoolMapNd[ n ] = false;
            sum += LG.id( n );
        }
    }
    cout << "ListGraph iterations with if & Map assignment \t" << t.realTime() << endl;
    
    t.restart();
    for (FullDigraph::NodeIt n(FG); n!=INVALID; ++n) {
        sum += FG.id( n );
    }
    cout << "FullGraph iterations \t" << t.realTime() << endl;

    
    t.restart();
    for (SmartDigraph::NodeIt n(SG); n!=INVALID; ++n) {
        sum += SG.id( n );
    }
    cout << "SmartGraph iterations \t" << t.realTime() << endl;

    t.restart();
    for (SubDigraph<SmartDigraph>::NodeIt n(SubSG); n!=INVALID; ++n) {
        sum += SubSG.id( n );
    }
    cout << "SubGraph iterations \t" << t.realTime() << endl;
    cout << "SubGraph Nodes: " << countNodes( SubSG ) << endl << endl;
    
    // -------------------------------------
    // --- Arc deletion & switching off
    
    t.restart();
    for ( int i = 0; i<sysSize/2; i++) {
//        LG.erase( LG.nodeFromId( i ) );
        LG.erase( LG.nodeFromId( rnd.integer(0, sysSize / 2) ) );
    }
    cout << "ListGraph deletion \t\t" << t.realTime() << endl;
    cout << "ListGraph size \t\t" << countNodes(LG ) << endl;
    
    t.restart();
    for ( int i = 0; i<sysSize/2; i++) {
        actNodes[ SG.nodeFromId( i ) ];
    }
    cout << "SubGraph deactivation \t" << t.realTime() << endl;
    
    // -------------------------------------
    // --- Test of iteration speed after deletion
    
    t.restart();
    for (ListDigraph::NodeIt n(LG); n!=INVALID; ++n) {
        sum += LG.id( n );
    }
    cout << "ListGraph iterations \t" << t.realTime() << endl;


    
    t.restart();
    for (FullDigraph::NodeIt n(FG); n!=INVALID; ++n) {
        sum += FG.id( n );
    }
    cout << "FullGraph ARC iterations \t" << t.realTime() << endl;
    cout << "FullGraph ARC size \t" << FG.arcNum() << endl;
    
    // -------------------------------------
    // --- FullGraph SubGraph ARC Iteration
    
    t.restart();
    FullDigraph::NodeMap<bool>     factNodes( FG, true );
    FullDigraph::ArcMap<bool>      factArcs( FG, true );
    SubDigraph<FullDigraph>         subFull( FG, factNodes, factArcs );
    cout << "FullGraph SubGraph built \t" << t.realTime() << endl;
    
    t.restart();
    for (SubDigraph<FullDigraph>::ArcIt n(subFull); n!=INVALID; ++n) {
        sum += subFull.id( n );
    }
    cout << "SUB FullGraph ARC iterations \t" << t.realTime() << endl;
//    cout << "SUB FullGraph ARC size \t" << countArcs( subFull) << endl;

//    struct task_basic_info t_info;
//    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
//    task_info(mach_task_self(),
//              TASK_BASIC_INFO, (task_info_t)&t_info,
//              &t_info_count);
//    cout << "Speicher: " << t_info.resident_size / 1000000 << "MB" << endl;ç
    
    cout << sum << endl;
    cout << "DONE!";
}
