//////////////////////////////////////////////////////////////////////////////
// statistics::detail::data::example::blocking.cpp        					//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/type_traits.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/include/at_key.hpp>

#include <boost/statistics/detail/data/adapt_fusion/estimation/input.hpp>
#include <boost/statistics/detail/data/field/framework/include.hpp>
#include <boost/statistics/detail/data/field/estimation/include.hpp>
#include <boost/statistics/detail/data/field/survival/fields/include.hpp>
#include <boost/statistics/detail/data/field/estimation/fields/include.hpp>

#include <libs/statistics/detail/data/example/blocking.h>

void example_blocking(std::ostream& os)
{
	os << "example_blocking: " << std::endl; 

	namespace stat = boost::statistics::detail; 
    namespace data = stat::data;

    namespace kwd = data::keyword;
    typedef data::field::float_valued::input fx_; 

	fx_ fx((data::_input = 1)); 
	data::field_value<fx_::key_type>(fx); 
    boost::fusion::at_key<fx_::key_type>(fx); 

	typedef boost::fusion::result_of::at_key<const fx_,fx_::key_type>::type result_;
	typedef const double& expected_;
    typedef boost::is_same<result_,expected_> same_;
    BOOST_STATIC_ASSERT(same_::value);

	os << std::endl;
}
