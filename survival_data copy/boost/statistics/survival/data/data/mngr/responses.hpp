///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::responses.hpp                     //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_RESPONSES_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_RESPONSES_HPP_ER_2009
#include <algorithm>
#include <iterator>
#include <vector>
#include <boost/range.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/statistics/survival/data/data/record.hpp>
#include <boost/statistics/survival/data/algorithm/events.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<typename T>
    class responses_mngr{
        public:

        typedef event<T>                                        response_type;
        typedef std::vector<response_type>                      responses_type;

        // [ Construction ]
        responses_mngr();

        // [ Update ]
        void clear_responses();
        template<typename It>
        void update_responses(
            It b_r,It e_r, // records
            const T& t
        );

        // [ Access ]
        const responses_type&   responses()const;
        const T&                time()const;

        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

        // [ Variables ] 
        responses_type  responses_;
        T               t_;
    };


    // Implementation //

    // [ Construction ]
    template<typename T>
    responses_mngr<T>::responses_mngr(){}

    // [ Update ]

    template<typename T>
    void responses_mngr<T>::clear_responses(){ 
        (this->responses_).clear(); 
        this->t_ = static_cast<T>(0);
    }
    
    template<typename T>
    template<typename It>
    void responses_mngr<T>::update_responses(It b_r,It e_r,const T& t){
        this->responses_.clear();
        this->responses_.reserve( std::distance(b_r,e_r) );
        events(
            b_r,
            e_r,
            t,
            std::back_inserter( this->responses_ )
        );
        this->t_ = t;
    }
        
    // [ Access ]
    
    template<typename T>
    const typename responses_mngr<T>::responses_type&   
    responses_mngr<T>::responses()const{
        return this->responses_;
    }

    template<typename T>
    const T&                
    responses_mngr<T>::time()const{
        return this->t_;
    }

    // [ Archive ]
        
    template<typename T>
        template<class Archive>
    void responses_mngr<T>::serialize(Archive & ar, const unsigned int version){
        ar & ( this->responses_ );
        ar & ( this->t_ );
    }

}// data
}// survival
}// statistics
}// boost

#endif