
///////////////////////////////////////////////////////////////////////////////
// random::example::poisson_convergence.cpp     						     //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef LIBS_RANDOM_EXAMPLE_POISSON_CONVERGENCE_CPP_ER_2010
#define LIBS_RANDOM_EXAMPLE_POISSON_CONVERGENCE_CPP_ER_2010
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/mpl/int.hpp>

#include <boost/typeof/typeof.hpp>
#include <boost/ref.hpp>
#include <boost/range.hpp>

#include <boost/assign/std/vector.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>

#include <boost/math/distributions/poisson.hpp>
#include <boost/random/poisson_distribution.hpp>

#include <boost/random/poisson_ext/devroye/detail/step4/standard.hpp>
#include <boost/random/poisson_ext/devroye/detail/step4/squeeze.hpp>
#include <boost/random/poisson_ext/devroye/sampler/meta_int_mean.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/statistics/detail/non_parametric/kolmogorov_smirnov/check_convergence.hpp>

template<typename Int>
void example_poisson_convergence(
	std::ostream& os,
    double mean,
    std::size_t n_loops,
    std::size_t n_init,
    std::size_t n_factor
)
{

	namespace ks = boost::statistics::detail::kolmogorov_smirnov;
	namespace devroye = boost::random::poisson::devroye;

    typedef Int int_;
    typedef double 	val_;
    typedef boost::math::poisson_distribution<val_> dist_;
    typedef boost::poisson_distribution<int_> random1_;
    typedef devroye::tag::standard tag3_;
    typedef devroye::tag::squeeze tag4_;
    typedef typename devroye::sampler::template 
    	meta_int_mean<tag3_,int_>::type random3_;
    typedef typename devroye::sampler::template 
    	meta_int_mean<tag4_,int_>::type random4_;
    
	typedef boost::mt19937 urng_;
	typedef std::vector<val_> vals_;
	typedef ks::check_convergence<val_> check_;

    urng_ urng;
	urng_ urng1 = urng;
    urng_ urng2 = urng;
    urng_ urng3 = urng;
    urng_ urng4 = urng;
	check_ check;

	os  << "mean = " << mean << std::endl;
	{
    	typedef boost::variate_generator<urng_&,random1_> vg1_;
    	typedef boost::variate_generator<urng_&,random3_> vg3_;
    	typedef boost::variate_generator<urng_&,random4_> vg4_;
    	
        dist_ dist(mean);
        os << "default : " << std::endl;
        {
			vg1_ vg1(urng,random1_(mean));
    		check(n_loops,n_init,n_factor,dist,vg1,os);
        }
        os << "devroye - standard" << std::endl;
        {
        	random3_ r(mean);
			vg3_ vg(urng,r);
            vg();
    		check(n_loops,n_init,n_factor,dist,vg,os);
            //os << vg.distribution() << std::endl;
        }
        os << "devroye - squeeze" << std::endl;
        {
        	random4_ r(mean);
			vg4_ vg(urng,r);
    		check(n_loops,n_init,n_factor,dist,vg,os);
            //os << vg.distribution() << std::endl;
        }
    }
	os << "<-" << std::endl;

}

#endif
