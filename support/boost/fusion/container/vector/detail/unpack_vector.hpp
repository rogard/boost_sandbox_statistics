///////////////////////////////////////////////////////////////////////////////
// unpack_vector.hpp                                                         //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_UNPACK_VECTOR_HPP_ER_2010
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_UNPACK_VECTOR_HPP_ER_2010
#include <boost/fusion/container/vector/limits.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/void.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/detail/sequence_to_unpack_variadic.hpp>

namespace boost{
namespace fusion{
namespace detail{

    BOOST_DETAIL_MPL_SEQUENCE_TO_UNPACK_VARIADIC(
        boost::fusion::vector,
        unpack_vector,
        0,
        FUSION_MAX_VECTOR_SIZE, 
        boost::fusion::void_
    );
    
}// detail
}// fusion
}// boost

#endif