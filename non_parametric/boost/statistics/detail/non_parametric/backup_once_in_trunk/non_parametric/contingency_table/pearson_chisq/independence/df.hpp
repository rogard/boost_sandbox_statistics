///////////////////////////////////////////////////////////////////////////////
// df.hpp                                                                    //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_DF_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_DF_HPP_ER_2010
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells_count.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/df_formula.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/lost_df.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/tag.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chisq_statistic{

  	template<typename Keys,typename AccSet>
    long degrees_of_freedom(
        const boost::mpl::detail::wrapper<
            pearson_chisq_statistic::tag::independence_between<Keys>
        >& statistic,    
        const AccSet& acc
    )
    {
        namespace ns = contingency_table;
        return pearson_chisq_statistic::degrees_of_freedom<long>(
            ns::cells_count<Keys>( acc ),
            pearson_chisq_statistic::lost_degrees_of_freedom( statistic, acc )
        );
    }

}// pearson_chisq_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif

