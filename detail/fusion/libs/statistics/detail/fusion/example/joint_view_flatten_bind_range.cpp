///////////////////////////////////////////////////////////////////////////////
// detail::fusion::example::joint_view_bind_range.cpp                  		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
/////////////////////////////////////////////////////////////////////////////// 
#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/range.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>

#include <boost/iterator/flatten_iterator.hpp>

#include <boost/statistics/detail/fusion/joint_view/flatten_bind_range.hpp>
#include <libs/statistics/detail/fusion/example/joint_view_flatten_bind_range.h>


void example_joint_view_flatten_bind_range(std::ostream&){

	namespace jv = boost::statistics::detail::fusion::joint_view;
   
	typedef int val_;
    typedef boost::mpl::int_<0> 					k0_;
    typedef boost::mpl::int_<1> 					k1_;
	const int n = 2;
    
	typedef boost::fusion::pair<k0_,val_> 			p0_;
    typedef boost::fusion::map<p0_>					m0_;
	typedef boost::fusion::pair<k1_,val_> 			p1_;
    typedef boost::fusion::map<p1_>					m1_;
    
    typedef boost::array<m0_,n>						ar0_;
    typedef boost::range_iterator<ar0_>::type 		it0_;
	typedef boost::multi_array<m1_, 2> 				ma1_;
    typedef boost::range_iterator<ma1_>::type 		it1_;
	typedef boost::multi_array_types::index_range 	idx_range_;
	typedef boost::multi_array_types::index 		idx_;
    
	typedef boost::array_view_gen<ma1_,2>::type 	view2_ma1_;
    
    typedef jv::result_of::flatten_bind_range<it0_,it1_> meta_; 
    typedef meta_::type 							flat_r_;
	typedef boost::range_iterator<flat_r_>::type	flat_it_;

	ar0_ ar0 = boost::assign::list_of(
    	boost::fusion::make_map<k0_>(1)
    )(
      	boost::fusion::make_map<k0_>(2)
    );

	ma1_ ma1(boost::extents[n][2]);
    {
        std::vector<m1_> vals1;
    	using namespace boost::assign;
        vals1 = list_of(
        	boost::fusion::make_map<k1_>(1)
        )(
        	boost::fusion::make_map<k1_>(2)
        )(
        	boost::fusion::make_map<k1_>(3)
        )(
        	boost::fusion::make_map<k1_>(4)
        );
        ma1.assign(boost::begin(vals1),boost::end(vals1));
	}        
    
	flat_r_ flat_r = jv::flatten_bind_range(
    	boost::begin(ar0),
        boost::end(ar0),
    	boost::begin(ma1),
        boost::end(ma1)
    );

	flat_it_ flat_b = boost::begin(flat_r);
	flat_it_ flat_e = boost::end(flat_r);

	// BUG : post increment causes runtime error.
	while(flat_b!=flat_e){
    	std::cout 
        	<< '(' 
            << boost::fusion::at_key<k0_>(*flat_b)
        	<< ','
            << boost::fusion::at_key<k1_>(*flat_b)
        	<< ')' 
            << std::endl;
        ++flat_b;
    }

}
