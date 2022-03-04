//////////////////////////////////////////////////////////////////////////////
// distribution::common::meta::is_discrete_support.hpp                      //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_META_IS_DISCRETE_SUPPORT_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_META_IS_DISCRETE_SUPPORT_HPP_ER_2010
#include <boost/mpl/bool.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace meta{

    template<typename D>
    struct is_discrete_support : boost::mpl::bool_<false>{};
    
}// meta
}// distribution
}// detail
}// statistics
}// boost

#endif
