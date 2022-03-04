//////////////////////////////////////////////////////////////////////////////
// statistics::detail::data::doc::readme                                    //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////

[ Contact ]

er.ci.2020 at gmail.com

[ Overview ]

This library offers a generic data-structure for representing and managing a 
unit of observation a.k.a a data-point, or a 'row' in dataset arranged as a 
matrix.

The class data::unit<> contains up to 5 fields (for now), each identified by a 
class type called a keyword tag (shorthand: tag) and modeling a concept Field. 
At the very least, in a regression context, one would have two fields, and 
therefore two tags say tag_x and tag_y, one for the input, the other for the
output. Accordingly, their values would fetched like this:
	field_value<tag_x>(unit)
	field_value<tag_y>(unit)

A model of Field is data::field<>, which hopefully meets most common usage. 
Pre-defined keyword tags for naming common data arising in estimation and 
survival analysis are available. 

While other sub-libraries in /statistics should ideally leave the client the 
option to choose the type of data-structure, the default choice should prefera-
bly one that is defined here, if such a need arises.

[ Functionality ]

Although data::unit<> is similar to fusion::map<> it differs by
- a constructor that takes an argument pack, 
- serialization*. 
- trading less memory for a slight performance penalty in construction
All the fusion functionality, moreoever, is optionally available through the 
usual fusion adapter.

*See /sandbox/statistics/detail/fusion/serialize/map for an alternative.

[ Applications ]

/statistics/cross_valdation 
/statistics/distribution_model 

[ Fusion functionality ]

Building a statistical-data interface directly around fusion would be limited to
adding free functions and in any case is un-natural because fusion is general 
purpose. Moreover, its functionality is still available through an adapter. For 
example, fusion can reduce the memory requirement of a dataset that is split 
into blocks, where fixed and variable fields of a unit are merged using 
fusion::joint_view.

[ Platform/Compiler ]

Tested Feb 8, 2010:
Mac OS X 10.6 - x86_64 - gcc 4.0 - boost_1_40_0
                            
[ Dependencies ]

boost_1_40_0
sandbox/detail/serialize/

The boost/serialize library must be installed and specified the library path.

[ TODO ]

Extend beyond 5 fields.

[ Revision History ]

Feb 8, 2010 Started.