//////////////////////////////////////////////////////////////////////////////
// data::field::framework::fields::impl.hpp         						//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_FIELD_FRAMEWORK_FIELDS_IMPL_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_FIELD_FRAMEWORK_FIELDS_IMPL_HPP_ER_2010
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/parameter/keyword.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace field{

	template<typename Tag,typename T>
    class impl
    { 
		typedef boost::parameter::keyword<Tag> par_key_;

		public:
        typedef Tag key_type;
        typedef T data_type;

		impl(){}
        impl(const T& val)
        	:value(val){}
        template<typename Args>
        impl(const Args& args)
        	:value(
				args(par_key_::instance|T())
            ){}

        T value;
                                
        private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & this->value;
        }

	};


}// field        
}// data
}// detail
}// statistics
}// boost

#endif


