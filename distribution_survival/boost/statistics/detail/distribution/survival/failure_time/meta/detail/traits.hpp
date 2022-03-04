///////////////////////////////////////////////////////////////////////////////
// distribution::survival::failure_time::meta::distribution.hpp       		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_DETAIL_TRAITS_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_DETAIL_TRAITS_HPP_ER_2009
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/statistics/detail/traits/remove_cvref.hpp>
#include <boost/statistics/detail/distribution/model/tag/covariate.hpp>
#include <boost/statistics/detail/distribution/model/tag/model.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/meta/is_survival_model.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace failure_time{
namespace detail{

	template<typename Map>
    struct traits
    {
    	typedef model::tag::covariate tag_x_;
    	typedef model::tag::model tag_m_;
        
        typedef typename 
        	boost::fusion::result_of::at_key<tag_x_,Map>::type cref_x_;
        typedef typename 
        	boost::fusion::result_of::at_key<tag_m_,Map>::type cref_m_;

		typedef typename statistics::detail::traits::remove_cvref<
        	cref_x_
        >::type covariate_type;
		typedef typename statistics::detail::traits::remove_cvref<	
        	cref_m_
        >::type model_type;
    };
    
}// detail
}// failure_time
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif


