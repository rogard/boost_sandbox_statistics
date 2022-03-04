//////////////////////////////////////////////////////////////////////////////
// data::field::survival::function::elapsed_time.hpp         				//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_FUNCTION_ELAPSED_TIME_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_FUNCTION_ELAPSED_TIME_HPP_ER_2010
#include <boost/statistics/detail/data/field/framework/function/field_value.hpp>
#include <boost/statistics/detail/data/field/survival/fields/entry_time.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace field{	

	// Beware that this value may be <0
	template<typename T,typename T1>
	T elapsed_time(
    	const typename field::meta::entry_time<T>::type& f,
        const T1& time
    ){
    	return time - <data::keyword::entry_time>(f);
    }

}// field
}// data
}// detail
}// statistics
}// boost                

#endif

