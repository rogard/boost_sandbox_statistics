///////////////////////////////////////////////////////////////////////////////
// distribution::survival::failure_time::meta::distribution.hpp       		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_DISTRIBUTION_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_DISTRIBUTION_HPP_ER_2009
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/statistics/detail/distribution/model/tag/covariate.hpp>
#include <boost/statistics/detail/distribution/model/tag/model.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/detail/traits.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace failure_time{

    template<typename Model>
    struct distribution{
        // Specialize for each model. See below.    
    };
    
    template<typename X,typename Model>
	typename distribution<Model>::type
    make_distribution(const X& x,const Model& m)
    {
        typedef failure_time::distribution<Model> meta_;
        return meta_::call(x,m);
    }

	template<typename Map>
	typename distribution<
		typename failure_time::detail::traits<Map>::model_type
    >::type
    make_distribution(const Map& map)
    {
    	typedef model::tag::covariate tag_x_;
    	typedef model::tag::model tag_m_;
        return make_distribution(
        	boost::fusion::at_key<tag_x_>(map),
        	boost::fusion::at_key<tag_m_>(map)
        );
    }

}// failure_time
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif