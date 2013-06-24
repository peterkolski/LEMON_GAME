//
//  ArgParser_Tester.cpp
//  MinimalNetGet
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 14.02.12.
//  Copyright (c) 2012 Peter A. Kolski.
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <lemon/arg_parser.h>

using namespace lemon;
using namespace std;

int main(int argc, char **argv){

    // --- Create parser
    ArgParser   ap( argc, argv );

    // --- Values to be set
    string fileString;
    double dblVal = 0.1;
    int     intVal = 39;
    
    // --- Set values
    ap.refOption("file", "Filename. Creates a LGF, EdgeList and analysis output", fileString, true);
    
    
    // ----- Perform parsing. Catch exceptions. ------
    try {
        ap.parse();
    } catch (ArgParserException &) {
        return 1;
    }

    stringstream    ss;
    ss << dblVal;
    string fsLFG        = fileString + "_LEMON_" + ss.str() + ".lgf";
    ss << intVal;
    string fsAnalyse    = fileString + "_Analysis_" + ss.str() + ".txt";
    ss.str("");
    ss << intVal;
    string fsEdgeList   = fileString + "_EdgeList_" + ss.str() + ".txt";

    cout << fsLFG       << endl;
    cout << fsAnalyse   << endl;
    cout << fsEdgeList  << endl;
    ifstream fileOne( fileString.c_str() );
    ifstream fileTwo( fsLFG.c_str() );
    
    fileOne.close();
    fileTwo.close();
    
}