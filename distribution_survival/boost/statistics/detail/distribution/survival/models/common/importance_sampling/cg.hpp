//////////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::importance_sampling::cg.hpp 					//
//                                                                           	//
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                	//
//  Software License, Version 1.0. (See accompanying file                    	//
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         	//
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_CG_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_CG_HPP_ER_2009
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/statistics/detail/accumulator/statistics/proportion_less_than.hpp>
#include <boost/statistics/detail/importance_sampling/statistics/percentage_effective_sample_size.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{

	// cook-gelman statistic
    template<typename It_t,typename T>
    T cg(It_t b_target,It_t e_target,const T& threshold){
                
        typedef accumulator::tag::proportion_less_than tag_plt_; 
        typedef boost::accumulators::stats<tag_plt_> stats_;
        typedef boost::accumulators::accumulator_set<T,stats_> acc_; 
        acc_ a = std::for_each(
            b_target,
            e_target,
            acc_(( accumulator::keyword::threshold = threshold ))
        );
		return boost::accumulators::extract_result<tag_plt_>(a);
	}
    
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif