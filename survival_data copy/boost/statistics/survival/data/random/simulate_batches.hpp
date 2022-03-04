///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::random::simulate_batches.hpp                  //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_RANDOM_SIMULATE_BATCHES_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_RANDOM_SIMULATE_BATCHES_HPP_ER_2009

#include <stdexcept>
#include <ostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/statistics/survival/data/data/mngr/default_parameter_records.hpp>
#include <boost/statistics/survival/data/data/mngr/default_covariates_prior_model.hpp>
#include <boost/typeof/typeof.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<typename T,typename X,typename D,typename M,typename N,typename U>
    void simulate_batches(
        std::ostream& ofs_pr_mngrs,  
//        std::ofstream& ofs_pr_mngrs,  
        default_covariates_prior_model_mngr<X,D,M>& xpm_mngr, //TODO const
        N n_batches,
        N n_records,
        const T& t,
        const T& delta_t,
        U& urng
    ){
        typedef BOOST_TYPEOF_TPL(
            boost::sample(
                (xpm_mngr.prior_model_wrapper()).prior(),
                urng
            )
        ) par_;

        typedef boost::archive::text_oarchive           oa_;
        typedef default_parameter_records_mngr<T,par_>  pr_mngr_;
        pr_mngr_ pr_mngr;

        oa_ oa_pr_mngrs(ofs_pr_mngrs); 
        for(unsigned i = 0; i<n_batches; i++){
            //records.clear();
            par_ par  = boost::sample( //TODO think about the unscope issue
                (xpm_mngr.prior_model_wrapper()).prior(),
                urng
            );

            pr_mngr.clear_records();
            pr_mngr.set_parameter( par );
            typedef default_covariates_model_mngr<X,M>      xm_mngr_;
            xm_mngr_& xm_mngr = static_cast<xm_mngr_&>(xpm_mngr); // TODO const
            pr_mngr.back_generate(
                n_records,
                xm_mngr,
                t,
                delta_t,
                urng
            );

            oa_pr_mngrs << pr_mngr; 
        }
    }
    
}// data
}// survival
}// statistics
}// boost

#endif