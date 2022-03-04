/////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::right_truncated::is_right_truncated.hpp 	   //
//                                                                                 //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                      //
//  Software License, Version 1.0. (See accompanying file                          //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)               //
/////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_IS_RIGHT_TRUNCATED_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_IS_RIGHT_TRUNCATED_HPP_ER_2009
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/event.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace response {
namespace meta{

	template<typename S>
	struct is_event : boost::mpl::bool_<false>{};

    template<typename T,typename B>
    struct is_event< event<T,B> > : boost::mpl::bool_<true>{};
    
}// meta
}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif


