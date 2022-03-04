///////////////////////////////////////////////////////////////////////////////
// mpl::rest.hpp                              				 				 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_MPL_REST_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_MPL_REST_HPP_ER_2010
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace mpl{

	template<typename Seq>
    struct rest : boost::mpl::iterator_range<
        typename boost::mpl::next<
            typename boost::mpl::begin<Seq>::type
        >::type,
        typename boost::mpl::end<Seq>::type
    >{};
    
}// mpl
}// detail
}// statistics
}// boost

#endif

