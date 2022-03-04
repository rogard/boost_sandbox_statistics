///////////////////////////////////////////////////////////////////////////////
// mpl::example::rest.cpp                              					 	 //
//                                                                           //
//  Copyright 2008 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/statistics/detail/mpl/rest.hpp>
#include <boost/statistics/detail/mpl/most.hpp>
#include <libs/statistics/detail/range_ex/example/rest.h>

void example_nested_chain(std::cout);

	typedef boost::mpl::range_c<int,0,3> vec_;
	namespace mpl = boost::statistics::detail::mpl;

	typedef mpl::rest<vec_> meta_rest_;
    typedef meta_rest_::type rest_;
	typedef mpl::most<vec_> meta_most_;
    typedef meta_most_::type most_;
        
    BOOST_MPL_ASSERT((
		boost::mpl::equal<
        	boost::mpl::range_c<int,1,3>,
            rest_
        >
    ));
    BOOST_MPL_ASSERT((
		boost::mpl::equal<
        	boost::mpl::range_c<int,0,2>,
            most_
        >
    ));

}
