///////////////////////////////////////////////////////////////////////////////
// statistics::detail::tuple::meta::is_tuple.hpp                             //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_TUPLE_META_IS_TUPLE_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_TUPLE_META_IS_TUPLE_HPP_ER_2009
#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace tuple{
namespace meta{
    
    template<typename T>
    struct is_tuple : mpl::bool_<false>{};

    template<typename Head,typename Tail>
    struct is_tuple< boost::tuple<Head,Tail > > : mpl::bool_<true>{};

}// meta
}// tuple
}// detail
}// statistics

#endif