///////////////////////////////////////////////////////////////////////////////
// statistics::survival::data::data::mngr::records.hpp                       //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_RECORDS_HPP_ER_2009
#define BOOST_STATISTICS_SURVIVAL_DATA_DATA_MNGR_RECORDS_HPP_ER_2009
#include <algorithm>
#include <iterator>
#include <vector>
#include <boost/range.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/statistics/survival/data/data/record.hpp>

namespace boost{
namespace statistics{
namespace survival{
namespace data{

    template<typename T>
    class records_mngr{
        public:

        typedef record<T>                                       record_type;
        typedef std::vector<record_type>                        records_type;
        
        // [ Construction ]
        records_mngr();
        records_mngr(const records_mngr&);

        // [ Update ]
        void clear_records();
        template<typename It>
        void back_insert_records(It b,It e);

        // [ Access ]
        const records_type& records()const;

        protected:
        // [ Archive ]
        friend class boost::serialization::access;
        
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

        records_type    records_;
    };


    // Implementation //

    // [ Construction ]
    template<typename T>
    records_mngr<T>::records_mngr(){}

    // [ Update ]

    template<typename T>
    void records_mngr<T>::clear_records(){ 
        (this->records_).clear(); 
    }

    template<typename T>
    template<typename It>
    void records_mngr<T>::back_insert_records(It b,It e){ 
        std::copy(
            b,
            e,
            std::back_inserter(this->records_)
        );
    }
            
    // [ Access ]
    template<typename T>
    const typename records_mngr<T>::records_type&     
    records_mngr<T>::records()const{
        return this->records_;
    }
    
    // [ Archive ]
        
    template<typename T>
        template<class Archive>
    void records_mngr<T>::serialize(Archive & ar, const unsigned int version){
        ar & ( this->records_ );
    }

}// data
}// survival
}// statistics
}// boost

#endif