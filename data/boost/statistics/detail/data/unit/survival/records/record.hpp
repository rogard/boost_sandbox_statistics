//////////////////////////////////////////////////////////////////////////////
// data::unit::survival::records::record.hpp								//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_UNIT_SURVIVAL_RECORDS_RECORD_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_UNIT_SURVIVAL_RECORDS_RECORD_HPP_ER_2010
#include <boost/statistics/detail/data/field/survival/fields/entry_time.hpp>
#include <boost/statistics/detail/data/field/survival/fields/failure_time.hpp>
#include <boost/statistics/detail/data/unit/framework/impl.hpp>
 
namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace unit{	
namespace survival{

    // This is probably the most common form of record
    typedef data::unit::impl<
        field::float_valued::entry_time,
        field::float_valued::failure_time
    > record;        
    
}// unit
}// data
}// detail
}// statistics
}// boost                

#endif
