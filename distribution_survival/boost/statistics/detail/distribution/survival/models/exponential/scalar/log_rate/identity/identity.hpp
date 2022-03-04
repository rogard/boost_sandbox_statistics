//////////////////////////////////////////////////////////////////////////////////
// survival::modelss::exponential::log_rate::identity::identity.hpp             //
//                                                                              //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                   //
//  Software License, Version 1.0. (See accompanying file                       //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_LOG_RATE_IDENTITY_IDENTITY_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_EXPONENTIAL_LOG_RATE_IDENTITY_IDENTITY_HPP_ER_2009

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace exponential_model_{
namespace log_rate{

    template<typename T>
    class identity 
    {

        public:
        identity(){}

        protected:
        template<typename X>
        T log_rate_impl( const X& predictor)const{ 
            return static_cast<T>(predictor); 
        }

    };
    
}// log_rage
}// exponential_model_
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif