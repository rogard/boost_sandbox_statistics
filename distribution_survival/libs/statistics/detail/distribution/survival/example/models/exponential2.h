////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::example::data::exponential2.h                              //
//                                                                                    //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                         //
//  Software License, Version 1.0. (See accompanying file                             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                  //
////////////////////////////////////////////////////////////////////////////////////////
#ifndef LIBS_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_EXAMPLE_MODEL_EXPONENTIAL2_H_ER_2009
#define LIBS_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_EXAMPLE_MODEL_EXPONENTIAL2_H_ER_2009
#include <string>
#include <ostream>

void example_model_exponential(
    long n_runs,                 // = 5e4; 
    long n_r,     // records     // = 
    long n_mod,                  // = 1e3;
    long n_p,     // proposals   // = 1e4; 
    long n_t,     // targets     // = 1e4;
    double time_analysis,          // = const_::inf_;
    std::string out_path,        // = "/Users/erwann/projets/2009/Xcode/survival/build/Release/
    std::ostream& out
);

#endif