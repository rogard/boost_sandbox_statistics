///////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::right_truncated::event.hpp        		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_EVENT_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_EVENT_HPP_ER_2009
#include <limits>
#include <ostream>
#include <boost/format.hpp>
#include <boost/operators.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <boost/statistics/detail/math/constant/shortcut.hpp>
#include <boost/statistics/detail/math/function/versatile_equal.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace response {

    // Abstraction for failure indicator and event time.
    //
    // B == T can be useful to represent a proportion of failures (see
    // mean_event)
    template<typename T,typename B = bool>
    class event : equality_comparable<event<T,B> >{
        typedef statistics::detail::math::constant::shortcut<T> const_;
        public:
        typedef T value_type;
        typedef B failure_type;
        // Construction 
        event():failure_(false),time_(const_::inf){}
        explicit event(B isf,value_type rt):failure_(isf),time_(rt){}
        event(const event& that):failure_(that.failure_),time_(that.time_){}
        event& operator=(const event& that){
        	if(&that!=this){
            	failure_ = (that.failure_);
            	time_ = (that.time_);            
        	}
        	return *this;
    	}

        // Access 
        B failure()const{ return failure_; }
        value_type time()const{ return time_; }
            
        // Operators 
        bool operator==(const event& e)
    	{
        	bool eq_1 = math::function::versatile_equal( 
            	e.time(),
            	(this->time())
        	);
        	bool eq_2 = math::function::versatile_equal(
            	(this->failure_) , (e.failure())
        	);
        	return  (eq_1 && eq_2);    
    	}
        
        protected:
        B failure_;         //!censored
        value_type time_;   //since entry time
    };

    template<typename T,typename B>
    std::ostream& operator<<(std::ostream& out,const event<T,B>& e){
        static const char* str = "(%1%,%2%)";
        typedef boost::format f_;
        f_ f(str);
        f % e.failure() % e.time();
        out << f.str();
        return out;
    }
            
}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif