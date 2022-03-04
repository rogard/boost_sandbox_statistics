///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::time_since_entry.hpp                		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_TIME_SINCE_ENTRY_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_TIME_SINCE_ENTRY_HPP_ER_2009
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/include/value_at_key.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/entry_time.hpp>
#include <boost/statistics/detail/traits/remove_cvref.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{

template<typename M,typename T>
typename traits::remove_cvref<
    typename boost::fusion::result_of::value_at_key<M,tag::entry_time>::type
>::type
time_since_entry(
    const M& m, 
    const T& t
)
{
    //Warning: does not check for < 0 (intentional)
    return (t - boost::fusion::at_key<tag::entry_time>(m));
}

}// record                
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif