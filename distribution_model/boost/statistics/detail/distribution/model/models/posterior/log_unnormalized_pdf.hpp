///////////////////////////////////////////////////////////////////////////////
// distribution::model::models::posterior::log_unnormalized_pdf.hpp          //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_POSTERIOR_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_POSTERIOR_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#include <numeric>
#include <boost/range.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/function.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution_common/functor/log_unnormalized_pdf.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{

    template<typename Pr,typename L,typename P>
    typename distribution::meta::value<
        distribution::model::posterior<Pr,L>
    >::type
    log_unnormalized_pdf(
        const distribution::model::posterior<Pr,L>& post,
        const P& p
    )
    {
        typedef typename distribution::meta::value<
            distribution::model::posterior<Pr,L>
        >::type val_;
        val_ val = log_unnormalized_pdf(post.prior(),p);
        val += log_unnormalized_pdf(static_cast<const L&>(post),p);
        return val;

    }
    
}// model
}// distribution
}// detail
}// statistics
}// boost

#endif


