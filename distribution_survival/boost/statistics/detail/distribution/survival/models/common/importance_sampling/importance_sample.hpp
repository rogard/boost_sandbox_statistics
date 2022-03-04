///////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::common::importance_sampling::sample.hpp   //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_IMPORTANCE_SAMPLE_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_IMPORTANCE_SAMPLE_HPP_ER_2009
#include <algorithm>
#include <boost/range.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/statistics/detail/importance_sampling/random/sampler.hpp>
#include <boost/statistics/detail/importance_sampling/weights/prepare_weights.hpp>
#include <boost/statistics/detail/fusion/at_key/range.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {

	// each elem of [b_p,e_p) is a fusion map with a pair tagged by TagPar
	template<
    	typename TagPar,
        typename It_t,typename N_t,typename It_p,typename V,typename U
    >
	It_t importance_sample(
    	It_t it_targets, 
        N_t n_targets,
        It_p b_p, 		// proposals 
        It_p e_p,
        const V& vec_w, // importance_weights
        U& urng
    )
    {    
        typedef typename boost::range_value<V>::type val_;
        typedef 
        	statistics::detail::fusion::at_key::meta_range<It_p,TagPar> meta_;
        typedef typename meta_::type r_;                
        typedef importance_sampling::sampler<r_,val_> sampler_;               
        sampler_ sampler(vec_w,meta_::call(b_p,e_p));
        typedef boost::variate_generator<U&,sampler_> vg_;
        vg_ vg(urng,sampler);
        return std::generate_n(it_targets, n_targets, vg );
	}
    
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif