///////////////////////////////////////////////////////////////////////////////
// cell_accumulator.hpp                                                      //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_DETAIL_CELL_ACCUMULATOR_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_DETAIL_CELL_ACCUMULATOR_HPP_ER_2010

namespace boost{
namespace statistics{
namespace detail{
namespace contingency_table{

    // This is equivalent to
    //     boost::lambda::bind<T1>(_1 + _2, _1, boost::lambda::bind(f,_2)) 
    template<typename T1,typename F>
    struct cell_accumulator
    {
     
        cell_accumulator(){};
        cell_accumulator(const F& f_):f( f_ ){}

        typedef T1 result_type;

        T1 operator()(T1& value, const C& cell)const
        {
            value += f( cell );
        }
    
        F f;
    
    };

}// contingency_table
}// detail
}// statistics
}// boost

#endif
