//
//  Boost_Accumulators.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 30.11.12.
//  Copyright (c) 2012 Peter A. Kolski. All rights reserved.
//

#include <lemon/random.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>

#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/density.hpp>

using namespace std;
using namespace boost;
using namespace boost::accumulators;
using namespace lemon;

/*
    HINWEIS:
        Bei den Features des Accumulators:
        tag::mean
        tag::variance
        
        Für Density (Histogramm):
        tag::density::num_bins
        tag::density::cache_size
        -   Cache greift am Anfang diese Zahl an Elementen heraus, um daraus die
            Bin-Größe und Aufteilung abzuschätzen
 */


typedef  accumulator_set<double, features<  tag::mean,
                                            tag::variance,
                                            tag::count,
                                            tag::density> > meanType;

typedef iterator_range< vector< pair<double, double>>::iterator > histogram_type;

int main( void ){

    // --- set random vector
    vector<double>      data(400);
    for( double &val : data ){
        val = rnd.integer( 40 );
    }
    
    // --- accumulator instance
    meanType    acc2(   tag::density::num_bins = 100,
                        tag::density::cache_size = 100);
    
    // --- push the values
    for( double &val : data )
        acc2( val );
    
    // ------------------ EASY OUTPUT
    // -- mean & variance
    cout << mean( acc2 ) << endl;
    cout << variance( acc2 ) << endl;
    cout << accumulators::count( acc2 ) << endl;
    cout << endl;
    
    // ----------------- HISTOGRAMM
    histogram_type      mHisto = density( acc2 );
    int i = 0;
    auto last = mHisto.end()-1;
    for( auto val : mHisto ){
        cout << i++ << " : \t" << val.first << " \t: "<< val.second << endl;
    }
    
    cout << endl << (*(mHisto.end() - 1)).first;
    
}