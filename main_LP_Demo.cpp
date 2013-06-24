//
//  main_Demo.cpp
//  MinCostFlow_LEMON
//
//  Created by Peter A. Kolski (BildPeter Visuals) A. Kolski on 08.07.11.
//  Copyright (c) 2011 Peter A. Kolski.
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
 *
 * This demo program shows how the LEMON LP solver interface can be used. 
 * A simple linear programming (LP) problem is formulated and solved 
 * using the default LP solver (e.g. GLPK).
 *
 */


#include <iostream>
#include <lemon/lp.h>

using namespace lemon;
0
int main()
{
    // Create an instance of the default LP solver class
    // (it will represent an "empty" problem at first)
    Lp lp;
    
    // Add two columns (variables) to the problem
    Lp::Col x1 = lp.addCol();
    Lp::Col x2 = lp.addCol();
    
    // Add rows (constraints) to the problem
    lp.addRow(x1 - 5 <= x2);
    lp.addRow(0 <= 2 * x1 + x2 <= 25);
    
    // Set lower and upper bounds for the columns (variables)
    lp.colLowerBound(x1, 0);
    lp.colUpperBound(x2, 10);
    
    // Specify the objective function
    lp.max();
    lp.obj(5 * x1 + 3 * x2);
    
    // Solve the problem using the underlying LP solver
    lp.solve();
    
    // Print the results
    if (lp.primalType() == Lp::OPTIMAL) {
        std::cout << "Objective function value: " << lp.primal() << std::endl;
        std::cout << "x1 = " << lp.primal(x1) << std::endl;
        std::cout << "x2 = " << lp.primal(x2) << std::endl;
    } else {
        std::cout << "Optimal solution not found." << std::endl;
    }
    
    return 0;
}