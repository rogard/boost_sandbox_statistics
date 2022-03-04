//////////////////////////////////////////////////////////////////////////////////
// survival::modelss::exponential::scalar::meta::failure_time_distribution.hpp 	//
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_META_FAILURE_TIME_DISTRIBUTION_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_META_FAILURE_TIME_DISTRIBUTION_HPP_ER_2009
#include <cmath>
#include <boost/math/distributions/exponential.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/exponential/is_math_distribution.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/exponential/random.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/distribution.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/model.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace failure_time{

    template<typename T,typename L>
    struct distribution< exponential_model<T,L> >
    {

        typedef exponential_model<T,L> model_;
        typedef boost::math::exponential_distribution<T> type;
        
        template<typename X>
        static type call(const X& x, const model_& mo){
            T lambda = mo.log_rate(x);
            lambda = exp( lambda );
            return type(
                lambda
            );
        }        
    };

}// failure_time
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif