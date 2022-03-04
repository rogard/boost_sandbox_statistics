//////////////////////////////////////////////////////////////////////////////
// statistics::detail::data::test::framework.cpp        					//
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#include <boost/statistics/detail/data/field/framework/fields/create.hpp>
#include <boost/statistics/detail/data/field/estimation/fields/include.hpp>
#include <libs/statistics/detail/data/test/framework.h>


void test_framework(std::ostream& os){
	os << "test_framework " << std::endl;
    
    typedef int val_;
    
	namespace data = boost::statistics::detail::data;    

    typedef data::field::keyword::estimate k_;
    typedef data::field::estimate<>::type m_;

	k_();
    m_();
    
	os << std::endl;
}
