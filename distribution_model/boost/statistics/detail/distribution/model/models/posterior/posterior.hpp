///////////////////////////////////////////////////////////////////////////////
// distribution::model::models::likelihood::posterior.hpp                    //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_POSTERIOR_POSTERIOR_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_MODEL_MODELS_POSTERIOR_POSTERIOR_HPP_ER_2009
#include <boost/statistics/detail/traits/add_cref.hpp>
#include <boost/statistics/detail/mpl/nested_type.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution/model/key/prior.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace model{

    template<typename Pr,typename L>
    class posterior : public L
    {

        typedef Pr prior_type;
        typedef typename 
            statistics::detail::traits::add_cref<prior_type>::type cref_p_;

        public:

        typedef typename distribution::meta::value<L>::type value_type;
    
        posterior(){}
        
        posterior(cref_p_ p,const L& likelihood):p_(p),L(likelihood){}
        
        posterior(cref_p_ p,typename L::cref_m_ m,typename L::cref_d_ d)
         : L(m,d),p_(p){} 
    
        template<typename Args>
        posterior(const Args& args) : L(args),p_(args[keyword::prior]){}

        posterior(const posterior& that)
            :   L(static_cast<const L&>(*this)),p_(that.p_){}

        cref_p_ prior()const{ return this->p_; }
            
        private:
        cref_p_ p_;
        
    };

}// model
}// distribution
}// detail
}// statistics
}// boost

#endif

