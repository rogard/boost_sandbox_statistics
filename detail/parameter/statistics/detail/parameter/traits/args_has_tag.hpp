///////////////////////////////////////////////////////////////////////////////
// parameter::traits::args_has_tag.hpp                                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_PARAMETER_TRAITS_ARGS_HAS_TAG_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_PARAMETER_TRAITS_ARGS_HAS_TAG_HPP_ER_2009
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/binding.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace parameter{
namespace traits{

    template<typename Tag,typename Args,typename Default = parameter::void_>
    struct args_has_not_tag : boost::is_same<
        typename boost::parameter::binding<Args, Tag, void_>::type,
        void_
    >
    {};

    template<typename Tag,typename Args,typename Default = parameter::void_>
    struct args_has_tag : boost::mpl::not_<
        ags_has_has_not_tag<Tag,Args,Default>
    >
    {};

}// traits
}// parameter
}// detail
}// statistics
}// boost

#endif