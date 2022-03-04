//////////////////////////////////////////////////////////////////////////////
// data::types::array::array_traits.hpp         							//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_TYPES_ARRAY_ARRAY_TRAITS_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_TYPES_ARRAY_ARRAY_TRAITS_HPP_ER_2010
#include <boost/parameter/name.hpp>
#include <boost/parameter/keyword.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{

	// E stands for "element". Generally a field or a data::unit.
	template<typename E,int N>
	struct array_traits{
    	typedef E elem_;
    	typedef boost::array<E,N> storage_;
        typedef typename boost::add_reference<storage_>::type ref_storage_;
        typedef typename boost::add_const<ref_storage_>::type cref_storage_;
    	typedef typename boost::range_iterator<storage_>::type it_;
    	typedef typename boost::range_iterator<const storage_>::type cit_;
	};


}// data
}// detail
}// statistics
}// boost

#endif


