///////////////////////////////////////////////////////////////////////////////
// distribution::model::models::likelihood::iid::detail::lpdf.hpp            //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_DETAIL_LPDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_DETAIL_LPDF_HPP_ER_2009
#include <numeric>
#include <boost/range.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/function.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/statistics/detail/traits/remove_cvref.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution_common/distributions/reference/wrapper.hpp>
#include <boost/statistics/detail/distribution_common/distributions/reference/log_unnormalized_pdf.hpp>
#include <boost/statistics/detail/distribution_common/functor/log_unnormalized_pdf.hpp>
#include <boost/statistics/detail/distribution/model/models/likelihood/iid/iid.hpp>
#include <boost/statistics/detail/distribution/model/models/likelihood/iid/detail/lpdf.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{
namespace detail{

    template<typename M,typename D>
    struct lpdf_iid_likelihood{
        typedef model::iid_likelihood<M,D> l_;
        typedef typename distribution::meta::value< l_ >::type value_type;

        template<typename P>
        static value_type call(const l_&l,const P& p)
        {
            typedef typename l_::model_type m_;
            typedef typename l_::dataset_type d_;
            typedef 
                typename statistics::detail::traits::add_cref<m_>::type cref_m_;
            typedef 
                typename statistics::detail::traits::add_cref<d_>::type cref_d_;
        
            typedef distribution::reference_wrapper<cref_m_> ref_;
            typedef distribution::functor::log_unnormalized_pdf_<ref_> f_;

            cref_m_ m = l.model();
        
            m.set_parameter(p);
            ref_ ref(m);
            f_ f(ref);
    
            typedef boost::function<
                value_type(const value_type&,const value_type&)
            > outer_;
            outer_ outer = boost::lambda::_1 + boost::lambda::_2;

            return std::accumulate(
                boost::begin(l.dataset()),
                boost::end(l.dataset()),
                static_cast<value_type>(0),
                boost::lambda::bind(
                    outer,
                    boost::lambda::_1,
                    boost::lambda::bind<value_type>(f,boost::lambda::_2)
                )
            );
        }
    };

}// detail
}// model
}// distribution    
}// detail
}// statistics
}// boost

#endif