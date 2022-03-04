///////////////////////////////////////////////////////////////////////////////
// impl.hpp                                                                  //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_IMPL_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_IMPL_HPP_ER_2010
#include <boost/accumulators/framework/accumulator_base.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace impl{

    template<typename Keys> 
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
}// contingency_table
}// detail
}// statistics
}// boost

#endif

