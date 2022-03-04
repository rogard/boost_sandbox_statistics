////////////////////////////////////////////////////////////////////////////////
// distribution::survival::failure_time::meta::random_distribution.hpp 	      //
//                                                                            //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                 //
//  Software License, Version 1.0. (See accompanying file                     //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)          //
////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_RANDOM_DISTRIBUTION_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_FAILURE_TIME_META_RANDOM_DISTRIBUTION_HPP_ER_2009
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp> 
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/is_event.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/detail/traits.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/distribution.hpp>
#include <boost/statistics/detail/distribution_common/meta/random/distribution.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace failure_time{

    // Returns a model of RandomDistribution
    // See http://www.boost.org/doc/libs/1_40_0/libs/random/random-concepts.html
    template<typename Model>
    struct random_distribution
    {
        typedef failure_time::distribution<Model> meta_;
        typedef typename meta_::type dist_;
        typedef typename distribution::meta::random_distribution<dist_> meta1_;
        typedef typename meta1_::type type;
        
        template<typename X>
        static type call(const X& x,const Model& m)
        {
            return distribution::make_random_distribution( meta_::call(x,m) ); 
        }
    };

	template<typename X,typename M>
    typename random_distribution<M>::type
    make_random_distribution(const X& x,const M& m)
    {
        typedef random_distribution<M> meta_;
        return meta_::call(x,m);
    }

	template<typename Map>
    typename random_distribution<
    	typename detail::traits<Map>::model::type
    >::type
    make_random_distribution(const Map& map)
    {
    	typedef model::tag::covariate tag_x_;
    	typedef model::tag::model tag_m_;
    	typedef typename detail::traits<Map>::model::type model_;
        typedef random_distribution<model_> meta_;
        return meta_::call(
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