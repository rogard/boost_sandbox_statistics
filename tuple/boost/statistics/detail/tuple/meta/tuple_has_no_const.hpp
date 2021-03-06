///////////////////////////////////////////////////////////////////////////////
// statistics::detail::tuple::meta::tuple_has_no_const.hpp                   //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_TUPLE_META_IS_TUPLE_HAS_NO_CONST_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_TUPLE_META_IS_TUPLE_HAS_NO_CONST_HPP_ER_2009
#include <boost/statistics/detail/tuple//meta/detail/tuple_has_no.hpp>
#include <boost/statistics/detail/tuple//meta/tuple_element_is_const.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace tuple{
namespace meta{
    
    template<typename T>
    struct tuple_has_no_const 
        : detail::tuple_has_no<T,tuple_element_is_const>{};

}// meta
}// tuple
}// detail
}// statistics

#endif