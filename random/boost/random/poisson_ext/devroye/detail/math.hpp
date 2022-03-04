//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::detail::math.hpp                                    //
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DETAIL_MATH_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DETAIL_MATH_HPP_ER_2010
#include <cmath>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/factorials.hpp>

#include <boost/numeric/conversion/converter.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/limits.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{
namespace detail{

	// Math functions or constants are gathered here, so that any implementation
    // change to one of them need not be replicated throughout the code.
 	template<typename Int,typename T,typename P>
	struct math{
    	typedef Int int_type;
    	typedef T float_type;
    
		static const float_type pi(){ 
        	static const float_type val 
            	= boost::math::constants::pi<float_type>();
            return val;
        }
        static const float_type eps(){
        	return boost::numeric::bounds<float_type>::smallest();
        }
        static bool is_strictly_negative(const float_type& x){
        	return ( !( x >= (-eps()) ) );
        }
        template<typename E>
        static float_type pow(const float_type& x,const E& k){
        	return std::pow(x,k);
        }
        static float_type exp(const float_type& x){
        	return std::exp(x);
        }
        static float_type sqrt(const float_type& x){
        	return std::sqrt(x);
        }
		static float_type floor(const float_type& x){
        	float_type val = std::floor(x);
        	return val;
        }
		static float_type ceil(const float_type& x){
        	float_type val = std::ceil(x);
        	return val;
        }
        static float_type log1p(const float_type& x){
        	return boost::math::log1p(x);
        }
        static float_type log1p(const float_type& x,const P& p){
        	return boost::math::log1p(x,p);
        }
        static float_type log(const float_type& x){
        	return std::log(x);
        }
        static float_type factorial(const int_type& i,const P& p){
        	return boost::math::factorial<float_type>(i,p);
        }

		template<typename To,typename From>
        static To convert(const From& t){
            typedef boost::numeric::converter<To,From> to_; 
            return to_::convert(t);        
        
        }
		static float_type to_float(const int_type& i){
            return convert<float_type>(i);        
        }
		static int_type to_int(const float_type& x){
            return convert<int_type>(x);        
        }
	};

}// math
}// devroye
}// poisson
}// random
}// boost

#endif     
    