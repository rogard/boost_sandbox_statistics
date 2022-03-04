//////////////////////////////////////////////////////////////////////////////
// data::field::framework::fields::create.hpp         					    //
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_FIELD_FRAMEWORK_FIELDS_CREATE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_FIELD_FRAMEWORK_FIELDS_CREATE_HPP_ER_2010
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/name.hpp>
#include <boost/statistics/detail/data/field/framework/fields/impl.hpp>
#include <boost/statistics/detail/data/types/primitive/float.hpp>

// The macro below should be used inside the desired namespace to create a new
// field.
//
// Usage : 
// BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD(name,U)
// Expression					Result 
// keyword::name				empty class
// _keyword						boost::parameter::keyword<keyword::name>& const
// name<T>::type				a field type with default data-type U

#define BOOST_STATISTICS_DETAIL_DATA_NS boost::statistics::detail::data
#define BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD_NO_NS(name,U)				\
	BOOST_PARAMETER_NAME((BOOST_PP_CAT(_,name), keyword) name)				\
    template<typename T = U>											    \
    struct name{											                \
        typedef BOOST_STATISTICS_DETAIL_DATA_NS::field::impl<			    \
            keyword::name,				                                    \
            T															    \
        > type;															    \
    };																	    \
/**/
#define BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD_NO_NS_FLOAT(name)			\
	BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD_NO_NS(name,					\
    BOOST_STATISTICS_DETAIL_DATA_FLOAT_TYPE)								\
/**/

#define BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD(name,U)					\
namespace boost{															\
namespace statistics{														\
namespace detail{															\
namespace data{																\
namespace field{															\
	BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD_NO_NS(name,U)					\
}																			\
}																			\
}																			\
}																			\
}																			\
/**/

#define BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD_FLOAT(name)				\
	BOOST_STATISTICS_DETAIL_DATA_CREATE_FIELD(name,							\
    BOOST_STATISTICS_DETAIL_DATA_FLOAT_TYPE)								\
/**/


#endif
