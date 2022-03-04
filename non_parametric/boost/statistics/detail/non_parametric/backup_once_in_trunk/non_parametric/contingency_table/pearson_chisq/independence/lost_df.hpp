///////////////////////////////////////////////////////////////////////////////
// lost_df.hpp                                                               //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_LOST_DF_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_LOST_DF_HPP_ER_2010
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/range.hpp>
#include <boost/accumulators/framework/depends_on.hpp> //contains_feature_of
#include <boost/accumulators/framework/accumulator_set.hpp> //visit_if
#include <boost/statistics/detail/non_parametric/contingency_table/factor/vec_levels.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/tag.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chisq_statistic{
namespace independence_between_aux{

    template<typename A>
    struct lost_df_accumulator{
    
        lost_df_accumulator(const A& acc,std::size_t& df)
            :acc_(acc),df_(df){}

        template<typename Key>
        void operator()(const boost::mpl::detail::wrapper<Key>& wrapper)const{
            namespace ns = contingency_table::extract;
            this->df_ += (ns::levels<Key>( this->acc_ ).size() - 1);
        }

        private:
        const A& acc_;
        mutable std::size_t& df_;
    };


    template<typename A>
    independence_between_aux::lost_df_accumulator<A> 
    make_lost_df_accumulator(const A& acc,std::size_t& df){
        return independence_between_aux::lost_df_accumulator<A>(acc,df);
    }

}// independence_between_aux

  	template<typename Keys,typename AccSet>
    std::size_t lost_degrees_of_freedom(
        const boost::mpl::detail::wrapper<
            pearson_chisq_statistic::tag::independence_between<Keys>
        >& statistic,    
        const AccSet& acc
    )
    {
        typedef boost::mpl::detail::wrapper<boost::mpl::_> op_;
        std::size_t result = 0;
        boost::mpl::for_each<Keys,op_>(
            independence_between_aux::make_lost_df_accumulator(acc, result)
        );
        return result;   
  	}

}// pearson_chisq_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
