///////////////////////////////////////////////////////////////////////////////
// example::iterator::flatten_iterator2.cpp                                  //
//                                                                           //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
/////////////////////////////////////////////////////////////////////////////// 
#include <iostream>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/range.hpp>
#include <vector>
#include <boost/iterator/flatten_iterator.hpp>
#include <boost/range/flatten_range.hpp>
#include <libs/iterator/example/flatten_iterator2.h>

void example_flatten_iterator2(std::ostream& out){
    out << "->example_flatten_iterator2 : ";

    using namespace boost;
    typedef int val_;
    typedef std::vector<val_>							vals_;
	typedef boost::multi_array<val_, 2> 				ma_;
	typedef boost::multi_array_types::index_range 		idx_range_;
	typedef boost::multi_array_types::index 			idx_;
    typedef boost::range_iterator<const ma_>::type		it_ma_;
    typedef flatten_iterator<it_ma_>					flat_it_;
    
    typedef boost::array_view_gen<ma_,2>::type 			view2_;
    typedef boost::range_iterator<view2_>::type 		nit2_;
    typedef flatten_iterator<nit2_>						flat_it2_;

    typedef boost::array_view_gen<ma_,1>::type 			view1_;
    
    //  	array_type::index_gen indices;
    //  	array_type::array_view<2>::type myview =
    //    myarray[ indices[range(0,2)][1][range(0,4,2)] ];

    ma_ ma(boost::extents[2][5]);
    {
        vals_ vals1;
    	using namespace boost::assign;
        vals1 += 1,2,3,4,5;
        vals1 += 6,7,8,9,10;
        vals1 += 11,12,13,14,15;
        ma.assign(boost::begin(vals1),boost::end(vals1));
	}        

//    view1_ view1 = ma[ boost::indices[1][idx_range_(0,4)] ]; // idx_range_(0,2)
//    typedef boost::range_iterator<const view_>::type nit_;

    view2_ view2 = ma[ boost::indices[idx_range_()][idx_range_(0,4)] ]; // idx_range_(0,2)
//    typedef boost::range_iterator<view2_>::type nit2_;
//    nit2_ nit2 = boost::begin(view2);

	flat_it2_ it2_b(boost::begin(view2),boost::end(view2));
	flat_it2_ it2_e(boost::end(view2),boost::end(view2));
    std::copy(it2_b,it2_e,std::ostream_iterator<val_>(std::cout," "));

//	it_ma_ it_ma = boost::begin(ma);
//    flat_it_ b(ma.begin(),ma.end());

    //	ma[boost::indices[1][idx_range_(0,4)]] = vals1; //assign(boost::begin(vals1),boost::end(vals1));
    //	ma(boost::indices[1]); 

    out << "<-" << std::endl;
}