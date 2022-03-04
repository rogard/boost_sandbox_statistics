//////////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::poisson_devroye::detail::q_function::using_sum.hpp       //
//                                                                              //
//                                                                              //
//  (C) Copyright 2010 Erwann Rogard                                            //
//  Use, modification and distribution are subject to the                       //
//  Boost Software License, Version 1.0. (See accompanying file                 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_USING_SUM_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_USING_SUM_ER_2010
#include <cmath>
#include <boost/mpl/bool.hpp>
#include <boost/math/special_functions/log1p.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{

namespace sum_method{
    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,const IntT& converter);
}
    struct using_sum{ using_sum(){} };

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,
        const IntT& converter,using_sum/*method*/)
    {
        return sum_method::fun<T>(i_mean,i_y,p,converter);
    }

namespace sum_method{

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const T& inv,const Int& i_y,const P& p,const IntT& converter,
        boost::mpl::bool_<false>/*y>0*/)
    {
        using namespace boost::math;
        BOOST_ASSERT(i_y<0);
        T j, r = IntT::convert( 0 );
        Int n = -( 1 + i_y ) + 1;
        for(Int i = 0; i < n; i++){
            j = IntT::convert( i );
            r += log1p(- inv * j, p );
        }
        return r;
    }

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const T& inv,const Int& i_y,const P& p,const IntT& converter,
        boost::mpl::bool_<true>/*y>0*/)
    {
        using namespace boost::math;
    
        BOOST_ASSERT(i_y>0);
        T j , r = IntT::convert( 0 );
        Int n = 1 + i_y;
        for(Int i = 1; i < n; i++){
            j = IntT::convert( i );
            r -= log1p( inv * j, p );
        }
        return r;
    }

    template<typename T,typename Int,typename P,typename IntT>
    T fun(const Int& i_mean,const Int& i_y,const P& p,const IntT& converter)
    {
        T r = IntT::convert( 0 );
        if(i_y!=0){
            T m = IntT::convert( i_mean );
            T inv = pow( m , -1);
            typedef boost::mpl::bool_<false> false_;
            typedef boost::mpl::bool_<true> true_;
            if(i_y<0) 
                r += sum_method::fun( inv, i_y, p , converter, false_());   
            if(i_y>0) 
                r += sum_method::fun( inv, i_y, p , converter, true_());   
        }
        return r;    
    }

}// sum_method
}// q
}// devroye
}// poisson
}// random
}// boost

#endif

