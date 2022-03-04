///////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::common::factory.hpp                 	 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_COMMON_FACTORY2_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_COMMON_FACTORY2_HPP_ER_2009
#include <boost/statistics/detail/distribution/survival/response/common/meta_factory.hpp>
#include <boost/statistics/detail/distribution/model/tag/response.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/make_map.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace response {


	// Returns a fusion map with tag Tag and data type Y
	template<typename Y,typename Tag = distribution::model::tag::response>
	class factory2{
    	typedef typename meta::factory<Y>::type factory_;
        typedef	boost::fusion::pair<Tag,Y> pair_;

        public:
		typedef Tag tag;
        typedef boost::fusion::map<pair_> result_type;

		factory2(){}
        template<typename Arg> 
        factory2(const Arg& arg):f(arg){}
        factory2(const factory2& that):f(that.f){}
        
        template<typename M>
        result_type operator()(const M& record)const{
        	return boost::fusion::make_map<Tag>(
    			f(record)
            );
        }
    
    	private:
    	mutable factory_ f;
    
    };
    
    
}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif