//////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::poisson_devroye::q_function::standard.hpp        	//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_FUNCTION_STANDARD_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_FUNCTION_STANDARD_HPP_ER_2010
#include <cmath>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/random/poisson_ext/devroye/detail/math.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace detail{

	// The q-function is needed in either version of step4 of the algorithm.
	// See equation (4), p.199.
    //
    // TODO make static
    template<typename Int,typename T,typename P>
    struct q
    {

		typedef devroye::detail::math<Int,T,P> ma_;
        
        // TODO perhaps make this a template or runtime choice
        // For now overwrite manually. Checking may impedede speed a bit.
        typedef boost::mpl::bool_<true> do_check_; 
        
        typedef std::string str_;
        typedef boost::format f_;
		static const str_ name(){ return "devroye::detail::q"; }

		public:
        
        q(){}
    
        typedef T float_;
		typedef Int int_;

        float_ q_fun(const int_& mean,const int_& y)const{
        	BOOST_ASSERT(y>=(-mean));
        	float_ result;
        
			if(y<0){ 
            	result = this->impl1(mean,y); 
            }else{
            	if(y==0){
					result = this->impl2(mean,y);                
                }else{
                	if(y>0){
                		result = this->impl3(mean,y);
                    }else{
                    	throw std::runtime_error(name() + "q");
                    }
                }
            }
            if(do_check_::value){
				this->check_against_slow_version(mean,y,result); 
				this->check_lemma1(mean,y,result); 
				this->check_lemma2(mean,y,result); 
            }
            
            return result;
		}

    private:

        float_ slow_version(const int_& mean,const int_& y)const
        {
            return y * ma_::log(y) 
                - ma_::log ( ma_::factorial(mean+y,P())/ma_::factorial(mean,P()) );
        }

        void check_against_slow_version(
            const int_& mean,
            const int_& y,
            const float_& result
        )const
        {
            static const str_ str = name() 
                + "::check_bound_against_slow_version, q(%1%) = %2% != %3%";
            float_ alt = this->slow_version(mean,y);
            std::cout << "alt=" << alt << ' ';
            std::cout << "res=" << result << std::endl;
            if((result> alt + ma_::eps()) || (alt> result + ma_::eps()) )
            {
                throw std::runtime_error(
                    ( boost::format(str) % y % result % alt ).str()
                );
            }
        
        }

		// Lemma 1, p.199
		// q(y) < upper_bound(y) if y >= -mean
		float_ upper_bound(const int_& mean,const int_& y)const{
        	float_ num = ( - ma_::to_float(y) * ma_::to_float(1+y) );
            float_ den = ma_::to_float(2 * mean);
            den += ma_::to_float((y<0)?0:y);
            return num / den;
        }

		void check_lemma1(
        	const int_& mean,
            const int_& y,
            const float_& result
        )const{
            if( y >= mean ){
            	float_ b = this->upper_bound(mean,y);
                if( result>b ){
                	static const str_ str 
                    	= name() + "::check_bound, %1% = q(%2%) > %3%";
                    throw std::runtime_error(
						( boost::format(str) % result % y % b ).str()
                    );
                }
            }
        }

		// Lemma 2, p. 199
		void check_lemma2(
            const int_& mean,
            const int_& y,
            const float_& q_val
        )const{
            static const str_ str1 
            	= "q::check_lemma2(%1%,%2%,%3%) : failed condition(s) :";

        	int_ yp1 = y + 1;
        	int_ yp1pm1 = yp1 + mean;
            int_ y2p1 = 2 * y + 1;
            int_ ysq = y * y;
            int_ yp1sq = yp1 * yp1;
            int_ m2 = 2 * mean;
            int_ msq = mean * mean;
            int_ mcu = msq * mean;
            
            float_ lhs 
            	= q_val + ma_::to_float( y * yp1 ) / ma_::to_float( m2 );

			str_ str2;
            bool fail = false;
            if(y>=0)
            {
                if(!(lhs >= 0)){
                	str2 += (f_("1: lhs = %1% >= 0")%lhs).str();
                    fail = true;
                }
            }else{
                if(!(lhs <= 0)){
                	str2 += (f_("1: lhs = %1% <= 0")%lhs).str();
                    fail = true;
                }
			}                

            float_ rhs 
            	=  ma_::to_float( y * yp1 * y2p1 ) / ma_::to_float(12 * msq);
            if(!(lhs <= rhs)){
				f_ f2(" 2: lhs = %1% <= rhs = %2%");
                str2 += (f2%lhs%rhs).str();
                fail = true;
            }

            float_ num = ma_::to_float( ysq * yp1sq );
            if(y>=0){
                rhs -= ( num / ma_::to_float(12 * mcu) );
            }else{
				rhs -= ( num / ma_::to_float(12 * msq * yp1pm1) );            	    
            }
            if(!(lhs >= rhs)){
                f_ f3(" 3: lhs = %1% >= rhs = %2%");
                str2 += (f_(f3)%lhs%rhs).str();
                fail = true;
            }
			if(fail){
            	str2 = (f_(str1)%mean%y%q_val).str() + str2;
                throw std::runtime_error(str2);
			}
        }

		// TODO consider using 
        // #include <boost/math/tools/series.hpp>

		float_ impl1(const int_& mean,const int_& y)const{
        	BOOST_ASSERT(y<0);
            float_ im1 = ma_::to_float(1) / ma_::to_float(mean);
        	float_ result = ma_::to_float(0);
            int_ n = -(y+1) + 1;
			for(int_ i = 0; i < n; i++){
            	result += ma_::log1p(-ma_::to_float(i)*im1,P());
            }
            return result;
        }
    
		float_ impl2(const int_& mean,const int_& y)const{
        	BOOST_ASSERT(y==0);
        	return ma_::to_float(0);
		}
		float_ impl3(const int_& mean,const int_& y)const{
        	BOOST_ASSERT(y>0);
            float_ im1 = ma_::to_float(1) / ma_::to_float(mean);
        	float_ result = ma_::to_float(0);
            int n = y+1;
			for(int_ i = 1; i < n; i++){
            	result -= ma_::log1p(ma_::to_float(i)*im1,P());
            }
            return result;
        }

	};

}// q_function
}// devroye
}// poisson
}// random
}// boost

#endif
