//////////////////////////////////////////////////////////////////////////////////
// survival::models::exponential::scalar::detail::lpdf_rt.hpp                   //
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_DETAIL_LPDF_RT_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_DETAIL_LPDF_RT_HPP_ER_2009
#include <stdexcept>
#include <string>
#include <cmath>
#include <boost/operators.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/event.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace exponential_model_{

    template<typename T,typename B>
    T lpdf_rt(
        const T& log_rate,
        const response::event<T,B>& e
    ){
    
        typedef std::string str_;
        static const str_ msg 
            = "exponential<T,right_truncated> : log_unnormalized_pdf";
        
        typedef T val_;
        
        val_ result = log_rate;
        result = exp( result );
        result *= (- e.time());
        try{
            if( boost::math::isinf(result) ){
                throw std::runtime_error(" isinf(result)");
            }
            if( boost::math::isnan(result) ){
                throw std::runtime_error(" isnan(result)");
            }
        }catch(std::exception ex){
            str_ str = msg;
            str += ex.what();
            throw std::runtime_error(str);
        }
        if(e.failure()){
            result += log_rate;
        }
        return result;
    }

}// exponential_model_
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif