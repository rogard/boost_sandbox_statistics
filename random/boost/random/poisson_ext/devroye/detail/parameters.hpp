//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::poisson_devroye::detail::parameters.hpp         	//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_PARAMETERS_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_PARAMETERS_HPP_ER_2010
#include <boost/random/poisson_ext/devroye/detail/math.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace detail{       
            
    // These are quantities that remain fixed throughout sampling and are only
    // modified if the poisson mean is changed.
	template<typename Int,typename T, typename P>
    struct parameters{

		typedef devroye::detail::math<Int,T,P> ma_;
    
    	public:
        
        typedef Int result_type;
        typedef T input_type;
        
        parameters(){}
    	explicit parameters(const Int& mean)
        {
			this->m1_ 		= 	ma_::to_float(mean);
			this->m2_ 		= 	ma_::to_float(2*mean);	
			input_type m8 	= 	ma_::to_float(8*mean);
            input_type m32 	= 	ma_::to_float(32*mean);
            
            this->c1_ = ma_::to_float(1)/m8; // Equation (6)			
            
            // Equation (10)
            this->delta_ 	= 	ma_::log1p( m32/ma_::pi(), P() );		
            this->delta_ 	= 	ma_::sqrt(this->delta() * this->m1());	

			// Below equation (7)
			this->sd1_ = ma_::sqrt(
            	this->m1() + this->delta() / ma_::to_float(2)
            ); 															
			this->shape2_ = this->delta() / (this->m2()+this->delta()); 
            
            input_type a1, a2, a3, a;
			
			a1 = ma_::sqrt( ma_::pi() * (this->m2() + this->delta()) ); 
            a1 *= ma_::exp(this->c1()); 				
            a2 = ma_::exp(-(this->delta()+ma_::to_float(1)) * this->shape2());
            a2 /= this->shape2(); 						
            a3 = ma_::to_float(1);
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

		const input_type& m1()const{ return this->m1_; }
		const input_type& m2()const{ return this->m2_; }
		const input_type& delta()const{ return this->delta_; }
		static input_type loc1(){ return -ma_::to_float(1)/ma_::to_float(2); }
		const input_type& sd1()const{ return this->sd1_; }
		const input_type& shape2()const{ return this->shape2_; }
        const input_type& c1()const{ return this->c1_; }
		const input_type& p1()const{ return this->p1_; }
		const input_type& p2()const{ return this->p2_; }
		const input_type& p3()const{ return this->p3_; }

		private:
        input_type inv_m1_;
		input_type m1_;
		input_type m2_;			
        input_type delta_;		
		input_type sd1_;		
		input_type shape2_;		
  
        input_type c1_;			
        input_type p1_;			
        input_type p2_;		
		input_type p3_;

    };
    
}// detail
}// devroye
}// poisson
}// random
}// boost

#endif
