///////////////////////////////////////////////////////////////////////////////
// null_hypothesis.hpp                                                       //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_NULL_HYPOTHESIS_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_NULL_HYPOTHESIS_HPP_ER_2010
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/mpl/for_each.hpp>
#include <numeric>
#include <boost/lambda/lambda.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/accumulators/statistics/detail/weighted_count.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/crtp.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/null_hypothesis.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells_count.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/aux/lost_df_accumulator.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/aux/chi_square_summand.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/feature.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{

    template<typename Keys,typename T1>
    struct null_hypothesis<
        pearson_chi_square_statistic::tag::independence_between<Keys,T1>
    > : crtp<
            null_hypothesis<
                pearson_chi_square_statistic::tag::independence_between<Keys,T1>
            >,
            Keys,
            T1
        >
    {
        typedef pearson_chi_square_statistic::tag::independence_between<
            Keys,T1> feature_type;
        typedef null_hypothesis<feature_type> this_type;
        typedef crtp<this_type, Keys, T1> super_type;
         
        null_hypothesis(){}

        protected:
        
        template<typename AccSet,typename P>
        T1 statistic_impl(const AccSet& acc, const P& policy)
        {
            namespace ac = boost::accumulators;
            namespace ct = contingency_table;
            namespace ps = pearson_chi_square_statistic;
            namespace aux = ps::independence_between_aux;
            typedef typename AccSet::weight_type weight_;
            typedef typename ct::result_of::extract::cells<
                Keys,AccSet>::type ref_cells_;
            typedef aux::chi_square_summand<T1,Keys,AccSet> summand_;
        
            ref_cells_ ref_cells = ct::extract::cells<Keys>( acc );
            weight_ n_obs = ac::extract::weighted_count( acc );       
            summand_ s(acc, n_obs);
            return std::accumulate(
                boost::begin( ref_cells ),
                boost::end( ref_cells ),
                static_cast<T1>(0),
                boost::lambda::ret<T1>(boost::lambda::_1 + boost::lambda::_2),
                s
            );
        }
        
        template<typename AccSet,typename P>
        typename AccSet::weight_type 
        lost_degrees_of_freedom_impl(const AccSet& acc, const P& policy)
        {   
            namespace aux = independence_between_aux;
            namespace ps = pearson_chi_square_statistic;
            typedef boost::mpl::detail::wrapper<boost::mpl::_> op_;
            typedef typename AccSet::weight_type weight_;
            weight_ lost_df = 0;
            boost::mpl::for_each<Keys,op_>(
                aux::make_lost_df_accumulator(acc, lost_df)
            );  
            return lost_df;
  	    }

    };

}// pearson_chi_square_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
