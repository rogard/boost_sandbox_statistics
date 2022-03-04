//////////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::poisson_devroye::detail::q_function::using_factorial.hpp //
//                                                                              //
//                                                                              //
//  (C) Copyright 2010 Erwann Rogard                                            //
//  Use, modification and distribution are subject to the                       //
//  Boost Software License, Version 1.0. (See accompanying file                 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_USING_FACTORIAL_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_USING_FACTORIAL_ER_2010
#include <cmath>
#include <boost/mpl/bool.hpp>
#include <boost/math/special_functions/factorials.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{

namespace factorial_method{
    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,const IntT& converter);
}

    struct using_factorial{ using_factorial(){} };

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,
        const IntT& converter,using_factorial/*method*/)
    {
        return factorial_method::fun<T>(i_mean,i_y,p,converter);
    }

namespace factorial_method{

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,const IntT& converter)
    {
        T r = IntT::convert( 0 );
        if(i_y!=0){
            T m = IntT::convert( i_mean );
            T y = IntT::convert( i_y );
            T mp1 = IntT::convert( i_mean + 1 );
            r += first_half(m,y,p);
            if(i_y<0) r += second_half(m,i_y,p,boost::mpl::bool_<false>());
            if(i_y>0) r += second_half(mp1,i_y,p,boost::mpl::bool_<true>());
        }
        return r;
    }  

    template<typename T,typename P>
    T first_half(const T& m,const T& y,const P& p){ return y * log( m ); }

    template<typename T,typename Int,typename P>
    T second_half(const T& mp1,const Int& i_y,const P& p,
        boost::mpl::bool_<true>/*y>0*/)
    {
        BOOST_ASSERT(i_y>0);
        using namespace boost::math;
        return -log( rising_factorial<T>(mp1,i_y,p) );
    }
    template<typename T,typename Int,typename P>
    T second_half(const T& m,const Int& i_y,const P& p,
         boost::mpl::bool_<false>/*y>0*/)
    {
        BOOST_ASSERT(i_y<0);
        using namespace boost::math;
        return log( falling_factorial<T>(m,-i_y,p) );
    }

}// factorial_method
}// q
}// devroye
}// poisson
}// random
}// boost

#endif

