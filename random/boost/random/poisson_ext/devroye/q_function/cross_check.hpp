//////////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::poisson_devroye::detail::q_function::cross_check.hpp     //
//                                                                              //
//                                                                              //
//  (C) Copyright 2010 Erwann Rogard                                            //
//  Use, modification and distribution are subject to the                       //
//  Boost Software License, Version 1.0. (See accompanying file                 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_CROSS_CHECK_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_CROSS_CHECK_ER_2010
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <boost/random/poisson_ext/devroye/q_function/self_checking.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{


    template<typename T,typename Int,typename P>
    void cross_check(
        Int i_mean_loops,
        Int i_mean, // 1
        Int i_mean_factor, // 10
        const T& tol,
        const P& pol
    )
    {
        BOOST_ASSERT(tol>=0);
        BOOST_ASSERT(i_mean>0);

        typedef boost::numeric::converter<T,Int> conv_;
        typedef boost::numeric::bounds<Int> bounds_;
        typedef std::string s_;
        typedef boost::format f_;
        conv_ conv;
        Int max = bounds_::highest();
        
        for(Int i1 = 0; i1<i_mean_loops; i1++){
            try{
                //fun<T>(i_mean,0,pol,conv_(),meth_());
                for (
                    Int delta = 1, i_y = -i_mean; 
                    i_y <max; ++delta, i_y = -i_mean + (delta-1))
                {   
                    T val1 = fun<T>(i_mean,i_y,pol,conv,using_factorial());            
                    T val2 = fun<T>(i_mean,i_y,pol,conv,using_sum()); 
                    if((val1 > tol + val2) || (val2 > tol + val1)){
                        using namespace boost::math::policies;
                        s_ call = "(%1%,%2%)";
                        s_ msg = " (using_factorial) != %1% (using_sum)";
                        f_ f1(call); f1 % i_mean % i_y; 
                        f_ f2(msg); f2 % val2;
                        call = "q_fun<%1%>" + f1.str(); 
                        msg = "%1%" + f2.str(); 
                        raise_evaluation_error(
                            call.c_str(), msg.c_str(), val1, pol);
                    }
                }
            }catch(std::exception& e){
                std::cout << e.what() << std::endl;
            }
            
            i_mean *= i_mean_factor;
        }
    }

    template<typename T,typename Int>
    void cross_check(
        Int i_mean_loops,
        Int i_mean, // 1
        Int i_mean_factor, // 10
        const T& tol
    )
    {
        typedef boost::math::policies::policy<> pol_;
        cross_check<T,Int>(i_mean_loops,i_mean,i_mean_factor,tol,pol_());
    }

}// q
}// devroye
}// poisson
}// random
}// boost

#endif

