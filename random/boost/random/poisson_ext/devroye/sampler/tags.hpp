//////////////////////////////////////////////////////////////////////////////
// random::poisson_ext::devroye::sampler::tags.hpp          				//
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_RANDOM_POISSON_EXT_DEVROYE_SAMPLER_TAGS_HPP_ER_2010
#define BOOST_RANDOM_POISSON_EXT_DEVROYE_SAMPLER_TAGS_HPP_ER_2010

namespace boost{
namespace random{
namespace poisson{
namespace devroye{  

// These tags are used by sampler::meta_int_mean to specify the implementation
// of step4.
namespace tag{
	struct standard{};
    struct squeeze{};
}

}// devroye
}// poisson
}// random
}// boost

#endif

