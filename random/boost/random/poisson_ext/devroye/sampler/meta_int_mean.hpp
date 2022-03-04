//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::devroye::sampler::meta_int_mean.hpp          		//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_SAMPLER_META_INT_MEAN_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_SAMPLER_META_INT_MEAN_HPP_ER_2010
#include <boost/math/policies/policy.hpp>
#include <boost/random/poisson_ext/devroye/detail/step4/choose.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  
namespace sampler{

	// Selects one of two versions, standard or squeeze, of Devroye's 
    // algorithm for sampling from the poisson with an integer mean.
	//
	// Example :
    // #include <boost/random/poisson_ext/detail/step4/squeeze.hpp
    // meta_int_mean<tag::squeeze>::type poisson(mean);
    //
    // Requirements : see comments inside /step4/*.hpp.
    template<typename Tag,typename Int = int,typename T = double,
    	typename P = boost::math::policies::policy<> >
    struct meta_int_mean : detail::step4::choose<Tag,Int,T,P>{};
    
}// sampler    
}// devroye
}// poisson
}// random
}// boost

#endif

