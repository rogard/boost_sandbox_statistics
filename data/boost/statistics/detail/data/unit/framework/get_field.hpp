//////////////////////////////////////////////////////////////////////////////
// data::unit::framework::get_field.hpp         							//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_UNIT_FRAMEWORK_GET_FIELD_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_UNIT_FRAMEWORK_GET_FIELD_HPP_ER_2010
#include <boost/statistics/detail/data/field/framework/fields/impl.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{

namespace result_of{
	
    template<typename Tag,typename U>
    struct get_field{
        typedef U& type; //?
    };
    
}

	// Usage : field_value<Tag>(unit) 
	template<typename Tag,typename T>
	field::impl<Tag,T>& 
    get_field(data::field::impl<Tag,T>& f){ return f; }

}// data
}// detail
}// statistics
}// boost                

#endif
