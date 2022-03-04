///////////////////////////////////////////////////////////////////////////////
// fwd_cells.hpp                                                             //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_FWD_CELLS_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_FWD_CELLS_HPP_ER_2010

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace tag
{

    template<typename Keys> struct cells; 

}// tag
namespace result_of{
namespace extract{

    template<typename Keys,typename AccSet> struct cells;
        
}// extract
}// result_of
namespace extract{

  	template<typename Keys,typename AccSet>
    typename contingency_table::result_of::extract::template 
        cells<Keys,AccSet>::type
  	cells(AccSet const& acc);

}// extract
}// contingency_table
}// detail
}// statistics
}// boost

#endif
