///////////////////////////////////////////////////////////////////////////////
// statistics::model::wrap::aggregate::prior_model.hpp                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_MODEL_WRAP_AGGREGATE_PRIOR_MODEL_HPP_ER_2009
#define BOOST_STATISTICS_MODEL_WRAP_AGGREGATE_PRIOR_MODEL_HPP_ER_2009
#include <boost/statistics/model/wrap/unary/prior.hpp>
#include <boost/statistics/model/wrap/unary/model.hpp>

namespace boost{
namespace statistics{
namespace model{

    template<typename D,typename M>
    class prior_model_ : 
        public model::prior_wrapper<D>, 
        public model::model_wrapper<M>
    {
        typedef model::prior_wrapper<D> prior_;
        typedef model::model_wrapper<M> model_;

    public:

        typedef prior_model_<D,M> prior_model_wrapper_type;
            
        // Construction
        prior_model_();
        prior_model_(prior_ p, model_ m);
        prior_model_(const prior_model_&);
            
    };

    // Implementation //

    // Implementation //
            
    template<typename D,typename M>
    prior_model_<D,M>::prior_model_() : prior_(), model_(){}
        
    template<typename D,typename M>
    prior_model_<D,M>::prior_model_( prior_ p, model_ m )
     : prior_( p ),model_( m ){}
        
    template<typename D,typename M>
    prior_model_<D,M>::prior_model_(const prior_model_& that)
    :prior_( that ), model_( that ){}

    // Free functions
        
    template<typename D,typename M>
    prior_model_<D,M> 
    make_prior_model(const D& p,const M& m){
        typedef prior_model_<D,M> result_type;
        return result_type(p,m);
    }

}// model
}// statistics
}// boost

#endif