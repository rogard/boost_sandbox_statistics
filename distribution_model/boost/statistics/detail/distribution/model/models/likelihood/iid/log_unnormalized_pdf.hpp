///////////////////////////////////////////////////////////////////////////////
// distribution::model::likelihood::iid::log_unnormalized_pdf.hpp    	     //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#include <boost/statistics/detail/distribution/model/models/likelihood/iid/iid.hpp>
#include <boost/statistics/detail/distribution/model/models/likelihood/iid/detail/lpdf.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{

    template<typename M,typename D,typename P>
    typename distribution::model::detail::lpdf_iid_likelihood<M,D>::value_type
    log_unnormalized_pdf(
        const distribution::model::iid_likelihood<M,D>& l,
        const P& p
    )
    {
        typedef distribution::model::detail::lpdf_iid_likelihood<M,D> lpdf_;
        return lpdf_::call(l,p);
    }
    
}// model
}// distribution
}// detail
}// statistics
}// boost

#endif