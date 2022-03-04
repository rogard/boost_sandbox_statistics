//////////////////////////////////////////////////////////////////////////////////
// survival::src::main.cpp                                                      // 
//																				//
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/statistics/detail/math/constant/shortcut.hpp>
#include <libs/statistics/detail/distribution/survival/test/model/functions.cpp>
#include <libs/statistics/detail/distribution/survival/example/data/dataset.h>
#include <libs/statistics/detail/distribution/survival/example/data/random.h>
#include <libs/statistics/detail/distribution/survival/example/models/exponential.h>

int main()
{
    //test_model_functions<double>(std::cout);
    //example_data_dataset(std::cout);
    //example_data_random(std::cout);
    typedef boost::statistics::detail::math::constant::shortcut<double> const_;
    example_model_exponential(
        // TODO n_bath should be deduced from input (getline)
        5e4,            // runs,  
        1e2,            // records   
        1e3,            // n_mod
        1e4,            // proposals 
        1e4,            // targets  
        const_::inf,    // time of analysis
        "/Users/erwann/projets/2009/Xcode/distribution_survival/build/", // path 
        std::cout
    );

    return 0;
}


