//////////////////////////////////////////////////////////////////////////////
// importance_sampling::doc::readme                                         //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////

[ Contact ]

er.ci.2020 at gmail.com

[ Overview ]

These are C++ tools for computing importance weights and sampling.

The classes prepare_weights followed by sampler cover most needs.

[ Note ]

To ensure that the draws are from the desired target distribution, we recommend
monitoring
a) The effective sample size (ESS) 
b) The uniformity of the Cook-Gelman statistics. The latter may be violated by
either i) too small a ESS ii) incorrect computations

[ Platform/Compiler ]

Tested January 20th 2010 
Mac OS X 10.6        gcc 4.0                                    boost_1_41_0
Note: gcc 4.2 and boost::format recently don't mix well.

As of November 1st 2009: 
Win7-32 V6.1.7100    Dev-C++ 5.0 beta 9.2 with Mingw/GCC 3.4.2 	boost_1_41_0


[ Dependencies ]

/usr/local/boost_1_40_0/ 
/Users/erwann/sandbox/statistics/detail/accumulator/
/Users/erwann/sandbox/statistics/detail/fusion/ 
/Users/erwann/sandbox/statistics/non_parametric/ 
/Users/erwann/sandbox/statistics/random/ 
/Users/erwann/sandbox/statistics/distribution_common/ 
/Users/erwann/sandbox/statistics/distribution_toolkit/

[ Sources ]

[1] http://en.wikipedia.org/wiki/Multinomial_distribution

[2] http://en.wikipedia.org/wiki/Particle_filter

[3] A note on Importance Sampling using standardized weights, Augustine Kong,
Technical report 348, Department of statistics, UChicago, 1992.

[4] Bayesian analysis of massive datasets via particle filters,
Ridgeway and Madigan

[5] Andrew Gelman et al., Bayesian Data Analysis, CRC Press

[ History ]

January 20th 2010 
	Changes to sampler.cpp to due those in changes in non_parametric/kolmogorov_statistic

November 1st 2009: 
    Removed computations of ess and pc_lt_eps from prepare_weights. In their
    place, have created standalone accumulators.

October 11 2009:
    Merged importance_sampling and importance_weights, and embedded it in 
    namespace statistics::detail

Sep    3  2009 : 
    - replaced is:: by statistics::importance_sampling
    - modified the interface of generate_n
    
August 18 2009 : refactored sampler to use discrete_distribution, no longer 
    categorical_distribution
    
July 2009 : First version

[ Output ]

Ouput of main.cpp:

->example_sampler : 
weights : 
(offset,scaling_factor) = (99,1)
(ess,plt_eps) = (0.444955,0)
proposal : normal(0,1)
target : normal(1,0.707107)
kolmogorov_smirnov(n,s)
(10,0.306601)
(110,0.0819208)
(1110,0.0167257)
(11110,0.00736992)
(111110,0.00692354)
(1111110,0.00604868)
(11111110,0.00637739)
<-
-> example_algorithm_scale_sum_to_finite : val = 1.79769e+308
c = 13
cum_sum = 1.79769e+308
<-

[ Remarks ]

The last kolmogorov_smirnov value in the output above is slightly greater than 
its preceding one. This is probably due to numerical error, which can be 
resolved by increasing the number of proposals.

