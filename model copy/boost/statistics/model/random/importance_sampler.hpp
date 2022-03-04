///////////////////////////////////////////////////////////////////////////////
// statistics::model::random::importance_generate.hpp                        //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_MODEL_RANDOM_IMPORTANCE_SAMPLER_HPP_ER_2009
#define BOOST_STATISTICS_MODEL_RANDOM_IMPORTANCE_SAMPLER_HPP_ER_2009
#include <vector>
#include <boost/range.hpp>
#include <boost/concept_check.hpp>
#include <boost/statistics/model/wrap/aggregate/prior_model_dataset.hpp>
#include <boost/importance_weights/algorithm/prepare_weights.hpp>
#include <boost/importance_sampling/generate.hpp>

namespace boost{
namespace statistics{
namespace model{
    
    // Bundles together some tasks associated with importance sampling
    template<typename T>
    class importance_sampler{
        public:
        typedef std::vector<T>                                  weights_type;
        typedef typename range_iterator< weights_type >::type   iter_;
        typedef importance_weights::prepare_weights<T>          pws_type; 
        
        importance_sampler();
        importance_sampler(const T& max_log);
        
        // [ Access ]
        const weights_type& weights()const; 
        // See importance_sampling::prepare_weights
        const pws_type& pws()const;                       

        // [ Update ]
        // weights  <- (log_posterior - lpdfs)
        template<
            typename D,
            typename M,
            typename Rx,
            typename Ry,
            typename ItP,
            typename ItL
        >
        iter_ 
        log_weights(
            prior_model_dataset_<D,M,Rx,Ry> pmd,
            ItP     b_p,       // proposal pars
            ItP     e_p,    
            ItL     b_lpdfs    // proposal log-pdfs
        );

        // weights <- exp(weights+offset)
        // Side effects : see importance_sampling::prepare_weights
        void prepare_weights();

        // Combines the two functions above
        template<
            typename D,
            typename M,
            typename Rx,
            typename Ry,
            typename ItP,
            typename ItL
        >
        void 
        prepare_weights(
            prior_model_dataset_<D,M,Rx,Ry> pmd,
            ItP     b_p,       // proposal pars
            ItP     e_p,    
            ItL     b_lpdfs    // proposal log-pdfs
        );

        template<typename ItP1,typename N,typename ItP,typename U>
        ItP1 
        generate_n(
            ItP1 b_post,
            N n,
            ItP b_p,    // same as that which was passed to prepare_weights
            U& urng
        );

        private:
        weights_type    weights_;
        pws_type        pws_;
    };

}// model
}// statistics


    template<typename ItP1,typename N,typename T,
        typename D,typename M,typename Rx,typename Ry,
        typename ItP,typename ItL,typename U
    >
    ItP1 
    generate_n(
        ItP1 b_post,
        N n,
        statistics::model::importance_sampler<T>& is,
        statistics::model::prior_model_dataset_<D,M,Rx,Ry> pmd,
        ItP     b_p,       
        ItP     e_p,    
        ItL     b_lpdfs,    
        U& urng
    ){
        is.prepare_weights(
            pmd,
            b_p,       
            e_p,    
            b_lpdfs
        );
        return is.generate_n(
            b_post,
            n,
            b_p,
            urng
        );
    }


    // Implementation //

namespace statistics{
namespace model{
    
    template<typename T>
    importance_sampler<T>::importance_sampler():pws_(){}
    
    template<typename T>
    importance_sampler<T>::importance_sampler(const T& max_log):pws_(max_log){}

    // Update
    template<typename T>
    template<
        typename D,
        typename M,
        typename Rx,
        typename Ry,
        typename ItP,
        typename ItL
    >
    typename importance_sampler<T>::iter_ 
    importance_sampler<T>::log_weights(
        prior_model_dataset_<D,M,Rx,Ry> pmd,
        ItP     b_p,        // proposal pars
        ItP     e_p,    
        ItL     b_lpdfs     // proposal log-pdfs
    ){
        this->weights_.resize(
            std::distance( b_p, e_p )
        );
        return log_posteriors2<T>(
            pmd,
            b_p,
            e_p,
            b_lpdfs,   
            boost::begin( this->weights_ )  
        );
    }

    template<typename T>
    void importance_sampler<T>::prepare_weights(){
        return this->pws_(
            boost::begin( this->weights_ ),
            boost::end( this->weights_ )
        );
    }

    template<typename T>
    template<
        typename D,
        typename M,
        typename Rx,
        typename Ry,
        typename ItP,
        typename ItL
    >
    void 
    importance_sampler<T>::prepare_weights(
        prior_model_dataset_<D,M,Rx,Ry> pmd,
        ItP     b_p,       
        ItP     e_p,    
        ItL     b_lpdfs   
    ){
        this->log_weights(
            pmd,
            b_p,       
            e_p,    
            b_lpdfs
        );
        return this->prepare_weights();
    }

    template<typename T>
    template<typename ItP1,typename N,typename ItP,typename U>
    ItP1 
    importance_sampler<T>::generate_n(
        ItP1 b_post,
        N n,
        ItP b_p,    
        U& urng
    ){
        return importance_sampling::generate(
            b_post,                            
            n,                  
            boost::begin( this->weights() ),
            boost::end( this->weights() ),
            b_p,                         
            urng
        );    
    }

    // Access
    template<typename T>
    const typename importance_sampler<T>::weights_type& 
    importance_sampler<T>::weights()const{
        return this->weights_;
    }
 
    template<typename T>
    const typename importance_sampler<T>::pws_type& 
    importance_sampler<T>::pws()const{
        return this->pws_;
    }                       

    
}// model
}// statistics
}// boost

#endif