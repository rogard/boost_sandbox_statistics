//////////////////////////////////////////////////////////////////////////////
// data::field::survival::accumulator::mean_response.hpp                    //
//                                                                          //
//                                                                          //
//  (C) Copyright 2010 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_ACCUMULATOR_MEAN_RESPONSE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_DATA_FIELD_SURVIVAL_ACCUMULATOR_MEAN_RESPONSE_HPP_ER_2010
#include <boost/statistics/detail/data/field/framework/function/field_value.hpp>
#include <boost/statistics/detail/data/field/survival/fields/entry_time.hpp>
#include <boost/statistics/detail/data/field/survival/keyword/entry_time.hpp>
#include <boost/statistics/detail/data/keyword/survival/entry_time.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

#include <boost/statistics/detail/accumulator/statistics/count_less_than.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace data{
namespace accumulator{	
namespace impl
{


	// U is a unit
	// S is a sequence of functors
    template<typename U,typename S>
    class dispatcher
    {

		typedef tags_; // extract the tags from U
		typedef pairs_; // pairs (Tag,Stat) 

        public:
    
        typedef void result_type;

        dispatcher(const S& s):s_(s){}
        
        template<typename U1>
        void operator()(const U1& u){
        	boost::fusion::for_each(stats,f(this->unit));
        }

		template<typename Tag,typename Stat,typename Unit>
		struct f{
        	f(U& u):u_(u){}
        
			template<typename T>
            void operator()(const t& in){        
				field_value<Tag>(this->unit) = this->stat(
					field_value<Tag>(in);
				);
        	}
        
        };

		U u_;
        pairs_ pairs;        

    };

}//impl

///////////////////////////////////////////////////////////////////////////////
// tag::proportion_less_than
namespace tag
{
    struct proportion_less_than
      : boost::accumulators::depends_on<
        boost::accumulators::tag::count,
        tag::count_less_than
    >
    {
      typedef statistics::detail::accumulator::
      	impl::proportion_less_than<boost::mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::proportion_less_than
namespace extract
{

  	template<typename AccSet>
  	typename boost::mpl::apply<
    	AccSet,
        statistics::detail::accumulator::tag::proportion_less_than
	>::type::result_type
  	proportion_less_than(AccSet const& acc){
    	typedef statistics::detail::accumulator
        	::tag::proportion_less_than the_tag;
    	return boost::accumulators::extract_result<the_tag>(acc);
  	}

}

using extract::proportion_less_than;

}// field
}// data
}// detail
}// statistics
}// boost                

#endif