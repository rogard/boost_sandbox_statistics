//////////////////////////////////////////////////////////////////////////////
// random::poisson::devroye::crtp::parameters.hpp                        	//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_CRTP_PARAMETERS_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_CRTP_PARAMETERS_HPP_ER_2010
#include <boost/math/constants/constants.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
            
    // These are quantities that remain fixed throughout sampling and are only
    // modified if the poisson mean is changed.
	template<typename Int,typename T, typename P,typename IntT>
    struct parameters{
        typedef IntT converter_;

    	public:
        static const T pi;
        static const T one;
        static const T two;
        static const T eps;
        
        typedef Int result_type;
        typedef T input_type;
        
        parameters(){}
    	explicit parameters(const Int& i_mean)
        {
            using namespace boost::math;
			this->m1_ = converter_::convert( i_mean );
			this->m2_ = converter_::convert( 2 * i_mean );	
			T m8  = converter_::convert( 8 * i_mean );
            T m32 = converter_::convert( 32 * i_mean );
            this->c1_ = converter_::convert(1) / m8; // Equation (6)			
            
            // Equation (10)
            this->delta_ = 	log1p( m32 / pi, P() );		
            this->delta_ = 	sqrt( this->delta() * this->m1() );	

			// Below equation (7)
			this->sd1_ = sqrt( this->m1() + this->delta() / two );
            this->shape2_ = this->delta() / ( this->m2() + this->delta() ); 
            
            T a1, a2, a3, a;
			
			a1 = sqrt( pi * ( this->m2() + this->delta() ) ); 
            a1 *= exp( this->c1() ); 				
            a2 = exp( -( this->delta() + one ) * this->shape2());
            a2 /= this->shape2(); 						
            a3 = one;
            a = a1 + a2 + a3;
            this->p1_ = a1 / a;								
            this->p2_ = a2 / a;												
            this->p3_ = a3 / a;												

			// Reconciliation with Fortran code
            // RL					m1
            // TWO					m2
			// CON 					c1
            // D 					delta
            // D2					delta + m2
			// D3 					1 / shape2
            // STDDEV 				sd1
            // SUM 					a1 + a2 + a3
            // PBODY 				p3 = a3/(a+a2+a3) 
			// PTAIL 				p2 + p3

        }

		std::ostream& parameters_description(std::ostream& os)const{
        	return os 
                << '('
                << "m1 = " 		<< this->m1()
                << ','
                << " m2 = "		<< this->m2()
                << ','
                << " delta = " 	<< this->delta()
                << ','
                << " loc1 = "	<< loc1()
                << ','
                << " sd1 = " 	<< this->sd1()
                << ','
                << " shape2 = "	<< this->shape2()
                << ','
                << " c1 = "		<< this->c1()
                << ','
                << " p1 = "		<< this->p1()
                << ','
                << " p2 = "		<< this->p2()
                << ','
                << " p3 = "		<< this->p3()
                << ')';
        }

		const T& m1()const{ return this->m1_; }
		const T& m2()const{ return this->m2_; }
		const T& delta()const{ return this->delta_; }
		static T loc1(){ return -one/two; }
		const T& sd1()const{ return this->sd1_; }
		const T& shape2()const{ return this->shape2_; }
        const T& c1()const{ return this->c1_; }
		const T& p1()const{ return this->p1_; }
		const T& p2()const{ return this->p2_; }
		const T& p3()const{ return this->p3_; }

		private:
        T inv_m1_;
		T m1_;
		T m2_;			
        T delta_;		
		T sd1_;		
		T shape2_;		
  
        T c1_;			
        T p1_;			
        T p2_;		
		T p3_;

    };

    template<typename Int,typename T,typename P,typename IntT>
    const T parameters<Int,T,P,IntT>::pi = boost::math::constants::pi<T>();

    template<typename Int,typename T,typename P,typename IntT>
    const T parameters<Int,T,P,IntT>::one = IntT::convert( 1 );

    template<typename Int,typename T,typename P,typename IntT>
    const T parameters<Int,T,P,IntT>::two = IntT::convert( 2 );

    template<typename Int,typename T,typename P,typename IntT>
    const T parameters<Int,T,P,IntT>::eps 
        = boost::numeric::bounds<T>::smallest();

}// devroye
}// poisson
}// random
}// boost

#endif
