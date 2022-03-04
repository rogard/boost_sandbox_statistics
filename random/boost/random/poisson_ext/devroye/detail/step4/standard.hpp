//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::devroye::detail::step4::standard.hpp         		//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_STANDARD_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_STANDARD_HPP_ER_2010
// --- For testing only ---
#include <string>
#include <boost/timer.hpp>
#include <boost/format.hpp>
// ------------------------

#include <boost/random/poisson_ext/devroye/detail/q.hpp>
#include <boost/random/poisson_ext/devroye/detail/int_mean.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  
namespace detail{
namespace step4{

	// Poisson sampler by the method of Devroye with a standard step4
	//
	// Complexity O(1+sqrt(mean)) as mean -> infinity, p.203
	//
    // Properties:
    // Int = int fails for mean >= c, 256 < c <= 512
    // Int = long int fails for mean >= c, 65536 < c <= 262144
    //
    // Warning : the properties need to be checked.
	template<typename Int,typename T,typename P>
    class standard :
        detail::q<Int,T,P>, 
        public detail::int_mean<step4::standard<Int,T,P>,Int,T,P>
    {
		typedef detail::q<Int,T,P> q_fun_;
		typedef detail::int_mean<step4::standard<Int,T,P>,Int,T,P> super_;

		public:
		typedef typename super_::result_type result_type;
		typedef typename super_::input_type input_type;

		standard():super_(){}
		explicit standard(const result_type& mean)
        :super_(mean)
//      ,elapsed(0)
        {}

		bool accept(){    
//        	t.restart();
            typename super_::input_type q_val = this->q_fun(
            	this->int_mean_val(),
                this->y()
            );
//            elapsed += t.elapsed(); 
			if(this->v()<q_val)
            {
            	this->y_ += this->int_mean_val();
                return true;
            }else{
				return false;            
            }
		}

// Only for testing :
//		~standard(){
//        	std::string str = "elapsed for q() at mean = %1% : %2%";
//            boost::format f(str);
//            f%this->int_mean_val()%elapsed;
//        	std::cout << f << std::endl;
//        }
//        boost::timer t;
//        typename super_::input_type elapsed;

	};

}// step4
}// detail
}// devroye
}// poisson
}// random
}// boost

#endif




