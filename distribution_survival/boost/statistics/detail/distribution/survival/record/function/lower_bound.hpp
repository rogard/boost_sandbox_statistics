///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::function::lower_bound.hpp                 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_FUNCTION_LOWER_BOUND_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_FUNCTION_LOWER_BOUND_HPP_ER_2009
#include <algorithm>
#include <boost/fusion/include/make_map.hpp>
#include <boost/statistics/detail/distribution/survival/record/function/lower_bound.hpp>
#include <boost/statistics/detail/distribution/survival/record/function/less_than.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{
	
	template<typename It,typename T>
    It lower_bound(It b,It e,const T& time_analysis)
    {
    	typedef record::tag::entry_time tag_;
    	return std::lower_bound(
            b,
            e,
            boost::fusion::make_map<tag_>( time_analysis ),
            record::less_than()
        );
    }

}// record                
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif