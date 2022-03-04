//////////////////////////////////////////////////////////////////////////////
// random::poisson::devroye::detail::crtp::crtp.hpp                        	//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_CRTP_CRTP_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_CRTP_CRTP_HPP_ER_2010
#include <boost/range.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>

#include <boost/random/poisson_ext/devroye/crtp/parameters.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{     

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
    // IntT          A converter from Int to T
    // TInt          A converter from T to Int
	//
    // Requiremens
    // Expression                       Description
    // crtp<Step4,Int,T,P,IntT,TInt>    Public base of Step4 
	//
    // Concept Step4:
    // crtp<Step4,Int,T,P> is a public base, and
    // Expression    Result type   Side effect
    //  accept()     bool          if true, y is set to the value to be returned
    //
    // The numbers on the right are those of the lines of the Fortran listing 
    // given in the reference above.
    template<typename Step4,typename Int,typename T,
        typename P = boost::math::policies::policy<>,
        typename IntT = boost::numeric::converter<T,Int>,
        typename TInt = boost::numeric::converter<Int,T>
    >
    class crtp : public devroye::parameters<Int,T,P,IntT>
    {
        typedef devroye::parameters<Int,T,P,IntT> parameters_;
        typedef IntT converter_;
        typedef std::string str_;

		public:

        typedef T input_type;
        typedef Int result_type;

        T mean() const { return converter_::convert(this->i_mean_); }
        void reset() { }
                        
		crtp(){}
        explicit crtp(const Int& i_mean)
        	:parameters_(i_mean),max_step1_cnt_(10)
            {
            	BOOST_ASSERT(this->i_mean()>=0);
            }

        explicit crtp(const Int& i_mean,const Int& max_step1_cnt)
        	:parameters_(i_mean),max_step1_cnt_(max_step1_cnt)
            {
            	BOOST_ASSERT(this->i_mean()>=0);
            }
        
  		template<class U>
  		Int operator()(U& urng)const
  		{
            this->step1_cnt_ = 0;
			Int result =  this->step1(urng);	        
            BOOST_ASSERT(result >= 0);
            return result;
        }

        const Int& step1_cnt()const{ return this->step1_cnt_; } 
		
        // --- I/O --- //
            
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT,Traits>&
        operator<<(
            std::basic_ostream<CharT,Traits>& os, 
            const crtp& pd
        )
        {
            os 	<< "devroye("
                << pd.i_mean()
                << ','
                << pd.u() 
                << ','
                << pd.x() 
                << ','
                << pd.i_y() 
                << ','
                << pd.v() 
                << ','
                << pd.step1_cnt() 
                << ')';
            return os;
        }
            
        template<class CharT, class Traits>
        friend std::basic_istream<CharT,Traits>&
        operator>>(std::basic_istream<CharT,Traits>& is, crtp& pd)
        {
            Int new_mean;
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
                >> std::ws
                >> std::ws	// step1_cnt
                >> std::ws;
            static_cast<Step4&>(pd) = Step4(new_mean);
            return is;
        }
            
        // ----------- //
            
        protected:
		
		template<typename U>
		Int step1(U& urng)const
        {
            static const str_ name = "devroy::crtp<%1%>::step1()";

            using namespace boost::math::policies;
            if( ( this->step1_cnt_++ ) > this->max_step1_cnt() ){
                 raise_evaluation_error( //<boost::uintmax_t>
                    name.c_str(),
                    "step1_cnt_ exceeded limit = %1%", 
                    this->max_step1_cnt(), P());
            }
            // line 10 : case mean = 0;
            
            this->u_ = urng();												//13
            if( this->u() > this->p1() ){ 
            	// Reconciliation with Fortran listing :
                // ptail = p2 + p3 = 1-p1. 
                // u' ~ 1-u. (u'<ptail) <=> (1-u<p2+p3) <=> (u > p1)
            	return this->step3( urng );
            }else{
                return this->step2( urng );
            }	
		}

		template<typename U>
		Int step2(U& urng)const
        {
        	T z = this->random_z( urng ); 							        //15
        	this->x_ = ( this->sd1() * z ) + parameters_::loc1();
            if( 
                ( this->x() > this->delta() ) || ( this->x() < ( -this->m1() ) ) 
            )
            { 
            	return this->step1( urng );
            }else{
                using namespace std;
            	// y is rounded away from zero
                if( this->x() <= -parameters_::eps /*strictly negative*/)
                {
                    this->i_y_ = floor( this->x() );
                }else{
                    this->i_y_ = ceil( this->x() );
                }
                T e  = this->random_exp1(urng);
                this->v_ = -( e + pow( z, 2 ) / parameters_::two ) + this->c1();
                return this->step4( urng );
            }
        }

		template<typename U>
		Int step3(U& urng)const
        {
        
            // Reconciliation with Fortran listing :
            // pbody = p3 = 1-(p1+p2) 
            // u' ~ 1-u. (u'<pbody) <=> (1-u<p3) <=> (u > p1+p2)
        	if( this->u() > this->p1() + this->p2() ){ 							
            	this->i_y_ = this->i_mean(); 
                return this->i_y();
            }else{
                using namespace std;
            	T e1 = this->random_exp1( urng );
            	T e2 = this->random_exp1( urng );
            	this->x_ = this->delta() + e1 / this->shape2();				//51 
            	this->i_y_ = TInt::convert( ceil( this->x() ) );
            	this->v_ = - ( 
                	e2 + this->shape2() * ( parameters_::one + this->x() )
                );
            	return this->step4( urng );
            }
        }

		template<typename U>
		Int step4(U& urng)const
        {
            const Step4& derived = static_cast<const Step4&>(*this);		
            if( derived.accept() ){
            	return this->i_y();
            }else{
				return this->step1( urng );            
            }
		}

		template<typename U>
		T random_z(U& urng)const
        {
        	typedef boost::normal_distribution<T> d_;
            static d_ d = d_( parameters_::zero, parameters_::one );
            return d( urng );
        }

		template<typename U>
		T random_exp1(U& urng)const
        {
        	typedef boost::exponential_distribution<T> d_;
            static d_ d = d_( parameters_::one );
            return d( urng );
        }

		// Parameter
		Int i_mean_;
        
        // These are quantities that vary throughout sampling
		mutable T	u_;
        mutable T 	x_;
        mutable Int i_y_;
        mutable T 	v_;
        
        // Implementation detail
        mutable Int step1_cnt_;
        mutable Int max_step1_cnt_;

        const Int& 	i_mean()const{ return this->i_mean_; } 
        const T& 	u()const{ return this->u_; } 
        const T& 	x()const{ return this->x_; } 
        const Int& 	i_y()const{ return this->i_y_; } 
        const T& 	v()const{ return this->v_; } 
        const Int& 	max_step1_cnt()const{ return this->max_step1_cnt_; } 


	};

}// devroye
}// poisson
}// random
}// boost

#endif 

