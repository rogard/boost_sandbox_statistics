///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::covariates_responses_mngr.hpp           //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_COVARIATES_RESPONSES_MNGR_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_COVARIATES_RESPONSES_MNGR_HPP_ER_2009
#include <boost/range.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/statistics/survival/data/covariates_mngr.hpp>
#include <boost/statistics/survival/data/responses_mngr.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<
        typename T,
        typename X
    >
    class covariates_responses_mngr : 
        public covariates_mngr<X>, 
        public responses_mngr<T>
    {
        public:
        typedef covariates_mngr<X>              super1_;
        typedef responses_mngr<T>               super2_;   

        // [ Construction ]
        covariates_responses_mngr();
        template<typename It> 
        covariates_responses_mngr(It b_x,It e_x); // x values
        
        // [ Update ]
        template<typename It>
        void update(
            It b_r,It e_r, // records
            const T& t
        );   

        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

    };

    template<typename T,typename X>
    covariates_responses_mngr<T,X>::covariates_responses_mngr()
    :super1_(),super2_(){}

    template<typename T,typename X>
        template<typename It>
    covariates_responses_mngr<T,X>::covariates_responses_mngr(It b_x,It e_x)
    :super1_(b_x,e_x),
    super2_(){}

    // [ Update ]
    template<typename T,typename X>
    void covariates_responses<T,X>::update(
        It b_r, It e_r,
        const T& t
    )
    {
        this->update_responses(b_r,e_r,t);
        this->update_covariates(boost::size(this->reponses()));
    }

    // [ Archive ] 
    template<typename T,typename X>
    template<class Archive>
    void covariates_responses<T,X>::serialize(
        Archive & ar, 
        const unsigned int version
    )
    {
        ar & boost::serialization::base_object<super1_>(*this);
        ar & boost::serialization::base_object<super2_>(*this);
    }


}// data
}// survival
}// statistics
}// boost

#endif






