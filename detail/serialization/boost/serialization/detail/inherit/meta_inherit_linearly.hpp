//////////////////////////////////////////////////////////////////////////////
// serialization::detail::inherit::meta_inherit_linearly.hpp                //
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SERIALIZATION_DETAIL_INHERIT_META_INHERIT_LINEARLY_HPP_ER_2010
#define BOOST_SERIALIZATION_DETAIL_INHERIT_META_INHERIT_LINEARLY_HPP_ER_2010
#include <boost/mpl/aux_/na_fwd.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/serialization/detail/inherit/inherit_linearly.hpp>

namespace boost{
namespace serialization{
namespace detail{

#ifndef BOOST_SERIALIZATION_DETAIL_INH_LIN_MAX_SIZE
#define BOOST_SERIALIZATION_DETAIL_INH_LIN_MAX_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#define BOOST_SERIALIZATION_DETAIL_INH_LIN_na boost::mpl::na

template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
	BOOST_SERIALIZATION_DETAIL_INH_LIN_MAX_SIZE,
    typename T,BOOST_SERIALIZATION_DETAIL_INH_LIN_na)>
struct meta_inherit_linearly
{
	typedef boost::mpl::vector<                                                 
        BOOST_PP_ENUM_PARAMS(BOOST_SERIALIZATION_DETAIL_INH_LIN_MAX_SIZE,T)                                       
    > components;

    typedef serialization::detail::inherit_linearly<components> type;
};

#undef BOOST_SERIALIZATION_DETAIL_INH_LIN_na

}// detail
}// serialization
}// boost

#endif