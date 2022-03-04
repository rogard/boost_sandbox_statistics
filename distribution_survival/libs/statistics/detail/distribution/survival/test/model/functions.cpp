///////////////////////////////////////////////////////////////////////////////////////////
// survival::test::model::functions.cpp                                                  //
//                                                                                       //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                            //
//  Software License, Version 1.0. (See accompanying file                                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                     //
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_TEST_MODEL_FUNCTIONS_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_TEST_MODEL_FUNCTIONS_HPP_ER_2009
#include <ostream>
#include <boost/concept/assert.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/map_fwd.hpp>

#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/include.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/model.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/function/log_unnormalized_pdf.hpp>

// Concepts must come after distributions
#include <boost/statistics/detail/distribution_common/concept/unary/log_unnormalized_pdf.hpp>
//#include <boost/statistics/detail/distribution_common/concept/unary/derivative_log_unnormalized_pdf.hpp>

#include <boost/statistics/detail/distribution_common/meta/wrapper/distribution.hpp>
#include <boost/statistics/detail/distribution_common/meta/wrapper/variable.hpp>
#include <boost/statistics/detail/distribution_common/meta/wrapper/probability.hpp>

#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/is_event.hpp>

#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/include/at_key.hpp>

template <typename T>
void test_model_functions(std::ostream& os)
{
    os << "test_functions - >" << std::endl;
    using namespace boost;
   
    namespace stat      = boost::statistics::detail;
    namespace dist		= stat::distribution;
    namespace dist_mo   = dist::model;
    namespace dist_su   = dist::survival;

    typedef fusion::map<
        fusion::pair<dist_mo::tag::covariate,T>,
        fusion::pair<
            dist_mo::tag::response,
            dist_su::response::event<T>
        >
    > unit_;

    typedef dist::meta::wrapper_variable<unit_> u_;
    typedef dist::meta::wrapper_probability<T,u_> p_u_; 

    {
        typedef dist_su::exponential_model<T>              			m_;
        typedef dist::meta::wrapper_distribution<m_,p_u_>          	w_;

        BOOST_CONCEPT_ASSERT((
            dist::concept::LogUnnormalizedPdf<w_>
        ));
    }

    
}

#endif