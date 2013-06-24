//
//  Boost_Histogramm.cpp
//  LEMON_GAME
//
//  Created by Peter A. Kolski (BildPeter Visuals) on 30.11.12.
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


#include <vector>
#include <algorithm>
#include <iostream>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/stats.hpp>

using namespace boost;
using namespace boost::accumulators;

typedef accumulator_set<double, features<tag::density> > acc;
typedef iterator_range<std::vector<std::pair<double, double> >::iterator > histogram_type;

template <typename T>
class data_filler
{
public:
    data_filler(){}
    T operator()() { return rand()/(T)RAND_MAX; }
};

int main(int argc, char** argv)
{

    //create some random data
    std::vector<double> data(100);
    std::generate(data.begin(), data.end(), data_filler<double>());
    int c = data.size();//cache size for histogramm.
    
    //create an accumulator
    acc myAccumulator( tag::density::num_bins = 100, tag::density::cache_size = 10);
    
    //fill accumulator
    for (int j = 0; j < c; ++j)
    {
        myAccumulator(data[j]);
    }
    
    histogram_type hist = density(myAccumulator);
    
    double total = 0.0;
    
    for( int i = 0; i < hist.size(); i++ )
    {
        std::cout << "Bin lower bound: " << hist[i].first << ", Value: " << hist[i].second << std::endl;
        total += hist[i].second;
    }
    
    std::cout << "Total: " << total << std::endl; //should be 1 (and it is)
    
    return 0;
}