//////////////////////////////////////////////////////////////////////////////
// random::poisson::devroye::q::lemma2.hpp                        	        //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_LEMMA2_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_LEMMA2_HPP_ER_2010
#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/format.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{
namespace lemma2{

    template<typename T,typename Int,typename IntT>
    inline 
    T lhs(const T& q, const Int& i_mean,const Int& i_y, const IntT& converter){
        return q + IntT::convert( i_y * ( i_y + 1 ) ) 
            / IntT::convert( 2 * i_mean );
    }

    template<typename T,typename Int,typename IntT>
    inline
    T upper_bound(const Int& i_mean,const Int& i_y, const IntT& converter){
        return IntT::convert( i_y * ( i_y + 1 ) * (2 * i_y + 1) )
         / IntT::convert( 12 * i_mean * i_mean );
    }

namespace impl{

    template<typename T,typename Int,typename IntT>
    inline 
    T lower_bound_common(
        const Int& i_mean,const Int& i_y,
        const IntT& converter, const T& den
    ){
        T ub = upper_bound<T>(i_mean,i_y,converter);
        T num = IntT::convert( (i_y * i_y) * ( (i_y + 1) * (i_y + 1) ) ); 
        return ub - num / den;
    }

    template<typename T,typename Int,typename IntT>
    inline 
    T lower_bound(
        const Int& i_mean,const Int& i_y,
        const IntT& converter, boost::mpl::bool_<true>/*y>=0*/
    ){
        T den = IntT::convert(12 * i_mean * i_mean * i_mean);
        return lower_bound_common<T>(i_mean,i_y,converter,den);
    }

    template<typename T,typename Int,typename IntT>
    inline
    T lower_bound(
        const Int& i_mean,const Int& i_y,
        const IntT& converter, boost::mpl::bool_<false>/*y<0*/
    ){
        T den = IntT::convert(12 * i_mean * i_mean * (i_mean + i_y + 1) );
        return lower_bound_common<T>(i_mean,i_y,converter,den);
    }

}//impl

    template<typename T,typename Int,typename IntT>
    inline 
    T lower_bound(const Int& i_mean,const Int& i_y,const IntT& converter){
        if(i_y >= 0){
           typedef boost::mpl::bool_<true> true_;
           return lemma2::impl::lower_bound<T>(i_mean,i_y,converter,true_());
        }else{
           typedef boost::mpl::bool_<false> false_;
           return lemma2::impl::lower_bound<T>(i_mean,i_y,converter,false_());
        }
    }

namespace impl{

    template<typename T,typename Int,typename IntT>
    bool do_raise_error1(
        const T& lhs,
        const T& tol,
        std::string& str,
        const Int& i_mean,
        const Int& i_y,
        const IntT& converter,
        boost::mpl::bool_<true> /*y>=0*/
    ){
        BOOST_ASSERT(i_y>=0);
        if(lhs <= -tol){
            const std::string msg = " [ lemma2 : lhs = %1% >=0 has failed ]";
            typedef boost::format f_;
            f_ f( msg ); 
            f % lhs; 
            str += f.str();
            return true;        
        }
        return false;
    }

    template<typename T,typename Int,typename IntT>
    bool do_raise_error1(
        const T& lhs,
        const T& tol,
        std::string& str,
        const Int& i_mean,
        const Int& i_y,
        const IntT& converter,
        boost::mpl::bool_<false> /*y>=0*/
    ){
        BOOST_ASSERT(i_y<0);
        if(lhs >= tol){
            const std::string msg = " [ lemma2.1 : lhs = %1% <=0 has failed ]";
            typedef boost::format f_;
            f_ f( msg ); f % lhs; 
            str += f.str();
            return true;        
        }
        return false;
    }

}

    template<typename T,typename Int,typename IntT>
    bool do_raise_error1(
        const T& q,
        const T& tol,
        std::string& str,
        const Int& i_mean,
        const Int& i_y,
        const IntT& converter
    ){
        T lhs = lemma2::lhs(q, i_mean, i_y, converter);
        if(i_y >= 0){
           typedef boost::mpl::bool_<true> true_;
           return lemma2::impl::do_raise_error1(
               lhs,tol,str,i_mean,i_y,converter,true_());
        }else{
           typedef boost::mpl::bool_<false> false_;
           return lemma2::impl::do_raise_error1(
               lhs,tol,str,i_mean,i_y,converter,false_());
        }
    }

    template<typename T,typename Int,typename IntT>
    bool do_raise_error2(
        const T& q,
        const T& tol,
        std::string& str,
        const Int& i_mean,
        const Int& i_y,
        const IntT& converter
    ){
        T lhs = lemma2::lhs(q, i_mean, i_y, converter);
        T ub = lemma2::upper_bound<T>(i_mean,i_y, converter);
        if(lhs > ub + tol){
            const std::string msg 
                = " [ lemma2.2 : lhs = %1% < %2% has failed ]";
            typedef boost::format f_;
            f_ f( msg ); f % lhs % ub; 
            str += f.str();
            return true;
        }
        return false;
    }

    template<typename T,typename Int,typename IntT>
    bool do_raise_error3(
        const T& q,
        const T& tol,
        std::string& str,
        const Int& i_mean,
        const Int& i_y,
        const IntT& converter
    ){
        T lhs = lemma2::lhs(q, i_mean, i_y, converter);
        T lb = lemma2::lower_bound<T>(i_mean,i_y,converter);
        if(lhs + tol < lb){
            const std::string msg 
               = " [ lemma2.3 : lhs = %1% > %2% has failed ]";
            typedef boost::format f_;
            f_ f( msg ); f % lhs % lb; 
            str += f.str();
            return true;
        }
        return false;
    }

}// lemma2
}// q
}// devroye
}// poisson
}// random
}// boost

#endif
