///////////////////////////////////////////////////////////////////////////////
// statistics::detail::fusion::example::serialize.cpp                  		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
/////////////////////////////////////////////////////////////////////////////// 
#include <vector>
#include <fstream>
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/typeof/typeof.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/assert.hpp>
#include <boost/range.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <boost/statistics/detail/fusion/joint_view/binder.hpp>
#include <boost/statistics/detail/fusion/joint_view/bind_iterator.hpp>
//#include <boost/statistics/detail/fusion/serialization/save.hpp>
//#include <boost/statistics/detail/fusion/serialization/load.hpp>
//#include <boost/statistics/detail/fusion/serialization/map.hpp>
//#include <boost/statistics/detail/fusion/serialization/vector.hpp>

#include <boost/fusion/include/make_vector.hpp>

#include <libs/statistics/detail/fusion/example/serialize.h>

void example_bind_range2(std::ostream& os){

    os << "example_joint_view_binder -> ";
    
    using namespace boost;
    namespace stat = boost::statistics::detail;
    namespace jv = stat::fusion::joint_view;

    typedef mpl::int_<0> key0_;
    typedef mpl::int_<1> key1_;
    typedef mpl::int_<2> key2_;
    
    typedef unsigned d0_;
    typedef unsigned d1_;
    typedef unsigned d2_;
    typedef fusion::pair<key0_,d0_>       			p0_;
    typedef fusion::pair<key1_,d1_>                 p1_;
    typedef fusion::pair<key2_,d2_>                 p2_;
    typedef fusion::map<p0_>                      	map0_;
    typedef fusion::map<p1_>                      	map1_;
	typedef std::vector<map1_>						vec1_;
    typedef boost::fusion::vector<map0_&,vec1_>		seq_;
	typedef jv::bind_range2							range2_;
        
    const d0_ d0 = 0;
    const d1_ d1 = 0;
    const d2_ d2 = 0;
    map0_ map0(boost::fusion::make_pair<key0_>(d0));    
    map1_ map1(boost::fusion::make_pair<key1_>(d1));
    map1_ map2(boost::fusion::make_pair<key1_>(d2));
	vec1_ vec1;    
	vec1.push_back( map1 );    
	vec1.push_back( map2 );    

	range2_ range2;
//	meta_::call(map0,vec1);
	range2(boost::fusion::make_vector(map0,vec1));

	seq_ seq(map0,vec1);
    range2(seq);
    
 	os << "<-";   
}