///////////////////////////////////////////////////////////////////////////////
// distribution::model::key::prior_model_dataset_spec.hpp                    //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_KEY_PRIOR_MODEL_PRIOR_MODEL_DATASET_SPEC_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_KEY_PRIOR_MODEL_PRIOR_MODEL_DATASET_SPEC_HPP_ER_2009
#include <boost/parameter/parameters.hpp>
#include <boost/statistics/detail/distribution/model/key/prior.hpp>
#include <boost/statistics/detail/distribution/model/key/model.hpp>
#include <boost/statistics/detail/distribution/model/key/dataset.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{

    struct prior_model_dataset_spec{
        typedef boost::parameter::parameters<
            boost::parameter::required<tag::prior>,
            boost::parameter::required<tag::model>,
            boost::parameter::required<tag::dataset>
        > type;
    };

}// model
}// distribution
}// detail
}// statistics
}// boost

#endif
