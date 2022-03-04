///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::less_than.hpp                       		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_LESS_THAN_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_LESS_THAN_HPP_ER_2009
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/entry_time.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{

    struct less_than{
        typedef bool result_type;
        less_than(){}
        template<typename M,typename M1>
        result_type operator()(const M& m, const M1& m1)const
        {
            return boost::fusion::at_key<tag::entry_time>(m)
            	< boost::fusion::at_key<tag::entry_time>(m1);
        }
    };

}// record                
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif