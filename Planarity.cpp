//
//  Planarity.cpp
//  MinimalNetGet
//
//  Created by Peter A. Kolski  (BildPeter Visuals) on 07.02.12.
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

#include <lemon/planarity.h>
#include <lemon/full_graph.h>
#include <lemon/list_graph.h>

using namespace lemon;
using namespace std;

int main(){

    FullGraph mGraph    ( 3 );
    ListGraph mListGr;
    
    DigraphCopy< FullGraph, ListGraph > dc( mGraph, mListGr );
    dc.run();
    
//    mListGr.clear();

    cout << countNodes( mGraph ) << endl;
    cout << countNodes( mListGr ) << endl;

//    PlanarDrawing< ListGraph > mDrawer( mListGr );
//    mDrawer.run();

}
