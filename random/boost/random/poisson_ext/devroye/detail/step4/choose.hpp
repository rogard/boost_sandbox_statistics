//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::devroye::detail::choose.hpp          				//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_CHOOSE_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_DETAIL_STEP4_CHOOSE_HPP_ER_2010
#include <boost/random/poisson_ext/devroye/sampler/tags.hpp>

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  
namespace detail{
namespace step4{

	// Maps a tag to an implementation

    template<typename Int,typename T,typename P> class standard;
    template<typename Int,typename T,typename P> class squeeze;

    template<typename Tag,typename Int,typename T,typename P> struct choose{};
    
    template<typename Int,typename T,typename P>
	struct choose<tag::standard,Int,T,P>{
        typedef detail::step4::standard<Int,T,P> type;
    };
    
    template<typename Int,typename T,typename P>
    struct choose<tag::squeeze,Int,T,P>{
        typedef detail::step4::squeeze<Int,T,P> type;
    };

}// step4
}// detail
}// devroye
}// poisson
}// random
}// boost

#endif
