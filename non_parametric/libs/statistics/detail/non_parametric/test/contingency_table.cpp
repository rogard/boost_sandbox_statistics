///////////////////////////////////////////////////////////////////////////////
// contingency_table.cpp                                                     //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <libs/statistics/detail/non_parametric/test/contingency_table1.cpp>
#include <libs/statistics/detail/non_parametric/test/contingency_table2.cpp>

using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE(" Contingency Table Test Suite ");
    test->add ( BOOST_TEST_CASE( &test_contingency_table1 ) );
    test->add ( BOOST_TEST_CASE( &test_contingency_table2 ) );
    
    return test;

}
