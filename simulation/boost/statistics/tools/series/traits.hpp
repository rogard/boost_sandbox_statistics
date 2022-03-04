///////////////////////////////////////////////////////////////////////////////
// traits.hpp                                                                //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_TOOLS_DETAIL_SERIES_TRAITS_HPP_ER_2010
#define BOOST_STATISTICS_TOOLS_DETAIL_SERIES_TRAITS_HPP_ER_2010
#include <boost/mpl/apply.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/statistics/tools/series/data_field.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/detail/inherit/inherit_linearly.hpp>

namespace boost{ 
namespace statistics{
namespace detail{
namespace series{

    template<typename A,typename Tag>
    struct value_of_extract{
        typedef typename boost::mpl::apply< 
            A, Tag>::type::result_type cref_;
        typedef typename boost::remove_cv<
            typename boost::remove_reference<cref_>::type
        >::type type;
    };

    template<typename A,typename Tag>
    struct data_field_of{
       typedef detail::series::data<
           Tag,
           typename detail::series::value_of_extract<A,Tag>::type
       > type;
    };

    template<typename A,typename F>
    struct data_fields_of : boost::mpl::fold<
        F,
        detail::series::data_field_of<A,boost::mpl::_1>
    >{};

    template<typename A,typename F,typename R = boost::mpl::empty_base>
    struct data_of{
       typedef typename detail::series::data_fields_of<A,F>::type fields_;
       typedef boost::serialization::detail::inherit_linearly<fields_,R> type;
    };

}// series
}// detail
}// statistics
}// boost

#endif
