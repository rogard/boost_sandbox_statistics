///////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::common::generator.hpp                 	 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_COMMON_GENERATOR_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_COMMON_GENERATOR_HPP_ER_2009
#include <algorithm>
#include <vector>
#include <iterator>
#include <boost/fusion/include/make_map.hpp>
#include <boost/statistics/detail/fusion/joint_view/bind_iterator.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace response{
    
    // e.g. Factory = factory2<event<T> >
    template<typename Factory>
	class generator{
    	public:

        typedef Factory factory_type;
        typedef typename factory_type::tag tag_y_;
        typedef typename factory_type::result_type y_;
        typedef record::tag::entry_time tag_et_;

        // Side effect : writes to out the responses  
        // Treats failure times in [b_ft,e_ft) as measured from entry_time
        template<typename ItY,typename T,typename It,typename T1>
        static ItY call(
        	ItY out,
        	const T& entry_time,
            It b_ft,
            It e_ft,
            const T1& time_analysis
        ){
            typedef typename 
            	boost::fusion::result_of::make_map<tag_et_,T1>::type et_;
            et_ et = boost::fusion::make_map<tag_et_>(entry_time);
        	BOOST_ASSERT(entry_time <time_analysis);
        
			namespace jv = statistics::detail::fusion::joint_view;
            return std::transform(
                jv::bind_iterator(et,b_ft),
                jv::bind_iterator(et,e_ft),
                out,
                factory_type( time_analysis )
            );
		}

    };

}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif