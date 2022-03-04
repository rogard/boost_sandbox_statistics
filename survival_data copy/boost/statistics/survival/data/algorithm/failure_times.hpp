///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::algorithm::failure_times.hpp                  //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_ALGORITHM_FAILURE_TIMES_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_ALGORITHM_FAILURE_TIMES_HPP_ER_2009
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/matrix_view/algorithm/transform_column.hpp> 
#include <boost/statistics/survival/data/data/record.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{
        
    template<unsigned k,typename ItR,typename ItO>
    ItO
    failure_times(
        ItR b,              // records
        ItR e,
        unsigned stride,    
        ItO i_o             // output
    )
    {
        typedef typename iterator_value<ItR>::type record_;
        return matrix_view::transform_column<k>(
            b,
            e,
            stride,
            lambda::bind(&record_::failure_time,lambda::_1),
            i_o
        );
    }

}// data
}// survival
}// statistics
}// boost

#endif