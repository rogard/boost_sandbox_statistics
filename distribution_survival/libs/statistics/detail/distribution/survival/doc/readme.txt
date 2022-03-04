//////////////////////////////////////////////////////////////////////////////
// statistics::distribution::survival::doc::readme                    //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////

[ Contact ]

er.ci.2020 at gmail.com

[ Overview ]

These C++ classes are abstractions for survival data (right censored, staggered 
entry) and their likelihoods.

[ Compiler ]

gcc version i686-apple-darwin9-gcc-4.0.1 (GCC) 4.0.1

[ Dependencies ]


[ History ]

November 2009 : 
	- A custom class for record has been replaced by a fusion map
    - Serialization have been removed (as a general rule I use a generic
    wrapper that is serializable.)
    - likelihoods have been refactored to fit within the distribution::model
	framework.

July 2009 : First version

[ Sources ]

http://en.wikipedia.org/wiki/Survival_analysis

[ Notation ]

    Consider, for example, a clinical trial. t is a time measured since the 
    beginning of the trial. ft is a failure time relative to a data-unit's 
    entry time into the trial and ct is a censoring time. The final censoring
    time Ct is the min of ct and the time since entry at t. 


