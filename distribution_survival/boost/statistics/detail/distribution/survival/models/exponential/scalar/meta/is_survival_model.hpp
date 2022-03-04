///////////////////////////////////////////////////////////////////////////////////////
// survival::modelss::exponential::scalar::meta::is_survival_model.hpp         		 //
//                                                                                   //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                        //
//  Software License, Version 1.0. (See accompanying file                            //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                 //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_META_IS_SURVIVAL_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_SCALAR_META_IS_SURVIVAL_MODEL_HPP_ER_2009
#include <boost/mpl/bool.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/meta/is_survival_model.hpp>
#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/model.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace meta{

    template<typename T,typename L>
    struct is_survival_model< exponential_model<T,L> > 
        : boost::mpl::bool_<true>{};
    
}// meta
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif