///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::description.hpp                     		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_DESCRIPTION_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_DESCRIPTION_HPP_ER_2009
#include <string>
#include <boost/format.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/has_key.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/entry_time.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/failure_time.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/censoring_time.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{

    template<typename K,typename M>
    void
    description_impl(
        const M& m,
        boost::format& f,
        std::string& str2,
        boost::mpl::bool_<true>
    ){
        str2 += " ";
        str2 += (f%boost::fusion::at_key<K>(m)).str();
    }

    template<typename K,typename M>
    void
    description_impl(
        const M& m,
        boost::format& f,
        std::string& str2,
        boost::mpl::bool_<false>
    ){}


template<typename M>
std::string description(const M& m)
{
    typedef tag::entry_time     tag1;
    typedef tag::failure_time   tag2;
    typedef tag::censoring_time tag3;

    typedef boost::fusion::result_of::has_key<M,tag1> has1;
    typedef boost::fusion::result_of::has_key<M,tag2> has2;
    typedef boost::fusion::result_of::has_key<M,tag3> has3;

    std::string str = "(";

    typedef boost::format f_;
    
    if(has1::value)
    {
        f_ f("et = %1% ");
        typedef typename has1::type b_;
        description_impl<tag1>(m,f,str,b_());
    }
    if(has2::value)
    {
        f_ f("ft = %1% ");
        typedef typename has2::type b_;
        description_impl<tag2>(m,f,str,b_());
    }
    if(has3::value)
    {
        f_ f("ct = %1% ");
        typedef typename has3::type b_;
        description_impl<tag3>(m,f,str,b_());
    }
    
    str += ")";

    return str;
}

}// record                
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif