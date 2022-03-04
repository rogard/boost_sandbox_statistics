///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::random_generator_v0.hpp                   //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_GENERATE_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_GENERATE_HPP_ER_2009
#include <algorithm>
#include <iterator>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution/survival/record/random/generator_v0.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{

 	// sample records given (x,model)
	template<typename It,typename N,typename U,typename M,typename X>
    It generate_n(It it_ft,const N& n,U& urng,const M& model,const X& x)
    {  
    	typedef typename distribution::meta::value<M>::type val_;
        typedef record::meta::random_generator<0,val_> meta_gen_;
        typedef typename meta_gen_::type gen_;
        gen_ gen = meta_gen_::call(x, model, urng);
        return std::generate_n( it_ft, n, gen );
    } 

}// record
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif