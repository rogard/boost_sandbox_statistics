///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::default_covariates_model.hpp      //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_MODEL_HPP_ER_2009
#include <algorithm>
#include <iterator>
#include <boost/statistics/model/wrap/unary/model.hpp>
#include <boost/statistics/survival/data/data/mngr/default_covariates.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    // Combines x_values and model into one class.
    // 
    // In generating batches of data, one for each of a set of model parameters,
    // using default_batch, these are two fixed components of the generation 
    // process, hence the rationale for combining them.
    template<typename X,typename M>
    class default_covariates_model_mngr 
        : public default_covariates_mngr<X>{
        typedef default_covariates_mngr<X> super_;
        public:
        typedef model::model_wrapper<M> model_wrapper_type;
        typedef std::vector<X>   x_values_type;

        // [ Construction ]
        default_covariates_model_mngr();
        template<typename It> default_covariates_model_mngr(
            It b_x,It e_x,      // x values
            model_wrapper_type
        );
        
        // [ Access ]
        model_wrapper_type model_wrapper()const;
        
        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);
        
        // [ Variables ]
        M m;
    };

    // [ Construction ]
    template<typename X,typename M>
    default_covariates_model_mngr<X,M>::default_covariates_model_mngr(){}
    
    template<typename X,typename M>
    template<typename It> 
    default_covariates_model_mngr<X,M>::default_covariates_model_mngr(
        It b_x,It e_x,
        model_wrapper_type w
    ):super_(b_x,e_x),m(w.model()){}

    // [ Access ]
    template<typename X,typename M>
    typename default_covariates_model_mngr<X,M>::model_wrapper_type 
    default_covariates_model_mngr<X,M>::model_wrapper()const
    {
        return model_wrapper_type(this->m);
    }

    // [ Archive ]
    template<typename X,typename M>
    template<class Archive>
    void default_covariates_model_mngr<X,M>::serialize(
        Archive & ar, 
        const unsigned int version
    )
    {
        ar & this->x_values_;
        ar & this->m;
    }
    
}// data
}// survival
}// statistics
}// boost

#endif