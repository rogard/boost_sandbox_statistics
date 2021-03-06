///////////////////////////////////////////////////////////////////////////////
// statistics::detail::tuple::meta::remove_cv.hpp                            //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_TUPLE_META_REMOVE_CV_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_TUPLE_META_REMOVE_CV_HPP_ER_2009
#include <boost/type_traits.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace tuple{
namespace meta{
        
    template<typename T>
    struct tuple_remove_cv{

        typedef typename tuples::element<0,T>::type first_;
        typedef typename tuples::element<1,T>::type second_;

        typedef tuple<
            typename remove_cv<first_>::type,
            typename remove_cv<second_>::type
        > type;

    };
    
}// meta
}// tuple
}// detail
}// statistics
    
#endif