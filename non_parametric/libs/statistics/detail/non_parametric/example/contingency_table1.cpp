///////////////////////////////////////////////////////////////////////////////
// contingency_table1.cpp                                                    //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include <string>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/container/map/detail/sequence_to_map.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/include/factor.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/include/cells.hpp>

#include <boost/statistics/detail/non_parametric/contingency_table/include/pearson_chisq/independence.hpp>

#include <libs/statistics/detail/non_parametric/example/contingency_table1.h>

void example_contingency_table1()
{
	namespace ct = boost::statistics::detail::contingency_table;

    typedef double val_;
    typedef boost::mpl::int_<0> x_; typedef int data_x_;
    typedef boost::mpl::int_<1> y_; typedef std::string data_y_;
    typedef boost::mpl::int_<2> z_; typedef int data_z_;
 
    typedef boost::fusion::detail::sequence_to_map<
        boost::mpl::vector6<x_,data_x_,y_,data_y_,z_,data_z_>
    >::type sample_;
    
    typedef boost::mpl::vector1<x_> keys_; //,y_> keys_;
    typedef ct::tag::cells<keys_> cells_;
    typedef boost::accumulators::stats< cells_> stats_;
    typedef boost::accumulators::accumulator_set< sample_, stats_, long int > acc_;
        
    using namespace boost::assign;
    acc_ acc(( ct::_map_of_levels = boost::fusion::make_map<x_>(
        list_of(-1)(1) ) ));
    
    {
     	BOOST_ASSERT( ct::extract::levels<x_>( acc ).count( -1  ) == 1 );
    }
    {
        ct::extract::levels<x_>( acc ).begin();
    }
    {
        ct::initialize<keys_>( acc );
    }
    {
        using namespace boost::accumulators;
        //acc( boost::fusion::make_map<x_>( -1 ), weight = 0 );
    }
    
    long n1 = ct::cells_count<keys_>( acc );
    long n2 = ct::cells<keys_>( acc ).size();
    
    std::cout << '(' << n1 << ',' << n2 << ')';
    
//    BOOST_ASSERT( ct::cells_count<keys_>(acc) == ct::cells<keys_>( acc ).size() );

}
