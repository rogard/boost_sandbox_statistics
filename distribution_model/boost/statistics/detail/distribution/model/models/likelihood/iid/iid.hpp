///////////////////////////////////////////////////////////////////////////////
// distribution::model::models::likelihood::iid::iid.hpp                     //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_IID_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_LIKELIHOOD_IID_IID_HPP_ER_2009
#include <boost/statistics/detail/traits/add_cref.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution/model/key/model.hpp>
#include <boost/statistics/detail/distribution/model/key/dataset.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{

    template<typename M,typename D>
    struct iid_likelihood
    {
        public:

        typedef M model_type;
        typedef D dataset_type;
        typedef typename detail::traits::add_cref<M>::type cref_m_;
        typedef typename detail::traits::add_cref<D>::type cref_d_;
        typedef typename distribution::meta::value<M>::type value_type;
        
        iid_likelihood(){}

        template<typename Args>
        iid_likelihood(cref_m_ m,cref_d_ d):m_(m),d_(d){}
        
        template<typename Args>
        iid_likelihood(const Args& args)
            : m_(args[keyword::model]),d_(args[keyword::dataset]){}
        
        iid_likelihood(const iid_likelihood& that) : m_(that.m_), d_(that.d_){}
            
        iid_likelihood& operator=(const iid_likelihood& that)
        {
            if(&that!=this)
            {
                m_ = that.m_;
                d_ = that.d_;
            }
            return (*this);
        }
        
        cref_m_ model()const{ return this->m_; }
        cref_d_ dataset()const{ return this->d_; }
        
        private:
        cref_m_ m_;
        cref_d_ d_;
    };

}// model
}// distribution
}// detail
}// statistics
}// boost

#endif