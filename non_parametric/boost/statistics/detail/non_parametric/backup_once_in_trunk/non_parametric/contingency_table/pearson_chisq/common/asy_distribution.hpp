///////////////////////////////////////////////////////////////////////////////
// asy_distribution.hpp                                                      //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_COMMON_ASY_DISTRIBUTION_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_COMMON_ASY_DISTRIBUTION_HPP_ER_2010
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/policies/policy.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chisq_statistic{

    namespace result_of{

        template<typename T1,
            typename Policy = boost::math::policies::policy<> >
        struct asy_distribution{
            typedef boost::math::chi_squared_distribution<T1,Policy> type;
        };

    }// result_of
            
    template<typename T1,typename AccSet,typename H0,typename Policy>
    typename pearson_chisq_statistic::result_of::asy_distribution<T1,Policy>::type 
    asy_distribution(
        const H0& hypothesis,
        const AccSet& acc,
        const Policy& pol
    )
    {
        namespace ns = pearson_chisq_statistic;
        typedef typename ns::result_of::asy_distribution<
            T1,Policy>::type result_;
        T1 df = static_cast<T1>( ns::degrees_of_freedom( hypothesis, acc ) );
        return result_( df );
    }

    template<typename T1,typename AccSet,typename H0>
    typename pearson_chisq_statistic::result_of::asy_distribution<T1>::type 
    asy_distribution(
        const H0& hypothesis,
        const AccSet& acc
    ){
        typedef boost::math::policies::policy<> pol_;
        return asy_distribution<T1>( hypothesis, acc, pol_() );
    }

}// pearson_chisq_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
