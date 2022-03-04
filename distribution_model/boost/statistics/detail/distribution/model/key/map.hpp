///////////////////////////////////////////////////////////////////////////////
// distribution::model::key::map.hpp                                         //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_KEY_MAP_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_KEY_MAP_HPP_ER_2009
#include <boost/statistics/detail/distribution/model/tag/map.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/name.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{
namespace keyword{
  namespace 
  {
        boost::parameter::keyword<tag::map>& map
            = boost::parameter::keyword<tag::map>::get();
  }
}// keyword
}// model
}// distribution
}// detail
}// statistics
}// boost

#endif