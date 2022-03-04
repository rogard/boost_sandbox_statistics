//////////////////////////////////////////////////////////////////////////////
// data::unit::framework::impl.hpp         									//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_UNIT_FRAMEWORK_IMPL_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_UNIT_FRAMEWORK_IMPL_HPP_ER_2010
#include <boost/mpl/empty_base.hpp>
#include <boost/serialization/detail/inherit/inherit_linearly.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace unit{

	// Maps the types of n fields, T1,...,Tn to a type suitable to represent
    // a data unit.
    //
    // The word unit is short for observational unit.
    // http://en.wikipedia.org/wiki/Unit_of_observation

    template<typename BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_VECTOR_SIZE, class T)>
    struct meta
    {
    
    	typedef boost::mpl::vector<BOOST_PP_ENUM_PARAMS(n,T)> components;
    
		typedef serialization::detail::inherit_linearly<types> type
    }; 

    
}// unit
}// data
}// detail
}// statistics
}// boost                

#endif