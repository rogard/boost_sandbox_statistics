////////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::right_truncated::meta_factory.hpp 		  //
//                                                                            //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                 //
//  Software License, Version 1.0. (See accompanying file                     //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)          //
////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_META_MAKE_RESPONSE_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_META_MAKE_RESPONSE_HPP_ER_2009
#include <boost/mpl/identity.hpp> 
#include <boost/statistics/detail/distribution/survival/response/common/meta_factory.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/event_factory.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace response {
namespace meta{

    template<typename T,typename B>
    struct factory< event<T,B> > : boost::mpl::identity< event_factory<T,B> >{};
    
}// meta
}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif