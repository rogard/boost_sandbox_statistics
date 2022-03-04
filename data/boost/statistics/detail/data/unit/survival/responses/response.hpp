//////////////////////////////////////////////////////////////////////////////
// data::unit::survival::responses::response.hpp							//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_UNIT_SURVIVAL_RESPONSES_RESPONSE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_UNIT_SURVIVAL_RESPONSES_RESPONSE_HPP_ER_2010
#include <boost/statistics/detail/data/field/survival/fields/is_failure.hpp>
#include <boost/statistics/detail/data/field/survival/fields/event_time.hpp>
#include <boost/statistics/detail/data/unit/framework/impl.hpp>
 
namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace unit{	
namespace survival{

    typedef data::unit::impl<
        field::is_failure,
        field::float_valued::event_time
    > response;        
	
}// unit
}// data
}// detail
}// statistics
}// boost                

#endif
