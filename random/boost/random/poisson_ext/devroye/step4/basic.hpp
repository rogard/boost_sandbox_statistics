//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::devroye::detail::step4::basic.hpp         		    //
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_BASIC_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_BASIC_HPP_ER_2010

#include <boost/random/poisson_ext/devroye/detail/q.hpp>
#include <boost/random/poisson_ext/devroye/detail/int_mean.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  
namespace step4{

	// Poisson sampler by the method of Devroye with a basic step4
	//
	// Complexity O(1+sqrt(mean)) as mean -> infinity, p.203
	template<typename Int,typename T,typename P,
        typename IntT,typename TInt,typename Q>
    class basic 
        public devroye::crtp<
            step4::basic<Int,T,P,IntT,TInt,Q>,
            Int,T,P,IntT,TInt
        >
    {
		typedef crtp<step4::basic<Int,T,P,IntT,Q>,Int,T,P,IntT,TInt> crtp_;

		public:

		basic(){}
		explicit basic(const result_type& mean)
            :crtp_(mean)
            {}

		bool accept()const{    
            T q = q::fun(this->i_mean(),this->i_y(),P(),IntT(),Q());
			if(this->v()<q)
            {
            	this->i_y_ += this->i_mean();
                return true;
            }else{
				return false;            
            }
		}

	};

}// step4
}// devroye
}// poisson
}// random
}// boost

#endif




