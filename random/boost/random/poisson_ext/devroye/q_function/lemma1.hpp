//////////////////////////////////////////////////////////////////////////////
// random::poisson::devroye::q::lemma1.hpp                        	        //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_LEMMA1_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_Q_LEMMA1_HPP_ER_2010
#include <string>
#include <boost/format.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{            
namespace q{
namespace lemma1{

    // Lemma 1, p.199
    // q(y) < upper_bound(y), if y >= -mean
    template<typename T,typename Int,typename IntT>
    T upper_bound(const Int& i_mean,const Int& i_y,const IntT& converter)
    {
        T z = IntT::convert( 0 );
        T y = IntT::convert( i_y );
        T yp1 = IntT::convert( i_y +1 );
        T pos_y = IntT::convert( i_y < 0 ? z : y );
        T num = ( - y * yp1 );
        T den = IntT::convert( 2 * i_mean ) + pos_y;
        return num / den;
    }

    template<typename T,typename Int,typename IntT>
    bool do_raise_error(const T& q,const T& tol,std::string& str,
        const Int& i_mean,const Int& i_y,const IntT& converter)
    {
        T ub1 = lemma1::upper_bound<T>(i_mean,i_y,converter);
        if( q > ( tol + ub1 ) ){
            std::string msg = " [ lemma1 : q = %1% < %2% has failed ]";
            boost::format f( msg ); f % q % ub1; 
            str += f.str();
            return true;
        }else{
            return false;
        }
    }

}// lemma1
}// q
}// devroye
}// poisson
}// random
}// boost

#endif
