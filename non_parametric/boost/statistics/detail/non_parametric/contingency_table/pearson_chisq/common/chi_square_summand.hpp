///////////////////////////////////////////////////////////////////////////////
// chi_square_summand.hpp                                                    //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_COMMON_CHISQ_SUMMAND_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_COMMON_CHISQ_SUMMAND_HPP_ER_2010
#include <boost/numeric/conversion/converter.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{

    // The sum over all cells of this quantity is a fraction, f, of Pearson's 
    // Chi-square statistic. If (expected, observed) are expressed in counts,
    // f = 1. If they are expressed in frequencies, f = 1/n, where n is the
    // total number of counts.
    template<typename T1,typename T2,typename T3>
    T1  chi_square_summand(const T2& expected, const T3& observed)
    {
        typedef boost::numeric::converter<T1,T2> conv2_;
        typedef boost::numeric::converter<T1,T3> conv3_;
        T1 summand = conv2_::convert( expected ) - conv3_::convert( observed );
        summand *= summand;
        return summand / conv2_::convert( expected );
    }


}// pearson_chi_square_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
