//////////////////////////////////////////////////////////////////////////////////
// statistics::survival::response::right_truncated::detail::logit_log.hpp 		//
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_LOGIT_LOG_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_LOGIT_LOG_HPP_ER_2009
#include <boost/statistics/detail/math/function/log_shift.hpp>
#include <boost/statistics/detail/math/function/logit_shift.hpp>
#include <boost/statistics/detail/survival/response/right_truncated/mean.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace survival{
namespace response{

template<typename T0,typename T1,typename T,typename B,typename ItO>
ItO logit_log_shift(
    const T0& c0,
    const T1& c1,
    const mean_event<T,B>& m, 
    ItO o
)
{
    (*o++) = statistics::detail::math::logit_shift(m.failure_time(),c0);
    (*o++) = statistics::detail::math::log_shift(m.entry_time(),c1);
    return o;
}

template<typename T0,typename T,typename B,typename ItO>
ItO logit_log_shift(
    const T0& c0,
    const mean_event<T,B>& m, 
    ItO o
)
{
    return logit_log(c0,c0,m,o);
}

}// response
}// survival
}// statistics
}// boost

#endif