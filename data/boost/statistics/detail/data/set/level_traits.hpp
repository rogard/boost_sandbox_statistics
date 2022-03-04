//////////////////////////////////////////////////////////////////////////////
// data::set::levels_traits.hpp         									//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_SET_LEVEL_TRAITS_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_SET_LEVEL_TRAITS_HPP_ER_2010
#include <boost/statistics/detail/data/types/array/array_traits.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{

	// An often convenient and efficient way to represent K input levels is
    // as a array of fields of static size (K).  
	template<int K, typename F = field::x>
    struct level_traits : array_traits<F,K>{};

}// data
}// detail
}// statistics
}// boost

#endif




