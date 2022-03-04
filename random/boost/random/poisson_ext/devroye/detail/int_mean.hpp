//////////////////////////////////////////////////////////////////////////////
// random::poisson::devroye::detail::int_mean.hpp                        	//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_INT_MEAN_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_INT_MEAN_HPP_ER_2010
#include <boost/range.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>

#include <boost/random/poisson_ext/devroye/detail/math.hpp>
#include <boost/random/poisson_ext/devroye/detail/parameters.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{     
namespace detail{

    // Samples from the poisson distribution with an integer mean
    //
    // Source : The computer generation of poisson random variables. L. Devroye,
    // Computing 26, Springer-Verlag, 1981
    //
    // Parameter     Description
    // Step4         A class that models the concept by the same name
    // Int           An integer type
    // T             A float type
    // P             An error handling policy
	//
    // Expression                 Requirement
    // int_mean<Step4,Int,T,P>    Public base of Step4 
	//
    // Concept Step4:
    // int_mean<Step4,Int,T,P> is a public base, and
    // Expression    Result type   Side effect
    //  accept()     bool          if true, y is set to the value to be returned
    //
    // The numbers on the right are those of the lines of the Fortran listing 
    // given in the reference above.
    template<typename Step4,typename Int,typename T,typename P>
    class int_mean : public devroye::detail::parameters<Int,T,P>
        {

		typedef devroye::detail::math<Int,T,P> ma_;
        typedef devroye::detail::parameters<Int,T,P> super1_;

		public:

        typedef T input_type;
        typedef Int result_type;

        input_type mean() const { return ma_::to_float(this->int_mean_); }
        void reset() { }
                        
		int_mean():super1_(){}
        explicit int_mean(const result_type& m)
        	:super1_(m),int_mean_(m){
            	BOOST_ASSERT(this->int_mean_val()>=0);
            }

        int_mean (const int_mean& that)
        	:super1_(that),
            int_mean_(that.int_mean_),
			u_(that.u_),
        	x_(that.x_),
        	y_(that.y_),
        	v_(that.v_)
            {}
        
        int_mean& operator=(const int_mean& that){
        	if(that!=this){
				static_cast<super1_&>(*this) = that;
            	this->int_mean_ = (that.int_mean_);
				this->u_ = (that.u_);
        		this->x_ = (that.x_);
        		this->y_ = (that.y_);
        		this->v_ = (that.v_);
            }
			return (*this);
		}

  		template<class U>
  		result_type operator()(U& urng)
  		{
			result_type result =  this->step1(urng);	        
            BOOST_ASSERT(result >= 0);
            return result;
        }
		
            // --- I/O --- //
            
            template<class CharT, class Traits>
            friend std::basic_ostream<CharT,Traits>&
            operator<<(
                std::basic_ostream<CharT,Traits>& os, 
                const int_mean& pd
            )
            {
                os 	<< "devroye("
            		<< pd.int_mean_val()
            		<< ','
            		<< pd.u() 
            		<< ','
            		<< pd.x() 
            		<< ','
            		<< pd.y() 
            		<< ','
            		<< pd.v() 
            		<< ')';
                return os;
            }
            
            template<class CharT, class Traits>
            friend std::basic_istream<CharT,Traits>&
            operator>>(
                std::basic_istream<CharT,Traits>& is, 
                int_mean& pd
            )
            {
            	result_type new_mean;
                is	>> std::ws
            		>> new_mean
            		>> std::ws
                	>> std::ws 	// u
            		>> std::ws
                	>> std::ws	// x
            		>> std::ws
                	>> std::ws	// y
            		>> std::ws
                	>> std::ws	// v
            		>> std::ws;
				static_cast<Step4&>(pd) = Step4(new_mean);
            	return is;
            }
            
        // ----------- //
            
        protected:
		
		template<typename U>
		inline result_type step1(U& urng){
        	// TODO max recursion policy
            
            // line 10 : case mean = 0;
            
            this->u_ = urng();												//13
            if(this->u()>this->p1()){ 
            	// Reconciliation with Fortran listing :
                // ptail = p2 + p3 = 1-p1. 
                // u' ~ 1-u. (u'<ptail) <=> (1-u<p2+p3) <=> (u > p1)
            	return this->step3(urng);
            }else{
                return this->step2(urng);
            }	
		}

		template<typename U>
		inline result_type step2(U& urng){
        	input_type z = this->random_z(urng); 							//15
        	this->x_ = ( this->sd1() * z ) + super1_::loc1();
            if(
            	(this->x()>this->delta()) 
                	||  (this->x()< (-this->m1()))
            ){ 
            	return this->step1(urng);
            }else{
            	// y is rounded away from zero
                if(ma_::is_strictly_negative(this->x())){ 
                    this->y_ = ma_::floor(this->x());
                }else{
                    this->y_ = ma_::ceil(this->x());
                }
                input_type e  = this->random_exp1(urng);
                this->v_ = -( e + ma_::pow(z,2)/ma_::to_float(2) ) + this->c1();
                return this->step4(urng);
            }
        }

		template<typename U>
		inline result_type step3(U& urng){
        
            // Reconciliation with Fortran listing :
            // pbody = p3 = 1-(p1+p2) 
            // u' ~ 1-u. (u'<pbody) <=> (1-u<p3) <=> (u > p1+p2)
        	if(this->u()>this->p1()+this->p2()){ 							
            	this->y_ = this->int_mean_val(); 
                return this->y();
            }else{
            	input_type e1 = this->random_exp1(urng);
            	input_type e2 = this->random_exp1(urng);
            	this->x_ = this->delta() + e1 / this->shape2();				//51 
            	this->y_ = ma_::to_int( ma_::ceil(this->x()) );
            	this->v_ = - ( 
                	e2 + this->shape2() * (ma_::to_float(1) + this->x())
                );
            	return this->step4(urng);
            }
        }

		template<typename U>
		inline result_type step4(U& urng){
            Step4& derived = static_cast<Step4&>(*this);		
            if(derived.accept()){
            	return this->y();
            }else{
				return this->step1(urng);            
            }
		}

		template<typename U>
		input_type random_z(U& urng)const{
        	typedef boost::normal_distribution<input_type> d_;
            static d_ d = d_(ma_::to_float(0),ma_::to_float(1));
            return d(urng);
        }

		template<typename U>
		input_type random_exp1(U& urng)const{
        	typedef boost::exponential_distribution<input_type> d_;
            static d_ d = d_(ma_::to_float(1));
            return d(urng);
        }

		// Parameter
		result_type int_mean_;
        
        // These are quantities that vary throughout sampling
		input_type	u_;
        input_type 	x_;
        result_type y_;
        input_type 	v_;

        const result_type& 	int_mean_val()const{ return this->int_mean_; } 
        const input_type& 	u()const{ return this->u_; } 
        const input_type& 	x()const{ return this->x_; } 
        const result_type& 	y()const{ return this->y_; } 
        const input_type& 	v()const{ return this->v_; } 

	};

}// detail
}// devroye
}// poisson
}// random
}// boost

#endif 
