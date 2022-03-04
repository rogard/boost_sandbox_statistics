//////////////////////////////////////////////////////////////////////////////////
// random::poisson_ex::poisson_devroye::detail::q_function::self_checking.hpp   //
//                                                                              //
//                                                                              //
//  (C) Copyright 2010 Erwann Rogard                                            //
//  Use, modification and distribution are subject to the                       //
//  Boost Software License, Version 1.0. (See accompanying file                 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)            //
//////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_SELF_CHECKING_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_Q_FUNCTION_SELF_CHECKING_ER_2010
#include <cmath>
#include <string>
#include <boost/format.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/random/poisson_ext/devroye/q_function/using_factorial.hpp>
#include <boost/random/poisson_ext/devroye/q_function/using_sum.hpp>
#include <boost/random/poisson_ext/devroye/q_function/lemma1.hpp>
#include <boost/random/poisson_ext/devroye/q_function/lemma2.hpp>
#include <boost/random/poisson_ext/devroye/q_function/bounds_tol.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{

    template<typename Q = q::using_sum>
    struct self_checking{ 
        self_checking(){} 
    };

    template<typename T,typename Int,typename P,typename IntT,typename Q>
    T fun(const Int& i_mean,const Int& i_y,const P& p,
        const IntT& converter,self_checking<Q>/*method*/)
    {
        typedef std::string s_;
        typedef boost::format f_;
        s_ exceptions;
        T tol = BOOST_RANDOM_POISSON_DEVROY_BOUNDS_TOL;                   
        T q;
        bool do_raise0 = false;
        try{
            q = fun<T>(i_mean,i_y,p,converter,Q());            
        }catch (std::exception& e) {
            do_raise0 = true;
            exceptions += e.what();
        }

        bool do_raise1 
            = lemma1::do_raise_error(q,tol,exceptions,i_mean,i_y,converter);
        bool do_raise2_1 
            = lemma2::do_raise_error1(q,tol,exceptions,i_mean,i_y,converter);
        bool do_raise2_2 
            = lemma2::do_raise_error2(q,tol,exceptions,i_mean,i_y,converter);
        bool do_raise2_3 
            = lemma2::do_raise_error3(q,tol,exceptions,i_mean,i_y,converter);

        if(do_raise0 || do_raise1 || do_raise2_1 || do_raise2_2 || do_raise2_3){
            using namespace boost::math::policies;
            f_ f("(%1%,%2%)"); f % i_mean % i_y;
            const s_ s = "devroye::q::fun<%1%>" + f.str();
            exceptions = "= %1%, error(s) : " + exceptions;
            return raise_evaluation_error(s.c_str(), exceptions.c_str(), q, p);
        }
        return q;
    }

}// q
}// devroye
}// poisson
}// random
}// boost

#endif

