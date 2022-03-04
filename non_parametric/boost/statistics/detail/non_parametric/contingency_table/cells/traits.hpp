///////////////////////////////////////////////////////////////////////////////
// traits.hpp                                                                //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_TRAITS_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_TRAITS_HPP_ER_2010
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/fwd_cells.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace cells_traits{

template<typename Keys,typename AccSet>
struct mapped_of{

    typedef typename contingency_table::result_of::extract::cells<
        Keys, AccSet>::type result_of_cells;
    typedef typename boost::remove_cv<
        typename boost::remove_reference<
            result_of_cells
        >::type
    >::type map_;
    typedef typename map_::mapped_type type;

};

template<typename Keys,typename AccSet>
struct size_of{

    typedef typename contingency_table::result_of::extract::cells<
        Keys, AccSet>::type result_of_cells;
    typedef typename boost::remove_cv<
        typename boost::remove_reference<
            result_of_cells
        >::type
    >::type map_;
    typedef typename map_::size_type type;

};

}// cells_traits
}// contingency_table
}// detail
}// statistics
}// boost

#endif
