///////////////////////////////////////////////////////////////////////////////
// survival::modelss::exponential::scalar::model.hpp                   		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_MODEL_HPP_ER_2009
#include <boost/operators.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/statistics/detail/mpl/nested_type.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/exponential/include.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/log_rate/identity/identity.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{

    // TODO add an error policy

    template<
        typename T, 
        typename L = exponential_model_::log_rate::identity<T>, 
        typename Err = boost::math::policies::policy<>
    >
    class exponential_model : L{
    	// TODO Err

        public:
        typedef T value_type;

        //typedef exponential_model<T,L> distribution_type;
    
        exponential_model():L(){}
        exponential_model(const exponential_model& that) 
            : L(static_cast<const L&>(that)),b_(that.b_){}
        exponential_model& operator=(const exponential_model& that)
        {
            if(&that!=this)
            {
                static_cast<L&>(*this) = static_cast<const L&>(that);
                b_ = that.b_;
            }
            return (*this);
        }
                
        template<typename X>
        T log_rate(const X& x)const
        {
            T cross_prod =  static_cast<T>( x );
            cross_prod *= this->parameter() ;
            return this->log_rate_impl( cross_prod );
        }

        const T& parameter()const{ return this-> b_; }
        template<typename B>
        void set_parameter(const B& b)const{ this->b_ = b; }

        protected:

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version){
            ar & b_;
        }

        mutable T b_;
    };

}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif