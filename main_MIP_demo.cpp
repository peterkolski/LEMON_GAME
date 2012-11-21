//
//  main_MIP_demo.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski on 08.07.11.
//  Copyright 2011 BildPeter Visuals. All rights reserved.
//

/*
 * This demo program shows how the LEMON MIP solver interface 
 * can be used. A simple mixed integer programming (MIP) 
 * problem is formulated and solved using the default MIP 
 * solver (e.g. GLPK).
 *
 */


#include <iostream>
#include <lemon/lp.h>

using namespace lemon;

int main()
{
    // Create an instance of the default MIP solver class
    // (it will represent an "empty" problem at first)
    Mip mip;
    
    // Add two columns (variables) to the problem
    Mip::Col x1 = mip.addCol();
    Mip::Col x2 = mip.addCol();
    
    // Add rows (constraints) to the problem
    mip.addRow(x1 - 5 <= x2);
    mip.addRow(0 <= 2 * x1 + x2 <= 25);
    
    // Set lower and upper bounds for the columns (variables)
    mip.colLowerBound(x1, 0);
    mip.colUpperBound(x2, 10);
    
    // Set the type of the columns
    mip.colType(x1, Mip::INTEGER);
    mip.colType(x2, Mip::REAL);
    
    // Specify the objective function
    mip.max();
    mip.obj(5 * x1 + 3 * x2);
    
    // Solve the problem using the underlying MIP solver
    mip.solve();
    
    // Print the results
    if (mip.type() == Mip::OPTIMAL) {
        std::cout << "Objective function value: " << mip.solValue() << std::endl;
        std::cout << "x1 = " << mip.sol(x1) << std::endl;
        std::cout << "x2 = " << mip.sol(x2) << std::endl;
    } else {
        std::cout << "Optimal solution not found." << std::endl;
    }
    
    return 0;
}