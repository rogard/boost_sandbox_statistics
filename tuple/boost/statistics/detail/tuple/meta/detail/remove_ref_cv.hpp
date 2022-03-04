///////////////////////////////////////////////////////////////////////////////
// statistics::detail::tuple::meta::detail::remove_ref_cv.hpp                //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_TUPLE_META_DETAIL_REMOVE_REF_CV_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_TUPLE_META_DETAIL_REMOVE_REF_CV_HPP_ER_2009
#include <boost/statistics/detail/tuple//meta/tuple_remove_cv.hpp>
#include <boost/statistics/detail/tuple//meta/tuple_remove_ref.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace tuple{
namespace meta{
namespace detail{
            
    template<typename T>
    struct remove_ref_cv : remove_cv<
        typename tuple_remove_ref<T>::type
    >{};
    
}// detail
}// meta
}// tuple
}// detail
}// statistics
}// boost
    
#endif
    