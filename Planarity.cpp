//
//  Planarity.cpp
//  MinimalNetGet
//
//  Created by BildPeter Visuals on 07.02.12.
//  Copyright (c) 2012 BildPeter Visuals. All rights reserved.
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
