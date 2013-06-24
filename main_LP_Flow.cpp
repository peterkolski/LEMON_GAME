//
//  main_Expl_Flow.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 08.07.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//

//
//  main.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 08.07.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//


/* 
 * This demo program shows how to solve the maximum flow 
 * problem using the LEMON LP solver interface. We would 
 * like to lay the emphasis on the simplicity of the way 
 * one can formulate LP constraints that arise in graph 
 * theory using LEMON
 *
 */


#include <iostream>
#include <lemon/smart_graph.h>
#include <lemon/lgf_reader.h>
#include <lemon/lp.h>

using namespace lemon;

#define 	LEMON_DEFAULT_LP

template <typename GR, typename CAP>    double maxFlow(const GR &g, const CAP &capacity,typename GR::Node source, typename GR::Node target)
{
    TEMPLATE_DIGRAPH_TYPEDEFS(GR);
    
    // Create an instance of the default LP solver
    Lp lp;
    
    // Add a column to the problem for each arc
    typename GR::template ArcMap<Lp::Col> f(g);
    lp.addColSet(f);
    
    // Capacity constraints
    for (ArcIt a(g); a != INVALID; ++a) {
        lp.colLowerBound(f[a], 0);
        lp.colUpperBound(f[a], capacity[a]);
    }
    
    // Flow conservation constraints
    for (NodeIt n(g); n != INVALID; ++n) {
        if (n == source || n == target) continue;
        Lp::Expr e;
        for (OutArcIt a(g, n); a != INVALID; ++a) e += f[a];
        for (InArcIt a(g, n); a != INVALID; ++a) e -= f[a];
        lp.addRow(e == 0);
    }
    
    // Objective function
    Lp::Expr o;
    for (OutArcIt a(g, source); a != INVALID; ++a) o += f[a];
    for (InArcIt a(g, source); a != INVALID; ++a) o -= f[a];
    lp.max();
    lp.obj(o);
    
    // Solve the LP problem
    lp.solve();
    
    return lp.primal();
}


int main(int argc, char *argv[])
{
    // Check the arguments
    if (argc < 2) {
        std::cerr << "Usage:" << std::endl;
        std::cerr << "  lp_maxflow_demo <input_file>" << std::endl;
        std::cerr << "The given input file has to contain a maximum flow\n"
        << "problem in LGF format (like 'maxflow.lgf')."
        << std::endl;
        return 0;
    }
    
    // Read the input file
    SmartDigraph g;
    SmartDigraph::ArcMap<double> cap(g);
    SmartDigraph::Node s, t;
    
    digraphReader(g, argv[1])
    .arcMap("capacity", cap)
    .node("source", s)
    .node("target", t)
    .run();
    
    // Solve the problem and print the result
    std::cout << "Max flow value: " << maxFlow(g, cap, s, t) << std::endl;
    
    return 0;
}