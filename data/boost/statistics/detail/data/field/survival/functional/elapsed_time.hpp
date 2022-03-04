//////////////////////////////////////////////////////////////////////////////
// data::field::survival::functional::elapsed_time.hpp         				//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_FUNCTIONAL_ELAPSED_TIME_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_FUNCTIONAL_ELAPSED_TIME_HPP_ER_2010
#include <boost/statistics/detail/data/field/framework/float_valued.hpp>
#include <boost/statistics/detail/data/field/survival/fields/entry_time.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace field{
namespace functional{

	template<typename T>
 	struct elapsed_time{
    	typedef typename field::meta::entry_time<T>::type f_;
    
		typedef T result_type;

		elapsed_time(const T& t):t_(t){}
        
        T operator()(const f_& t)const{
        	return field::elapsed_time(f,this->t_);
        }

		private:
		T t_;          
             
    };
    
}// functional
}// field
}// data
}// detail
}// statistics
}// boost

#endif
