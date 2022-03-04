///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::tag::entry_time.hpp                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_TAG_ENTRY_TIME_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_TAG_ENTRY_TIME_HPP_ER_2009
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/name.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/statistics/detail/traits/remove_cvref.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{
namespace tag{
    struct entry_time{};
}
namespace meta{

	template<typename Map>
	struct entry_time 
    	: statistics::detail::traits::remove_cvref<
        	typename boost::fusion::result_of::at_key<
            	Map,
                tag::entry_time
            >::type
        >{};
            
}
}// record
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif
