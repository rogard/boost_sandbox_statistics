///////////////////////////////////////////////////////////////////////////////
// bound_distribution_value.hpp                                              //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_BOUND_DISTRIBUTION_VALUE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_BOUND_DISTRIBUTION__HPP_ER_2010
#include <cmath>
#include <utility>
#include 

#include <boost/type_traits.hpp>
#include <boost/range.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>

#include <boost/foreach.hpp>
#include <boost/parameter/name.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/count.hpp>

#include <boost/statistics/detail/non_parametric/empirical_distribution/ordered_sample.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace empirical_distribution{
namespace kolmogorov_smirnov_statistic{
namespace impl{

    // T can be an integer or a float
    template<typename T,typename D>
	class bound_distribution_value : public boost::accumulators::accumulator_base
    {
        typedef Comp comp_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

        typedef typename D::value_type result_type;
        typedef T sample_type;

        template<typename Args>
        bound_distribution_value(const Args& args)
        :dist_(kolmogorov_smirnov_statistics::_benchmark_distribution){}

        void operator()(dont_care_){}
		
        result_type result(dont_care_)const{
            namespace ac = boost::accumulators;
            namespace ed = boost::statistics::detail::empirical_distribution;
            namespace ks = boost::statistics::detail::kolmogorov_smirnov;
            return ks::value(boost::accumulators;
        }

    };
 
}// impl
namespace tag
{
    template<typename T1 = double>
    struct bound_distribution_value: boost::accumulators::depends_on<
        empirical_distribution::tag::ordered_sample,
        accumulators::tag::count
    >
    {
        struct impl{
            template<typename T,typename W>
            struct apply{
                typedef empirical_distribution
                    ::kolmogorov_smirnov_statistic::impl::bound_distribution_value<T,T1> type;
            };
        };
    };
}// tag
namespace result_of{

    // where to specify T1?!
    template<typename AccSet,typename T1,typename D>
    struct bound_distribution_value{
    	typedef empirical_distribution
            ::kolmogorov_smirnov_statistic::tag::bound_distribution_value<T1> tag_;
        typedef typename
            boost::accumulators::detail::template 
            	extractor_result<AccSet,tag_>::type type; 
    };

}// result_of
namespace extract
{

    template<typename AccSet,typename T1,typename D>
    typename detail::empirical_distribution::result_of::template 
        bound_distribution_value<AccSet,T1,D>::type
  	bound_distribution_value(AccSet const& acc,const D& dist)
    { 
        namespace ed = detail::empirical_distribution;
        namespace ks = ed::kolmogorov_smirnov;
    	typedef ks::tag::bound_distribution_value<T1> tag_;
        return boost::accumulators::extract_result<tag_>(
            acc,
            (ks::_benchmark_distribution = dist)
        );
  	}

}// extract
}// kolmogorov_smirnov_statistic
}// empirical_distribution
}// detail
}// statistics
}// boost

#endif
