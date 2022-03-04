///////////////////////////////////////////////////////////////////////////////
// data_field.hpp                                                            //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_TOOLS_DETAIL_SERIES_DATA_FIELD_HPP_ER_2010
#define BOOST_STATISTICS_TOOLS_DETAIL_SERIES_DATA_FIELD_HPP_ER_2010
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace boost{ 
namespace statistics{
namespace detail{
namespace series{
 
    // This data_field is meant to keep the result of extracting an 
    // accumulator_set<>'s feature specified by Tag, and evaluating to an 
    // object of type T.
    template<typename Tag,typename T>
    struct data_field
    {
        typedef T value_type;
                
        data_field(){}
        
        value_type value;
        
        private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & this->value;
        }
        
    };

	template<typename Tag,typename T>
	data_field<Tag,T>& 
    get_field(data_field<Tag,T>& field){ return field; }

    template<typename Tag,typename T>
	std::ostream&
    operator<<(std::ostream& os,const data_field<Tag,T>& field)
    {
        return (os << field.value);
    }

}// series
}// detail
}// statistics
}// boost

#endif
