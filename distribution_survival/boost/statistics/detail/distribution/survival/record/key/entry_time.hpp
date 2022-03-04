///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::key::entry_time.hpp                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_KEY_ENTRY_TIME_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_KEY_ENTRY_TIME_HPP_ER_2009
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/name.hpp>
#include <boost/statistics/detail/distribution/survival/record/tag/entry_time.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{
namespace keyword{
    namespace 
    {
        boost::parameter::keyword<tag::entry_time>& entry_time
            = boost::parameter::keyword<tag::entry_time>::get();
    }
}// keyword
}// record
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif
