///////////////////////////////////////////////////////////////////////////////
// statistics::model::concept::log_likelihood.hpp                            //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_MODEL_CONCEPT_HAS_LOG_LIKELIHOOD_HPP_ER_2009
#define BOOST_STATISTICS_MODEL_CONCEPT_HAS_LOG_LIKELIHOOD_HPP_ER_2009
#include <boost/concept_check.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/statistics/model/wrap/aggregate/model_data.hpp>

namespace boost{
namespace statistics{
namespace model{

    template<
        typename T,
        typename M,
        typename X,
        typename Y,
        typename P,
        typename B = mpl::empty_base
    >
    class HasLogLikelihood : B
    {        
        public:
        
        BOOST_CONCEPT_USAGE(HasLogLikelihood)
        {
            // TODO
            //T log_likelihood<T>(md, p); 
        }
    
        private:
        
        model_data_<M,X,Y> md;
        P p;
    };


}// model
}// statistics
}// boost

#endif