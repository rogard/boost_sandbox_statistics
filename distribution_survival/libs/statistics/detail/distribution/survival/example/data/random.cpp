///////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::example::data::random.cpp                                     //
//                                                                                       //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                            //
//  Software License, Version 1.0. (See accompanying file                                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                     //
///////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string> //needed?
#include <algorithm>
#include <iterator>
#include <vector>

#include <boost/typeof/typeof.hpp>
#include <boost/range.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp> 
#include <boost/accumulators/accumulators.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/fusion/container/generation/make_map.hpp>
#include <boost/fusion/include/make_map.hpp>

#include <boost/statistics/detail/non_parametric/kolmogorov_smirnov/check_convergence.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/exponential/include.hpp>

#include <boost/statistics/detail/distribution/survival/record/key/include.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/include.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/include.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/include.hpp>

#include <libs/statistics/detail/distribution/survival/example/data/random.h>

void example_data_random(std::ostream& os)
{
    os << "-> example_data_random : " << std::endl;

    // Generate failure-time data randomly
    // Computes kolmogorov-smirnov statistics at various iterations to verify
    // convergence to the desired distribution

    using namespace boost;
    namespace stat = boost::statistics::detail;
    namespace ds = stat::distribution::survival;
    namespace dt = stat::distribution::toolkit;
    namespace dm = stat::distribution::model;
    namespace ks = stat::kolmogorov_smirnov;

    typedef ds::record::tag::entry_time     tag_et_;
    typedef ds::record::tag::failure_time   tag_ft_;
    typedef dm::tag::covariate          	tag_x_;
    typedef boost::mpl::int_<1>         	tag_cdf_;
    typedef mt19937                     	urng_;
    typedef double                      	val_;
    typedef ds::exponential_model<val_> 	m_;
    typedef ds::failure_time::distribution<m_>::type           d_;
    typedef ds::failure_time::random_distribution<m_>::type    r_;
    typedef boost::variate_generator<urng_&,r_>                g_;
	typedef ks::check_convergence<val_> check_;

    const int n_loops = 1.5e1;
    const int n_init = 2;
    const int n_factor = 2;

    urng_ urng;
    m_ m;
    val_ x = -1.0;
    val_ p = 1.0;
    m.set_parameter(p);
    d_ d = ds::failure_time::make_distribution( x, m );
    g_ g(
        urng,
        ds::failure_time::make_random_distribution( x, m )
    );
    
	check_ check;
    
    check(n_loops,n_init,n_factor,d,g,os);

}