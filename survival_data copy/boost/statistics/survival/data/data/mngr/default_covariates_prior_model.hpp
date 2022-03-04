//////////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::default_covariates_prior_model.hpp   //
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_PRIOR_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_PRIOR_MODEL_HPP_ER_2009
#include <boost/statistics/model/wrap/aggregate/prior_model.hpp>
#include <boost/statistics/survival/data/data/mngr/default_covariates_model.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<typename X,typename D,typename M>
    class default_covariates_prior_model_mngr
        : public default_covariates_model_mngr<X,M>
    {
        typedef default_covariates_model_mngr<X,M> super_;
        public:
        typedef statistics::model::prior_model_<D,M> prior_model_wrapper_type;
        
        // [ Construction ]
        default_covariates_prior_model_mngr();
        template<typename It> 
        default_covariates_prior_model_mngr(
            It b_x,It e_x,      // x values
            prior_model_wrapper_type
        );

        // [ Access ]
        prior_model_wrapper_type 
        prior_model_wrapper()const;

        protected:
        D p_;
    };

    template<typename X,typename D,typename M>
    default_covariates_prior_model_mngr<X,D,M>
        ::default_covariates_prior_model_mngr(){}
    
    template<typename X,typename D,typename M>
    template<typename It> 
    default_covariates_prior_model_mngr<X,D,M>
            ::default_covariates_prior_model_mngr
    (
        It b_x,It e_x,      // x values
        prior_model_wrapper_type pm
    ):super_(b_x,e_x,pm),p_(pm.prior()){}
   
    template<typename X,typename D,typename M>
    typename 
        default_covariates_prior_model_mngr<X,D,M>::prior_model_wrapper_type 
    default_covariates_prior_model_mngr<X,D,M>::prior_model_wrapper()const
    {
        typedef statistics::model::prior_wrapper<D> prior_;
        return prior_model_wrapper_type(
            prior_(this->p_),
            this->model_wrapper()
        );
    }
    
}// data
}// survival
}// statistics
}// boost

#endif