///////////////////////////////////////////////////////////////////////////////
// feature.hpp                                                               //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_TAG_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_TAG_HPP_ER_2010
#include <boost/mpl/always.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/independence/depends_on.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{
namespace impl{

    template<typename Keys,typename T1> 
    class independence_between : public boost::accumulators::accumulator_base
    {
        typedef boost::accumulators::dont_care dont_care_;

        public:

        typedef void result_type;

        independence_between(dont_care_){}
        
        void operator()(dont_care_)const{}

        result_type result(dont_care_)const{}

    };

}// impl
namespace tag
{
    template<typename Keys,typename T1 = double>
    struct independence_between
      : independence_between_aux::template depends_on<Keys>::type
    {
        typedef T1 value_type;
    
        typedef boost::mpl::always< 
            pearson_chi_square_statistic::impl::independence_between<Keys,T1> 
        > impl;
    };
    
}// tag
}// pearson_chi_square_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif

