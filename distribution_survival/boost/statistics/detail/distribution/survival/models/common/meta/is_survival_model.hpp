///////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::meta::is_survival_model.hpp               //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_COMMON_META_IS_SURVIVAL_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_COMMON_META_IS_SURVIVAL_MODEL_HPP_ER_2009
#include <boost/mpl/bool.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace meta{

    template<typename Model>
    struct is_survival_model : boost::mpl::bool_<false>{};
        
}// meta
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif