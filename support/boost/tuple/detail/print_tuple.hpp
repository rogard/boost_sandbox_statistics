//////////////////////////////////////////////////////////////////////////////
//  Boost.Assign v2                                                         //
//                                                                          //
//  Copyright (C) 2003-2004 Thorsten Ottosen                                //
//  Copyright (C) 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_TUPLE_DETAIL_PRINT_TUPLE_HPP_ER_2010
#define BOOST_TUPLE_DETAIL_PRINT_TUPLE_HPP_ER_2010
#include <ostream>
#include <tuple>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>

namespace er2010{

    template<int n, typename...Args>
    void print_tuple_impl(
        std::tuple<Args...> const& t,
        std::ostream& os,
        typename boost::disable_if_c<
            n < sizeof...(Args)
        >::type* = 0
    )
    {}

    template<int n, typename...Args>
    void print_tuple_impl(
        std::tuple<Args...> const& t,
        std::ostream& os,
        typename boost::enable_if_c<
            n < sizeof...(Args)
        >::type* = 0
    )
    {
        if( n > 0 ){ os << ", "; }
        os << std::get<n>( t );
        print_tuple_impl<(n + 1)>( t, os );
    }

    template<typename ...Args>
    void print_tuple( std::tuple<Args...> const& t,  std::ostream& os)
    {
        BOOST_STATIC_ASSERT((sizeof...(Args)==0));
        os << "()" << std::endl;
    }

    template<typename U, typename... Args>
    void print_tuple( std::tuple<U, Args...> const& t, std::ostream& os)
    {
        os
            << '(';
        print_tuple_impl<0>( t, os );
        os  << ')'
            << std::endl;
    }

}// er

#endif // BOOST_TUPLE_DETAIL_PRINT_TUPLE_HPP_ER_2010
