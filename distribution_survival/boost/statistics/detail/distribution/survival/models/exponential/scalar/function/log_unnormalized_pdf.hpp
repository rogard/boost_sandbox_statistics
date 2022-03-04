//////////////////////////////////////////////////////////////////////////////////
// survival::models::exponential::scalar::function::log_unnormalized_pdf.hpp    //
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_FUNCTION_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_FUNCTION_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#include <stdexcept>
#include <string>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/sequence/intrinsic/value_at_key.hpp>
#include <boost/statistics/detail/distribution/model/key/covariate.hpp>
#include <boost/statistics/detail/distribution/model/key/response.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/model.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/detail/lpdf_rt.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{

    template<typename T,typename D,typename U>
    T
    log_unnormalized_pdf(
        const exponential_model<T,D>& m,
        const U& unit
    ){

        typedef exponential_model<T, D> m_;
        typedef typename distribution::meta::value<m_>::type val_;

        typedef std::string str_;
    
        val_ log_rate  = m.log_rate( 
            boost::fusion::at_key<distribution::model::tag::covariate>(unit)
        );
        
        return exponential_model_::lpdf_rt(
            log_rate,
            boost::fusion::at_key<distribution::model::tag::response>(unit)
        );
    }
    
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif