///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::default_parameter_records.hpp     //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_PARAMETER_RECORDS_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_DEFAULT_PARAMETER_RECORDS_HPP_ER_2009
#include <algorithm>
#include <ext/algorithm> // is_sorted
#include <iterator>
#include <boost/serialization/base_object.hpp>
#include <boost/range.hpp>
#include <boost/functional/clock.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/statistics/model/wrap/unary/parameter.hpp>
#include <boost/statistics/model/wrap/unary/model.hpp>
#include <boost/statistics/model/wrap/aggregate/model_parameter.hpp>
#include <boost/statistics/survival/data/data/mngr/records.hpp>
#include <boost/statistics/survival/data/data/mngr/default_covariates_model.hpp>
#include <boost/statistics/survival/data/random/default_batch.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    // Same as dataset_y but can self-generate records by internally using
    // default_batch
    //
    // P parameter type
    template<typename T,typename P>
    class default_parameter_records_mngr : public records_mngr<T>{
        typedef records_mngr<T> super_t;
        typedef statistics::model::parameter_wrapper<P> parameter_wrapper_type; 
        
        public:
        typedef functional::clock<T>    clock_type;

        // [ Construction ]
        default_parameter_records_mngr();
        default_parameter_records_mngr(const P&);
        
        // [ Update ]
        // Generates records at the back of container
        template<typename N,typename X,typename M,typename U>
        void back_generate(
            N n,
            default_covariates_model_mngr<X,M> cm,
            const clock_type& c,
            U& urng
        );

        template<typename N,typename X,typename M,typename U>
        void back_generate(
            N n,
            default_covariates_model_mngr<X,M> cm,
            const T& t,     // clock parameters
            const T& delta,
            U& urng
        );

        void set_parameter(const P& p);

        // [ Access ] 
        parameter_wrapper_type parameter_wrapper()const;

        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

        // [ Variables ]
        P p_;
    };

    // [ Construction ]
    template<typename T,typename P>
    default_parameter_records_mngr<T,P>::default_parameter_records_mngr(){}

    template<typename T,typename P>
    default_parameter_records_mngr<T,P>::default_parameter_records_mngr(
        const P& p
    )
    :p_(p){}
    
    // [ Update ]
    
    template<typename T,typename P>
    void default_parameter_records_mngr<T,P>::set_parameter(const P& p)
    {
        this->p_ = p;
    }
    
    template<typename T,typename P>
        template<typename N,typename X,typename M,typename U>
    void default_parameter_records_mngr<T,P>::back_generate(
        N n,
        default_covariates_model_mngr<X,M> cm, 
        const clock_type& c, 
        U& urng
    ){
        typedef default_covariates_model_mngr<X,M>          cm_;
        typedef typename cm_::x_values_type                 rx_;
        typedef random::meta_default_batch<T,M,P,rx_>       meta_;
        typedef typename meta_::type                        batch_;
        typedef variate_generator<U&,batch_>                vg_; 
        typedef statistics::model::model_parameter_<M,P>    mp_;

        typename meta_::rcov_ r_x = meta_::rcov(
            cm.x_values(), 
            0,
            n
        );

        mp_ mp(
            cm.model_wrapper(),
            this->parameter_wrapper()
        );
        batch_ b = meta_::make( 
            mp,
            c, 
            r_x
        );

        vg_ vg( urng, b ); 
        std::generate_n(
            std::back_inserter( this->records_ ),
            n,
            vg
        ); 

        BOOST_ASSERT(
            is_sorted(
                boost::begin( this->records() ),
                boost::end( this->records() )
            )
        );// clock is supposed to tick forward

    }

    template<typename T,typename P>
        template<typename N,typename X,typename M,typename U>
    void default_parameter_records_mngr<T,P>::back_generate(
        N n,
        default_covariates_model_mngr<X,M> cm,
        const T& t,
        const T& delta,
        U& urng
    )
    {
        return default_parameter_records_mngr<T,P>::back_generate(
            n,
            cm, 
            clock_type(t,delta), 
            urng
        );        
    }

    // [ Access ] 
    template<typename T,typename P>
    typename default_parameter_records_mngr<T,P>::parameter_wrapper_type 
    default_parameter_records_mngr<T,P>::parameter_wrapper()const{
        return parameter_wrapper_type(this->p_);
    }

    // [ Archive ]
    template<typename T,typename P>
    template<class Archive>
    void default_parameter_records_mngr<T,P>::serialize(
        Archive & ar, 
        const unsigned int version
    )
    {
        ar & boost::serialization::base_object<super_t>(*this);
        ar & (this->p_);
    }
    
}// data
}// survival
}// statistics
}// boost

#endif
