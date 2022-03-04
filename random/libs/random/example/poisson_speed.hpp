///////////////////////////////////////////////////////////////////////////////
// random::example::poisson_speed.cpp     						     		 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/timer.hpp>

#include <boost/random/poisson_distribution.hpp>
#include <boost/random/poisson_ext/devroye/detail/step4/standard.hpp>
#include <boost/random/poisson_ext/devroye/detail/step4/squeeze.hpp>
#include <boost/random/poisson_ext/devroye/sampler/meta_int_mean.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

template<typename Int>
void example_poisson_speed(
	std::ostream& os,
    std::size_t n, 			//sample size
    int n_loops,
    int mean,		
    int factor 			// mean *= factor at each loop
){
	os << "poisson_speed{" << std::endl;

	namespace devroye = boost::random::poisson::devroye;
	typedef boost::timer timer_;
    typedef Int 	int_;
    typedef double 	val_;
    timer_ timer;
	typedef boost::mt19937 urng_;
    typedef boost::poisson_distribution<int_> random1_;
    typedef devroye::tag::standard tag3_;
    typedef devroye::tag::squeeze tag4_;
    typedef typename devroye::sampler::meta_int_mean<tag3_,int_>::type random3_;
    typedef typename devroye::sampler::meta_int_mean<tag4_,int_>::type random4_;
    
    urng_ urng;
	urng_ urng1 = urng;
    urng_ urng3 = urng;
    urng_ urng4 = urng;

	typedef boost::variate_generator<urng_&,random1_> vg1_;
	typedef boost::variate_generator<urng_&,random3_> vg3_;
	typedef boost::variate_generator<urng_&,random4_> vg4_;

	val_ t1, t3, t4 = 0;
	os << "n = " << n << std::endl;
	os << "(mean,{time[j] : j = default,devroye-st,devroye-sq})" << std::endl;
	for(int_ i1 = 0; i1<n_loops; ++i1){
		vg1_ vg1(urng1,random1_(mean));
		vg3_ vg3(urng3,random3_(mean));
		vg4_ vg4(urng4,random4_(mean));

        for(int_ i2 = 0; i2<n; i2++){
            timer.restart(); vg1();	t1 += timer.elapsed();
            timer.restart(); vg3();	t3 += timer.elapsed();
            timer.restart(); vg4();	t4 += timer.elapsed();
        }
        mean *= factor;
        os 
        	<< '(' 
            << mean
            << ',' 
            << t1 
            << ',' 
            << t3 
            << ',' 
            << t4
            << ')' 
            << std::endl;
    }

	os << "}" << std::endl;

}

