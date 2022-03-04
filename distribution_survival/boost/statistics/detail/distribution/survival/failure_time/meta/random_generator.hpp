///////////////////////////////////////////////////////////////////////////////
// distribution::survival::failure_time::meta::random_generator.hpp        	 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_RANDOM_GENERATOR_N_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_RANDOM_GENERATOR_N_HPP_ER_2009
#include <boost/utility/enable_if.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/random_distribution.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/detail/traits.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace failure_time{

	template<typename M,typename U>
    struct random_generator{
    
        typedef typename failure_time::random_distribution<M>::type r_ft_;
        typedef boost::variate_generator<U&,r_ft_> type;
        
        template<typename X>
        static type call(const X& x,const M& m, U& urng)
        {
            return type(
                urng,
                failure_time::make_random_distribution( x, m )
            );            
        }
    };

	template<typename X,typename M,typename U>
	typename random_generator<M,U>::type
    make_random_generator(const X& x,const M& model,U& urng)
    {
    	typedef random_generator<M,U> meta_;
		return meta_::call(x,model,urng);
    }

	template<typename Map,typename U>
	typename random_generator<
        typename detail::traits<Map>::model::type,
        U
    >::type
    make_random_generator(const Map& map,U& urng)
    {
    	typedef typename detail::traits<Map>::model::type model_;
    	typedef random_generator<model_,U> meta_;
		return meta_::call(map,urng);
    }
	    
}// failure_time
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif