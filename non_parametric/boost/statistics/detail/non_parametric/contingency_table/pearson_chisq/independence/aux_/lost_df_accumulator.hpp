///////////////////////////////////////////////////////////////////////////////
// lost_df_accumulator.hpp                                                   //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_AUX_LOST_DF_ACCUMULATOR_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_AUX_LOST_DF_ACCUMULATOR_HPP_ER_2010
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/factor/levels.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{
namespace independence_between_aux{

    template<typename A,typename N>
    struct lost_df_accumulator{

        lost_df_accumulator(const A& acc, N& df) : acc_(acc), df_(df){}

        template<typename Key>
        void operator()(const boost::mpl::detail::wrapper<Key>& wrapper)const
        {
            namespace ct = contingency_table;
            this->df_ += (ct::extract::levels<Key>( this->acc_ ).size() - 1);
        }

        private:
        const A& acc_;
        mutable N& df_;
    };

    template<typename A,typename N>
    independence_between_aux::lost_df_accumulator<A,N> 
    make_lost_df_accumulator(const A& acc, N& df)
    {
        namespace aux = independence_between_aux;
        return aux::lost_df_accumulator<A,N>(acc, df);
    }

}// independence_between_aux
}// pearson_chi_square_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
