//////////////////////////////////////////////////////////////////////////////
// data::unit::estimation::units::cross_validation.hpp						//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_UNIT_ESTIMATION_UNITS_CROSS_VALIDATION_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_UNIT_ESTIMATION_UNITS_CROSS_VALIDATION_HPP_ER_2010
#include <boost/statistics/detail/data/field/estimation/fields/estimate.hpp>
#include <boost/statistics/detail/data/field/estimation/fields/input.hpp>
#include <boost/statistics/detail/data/field/estimation/fields/output.hpp>
 
namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace unit{	
namespace estimation{

    typeded data::unit<
        field::float_valued::estimate,
        field::float_valued::input,
        field::float_valued::output
    > cross_validation;        

}// estimation
}// unit
}// data
}// detail
}// statistics
}// boost                

#endif
