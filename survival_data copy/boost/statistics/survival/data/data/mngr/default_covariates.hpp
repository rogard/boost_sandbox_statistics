///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::default_covariates.hpp            //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_COVARIATES_HPP_ER_2009
#include <boost/iterator/range_cycle.hpp> 

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<typename X>
    class default_covariates_mngr{
        typedef range_cycle<>                                   meta_cycle_;
        typedef std::size_t                                     size_t;

        public:
        typedef std::vector<X>                                  x_values_type;
        typedef X                                               covariate_type;
        typedef typename meta_cycle_::apply<x_values_type>::type 
                                                                covariates_type;

        // [ Construction ]
        default_covariates_mngr();
        template<typename It> default_covariates_mngr(It b_x,It e_x);

        // [ Update ]
        template<typename N>
        void update_covariates(N n); 

        // [ Access ]
        covariates_type covariates()const; 
        const x_values_type& x_values()const;
        x_values_type& x_values(); // TODO remove. See default_records

        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

        size_t size_covariates_;
        mutable x_values_type x_values_; // TODO remove mutable see above
    };

    // [ Construction ]
    template<typename X>
    default_covariates_mngr<X>::default_covariates_mngr(){}

    template<typename X>
    template<typename It>
    default_covariates_mngr<X>::default_covariates_mngr(It b_x,It e_x)
    {
        (this->x_values_).reserve(std::distance(b_x,e_x));
        std::copy(
            b_x,
            e_x,
            std::back_inserter( this->x_values_ )
        );
    }
    
    // [ Update ]
    template<typename X>
        template<typename N>
    void default_covariates_mngr<X>::update_covariates(N n){
        this->size_covariates_ = static_cast<size_t>(n);
    }

    // [ Access ]
    template<typename X>
    typename default_covariates_mngr<X>::covariates_type 
    default_covariates_mngr<X>::covariates()const
    {
        return meta_cycle_::make( 
            this->x_values_, 
            0, 
            this->size_covariates_ 
        );
    } 

    template<typename X>
    const typename default_covariates_mngr<X>::x_values_type& 
    default_covariates_mngr<X>::x_values()const{
        return this->x_values_;
    }

    template<typename X>
    typename default_covariates_mngr<X>::x_values_type& 
    default_covariates_mngr<X>::x_values(){
        return this->x_values_;
    }

    // [ Archive ]
    template<typename X>
    template<class Archive>
    void default_covariates_mngr<X>::serialize(Archive & ar, const unsigned int version)
    {
        ar & (this->size_covariates_);
        ar & (this->x_values_);
    }
    
}// data
}// survival 
}// statistics
}// boost

#endif