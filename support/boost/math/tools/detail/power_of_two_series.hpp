///////////////////////////////////////////////////////////////////////////////
// power_of_two_series.hpp                                                   //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MATH_TOOLS_DETAIL_POWER_OF_TWO_SERIES_HPP_ER_2010
#define BOOST_MATH_TOOLS_DETAIL_POWER_OF_TWO_SERIES_HPP_ER_2010
#include <cmath>
#include <boost/numeric/conversion/converter.hpp>

namespace boost{ 
namespace math{
namespace tools{
namespace detail{

    template<typename T1 = long>
    struct power_of_two_series{
    
        power_of_two_series(start_value, start_exponent)
        :start_value_(start_value),n_( std::pow(2,start_exponent) ){}
    
        typedef T1 result_type;
        
        T1 operator()()const{
            typedef boost::numeric::converter<T1,long> converter_;
            this->n_ *= 2;
            return this->start_value_ + converter_::convert( n );
        }
            
        private:
        long n_;
        T1 start_value_;
        
    };
    
}// detail
}// tools
}// math
}// boost

#endif
