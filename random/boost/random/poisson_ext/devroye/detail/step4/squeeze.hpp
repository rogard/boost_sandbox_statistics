//////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::devroye::detail::step4::squeeze.hpp         			//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_SQUEEZE_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_SQUEEZE_HPP_ER_2010
#include <boost/random/poisson_ext/devroye/detail/q.hpp>
#include <boost/random/poisson_ext/devroye/detail/math.hpp>
#include <boost/random/poisson_ext/devroye/detail/int_mean.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  
namespace detail{
namespace step4{

    // Poisson sampler by the method of Devroye with a squeeze step4
	//
	// Complexity O(1) as mean -> infinity, p.204
    //
    // Bug : currently does not converge.
	template<typename Int ,typename T,typename P>
    class squeeze :
        detail::q<Int,T,P>, 
        public detail::int_mean<step4::squeeze<Int,T,P>,Int,T,P>
    {

		typedef detail::q<Int,T,P> q_fun_;
        typedef devroye::detail::math<Int,T,P> ma_;

		typedef detail::int_mean<step4::squeeze<Int,T,P>,Int,T,P> super_;

		public:
		typedef typename super_::result_type result_type;
		typedef typename super_::input_type input_type;

		squeeze():super_(){}
		explicit squeeze(const result_type& mean):super_(mean){}

		bool accept(){        
            bool a = ma_::is_strictly_negative(this->x());

			typedef result_type int_; 	
			typedef input_type float_;  	
			int_ y1 = this->y();
			int_ yp1 = y1 + 1;
            int_ y1yp1 = y1 * yp1;

			float_ t = ma_::to_float(y1yp1) / this->m2(); 	// 1.
            
			if(
            	(!a) && ( this->v() < (-t) )
            ){
				// exit
            }else{
                int_ m1 = this->int_mean_val();
                int_ m6 = 6 * m1;
                int_ y2 = 2 * y1;
                int_ y2p1 = y2 + 1;
                int_ m1p_ayp1 = m1 + a ? yp1 : 0;

            	float_ qr = t * ( 
                	ma_::to_float(y2p1) /ma_::to_float(m6) - ma_::to_float(1) 
                );
                float_ tsq = t * t;
            	float_ qa =  qr - tsq  / ma_::to_float(3 * m1p_ayp1); 

				if(this->v()<qa){
					// exit                
                }else{
                	if(this->v()>qr){
                    	return false;
                    }else{
						
                    	float_ q_val = this->q_fun(m1,this->y());
                    
                    	if(this->v() < q_val)
                        {
                        	// exit
                        }else{
                        	return false;
                        }
                    }
                }
				return false;            
            }

            // exit :
            this->y_ += this->int_mean_val();
            return true;
		}


	};
    
}// detail
}// step4
}// devroye
}// poisson
}// random
}// boost

#endif

