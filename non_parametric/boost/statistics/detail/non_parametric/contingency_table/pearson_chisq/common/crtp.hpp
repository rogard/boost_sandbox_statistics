///////////////////////////////////////////////////////////////////////////////
// crtp.hpp                                                                  //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_CRTP_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_CRTP_HPP_ER_2010
#include <boost/math/policies/policy.hpp>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/degrees_of_freedom.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells_count.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace contingency_table{

    template<typename D,typename Keys,typename T1>
    struct crtp
    {
         crtp(){}

        typedef boost::math::policies::policy<> default_policy_;

        const D& derived()const{ return static_cast<const D&>(*this); }

        // statistic :
        template<typename AccSet,typename P>
        T1 statistic(const AccSet& acc,const P& policy)const{
            return this->derived().statistic_impl( acc, policy );
        }
        template<typename AccSet>
        T1 statistic(const AccSet& acc)const
        {
            return this->statistic( acc, default_policy_() );
        }

        // lost_degrees_of_freedom :
        template<typename AccSet,typename P>
        typename AccSet::weight_type
        lost_degrees_of_freedom(const AccSet& acc,const P& policy)const
        {
            return this->derived().lost_degrees_of_freedom_impl( acc, policy );
        }
        template<typename AccSet>
        typename AccSet::weight_type
        lost_degrees_of_freedom(const AccSet& acc)const
        {
            return this->lost_degrees_of_freedom( acc, default_policy_() );
        }

        // degrees_of_freedom
        template<typename AccSet,typename P>
        typename AccSet::weight_type 
        degrees_of_freedom(const AccSet& acc,const P& policy)const
        {
            namespace ct = contingency_table;
            namespace ps = ct::pearson_chi_square_statistic;
            typedef typename AccSet::weight_type weight_;
            weight_ df =  ps::degrees_of_freedom<weight_>(
                ct::cells_count<Keys>( acc ),
                this->derived().lost_degrees_of_freedom_impl( acc, policy )
            );
                                  
        }

        template<typename AccSet>
        typename AccSet::weight_type 
        degrees_of_freedom(const AccSet& acc)const
        {
            return this->degrees_of_freedom( acc, default_policy_() );
        }

        // asy_distribution

        template<typename P = default_policy_>
        struct result_of_asy_distribution
        { 
            typedef boost::math::chi_squared_distribution<T1, P> type;
        };

        template<typename AccSet,typename P>
        typename result_of_asy_distribution<P>::type 
        asy_distribution(const AccSet& acc,const P& policy)
        {   
            typedef typename result_of_asy_distribution<P>::type result_;     
            typedef typename AccSet::weight_type weight_;
            typedef boost::numeric::converter<T1, weight_> converter_;
            T1 df = converter_::convert( 
                this->degrees_of_freedom( acc, policy ) );
            return result_( df );
        }

        template<typename AccSet>
        typename result_of_asy_distribution<>::type 
        asy_distribution(const AccSet& acc)
        {
            return this->asy_distribution( acc, default_policy_() );
        }

    };

}// contingency_table
}// detail
}// statistics
}// boost

#endif
