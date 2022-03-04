///////////////////////////////////////////////////////////////////////////////
// cdf.hpp                                                                   //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_CDF_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_CDF_HPP_ER_2010
#include <boost/range.hpp>
#include <boost/numeric/conversion/converter.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/count.hpp>

#include <boost/statistics/detail/non_parametric/empirical_distribution/cumulative_count.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace empirical_distribution{
namespace impl{

    // T can be an integer or a float
    template<typename T,typename T1,typename Comp = std::less<T> >
	class cdf : public boost::accumulators::accumulator_base
    {
        typedef Comp comp_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

        typedef T1 result_type;
        typedef T sample_type;

        cdf(dont_care_){}

        void operator()(dont_care_){}
		
        template<typename Args>
        result_type result(const Args& args)const{
            typedef std::size_t size_;
            namespace ns = empirical_distribution;
            namespace ac = boost::accumulators;
            size_ i =  ns::extract::cumulative_count( 
                args[ac::accumulator], args[ ac::sample ] );
            size_ n = ac::extract::count( args[ ac::accumulator ] );
            typedef boost::numeric::converter<T1,size_> converter_;
            return converter_::convert( i )/converter_::convert( n );
        }

    };
    
}
namespace tag
{
    template<typename T1>
    struct cdf: boost::accumulators::depends_on<
        empirical_distribution::tag::cumulative_count,
        accumulators::tag::count
    >
    {
        struct impl{
            template<typename T,typename W>
            struct apply{
                typedef empirical_distribution::impl::cdf<T,T1> type;
            };
        };
    };
}
namespace result_of{

    template<typename T1,typename AccSet>
    struct cdf{
    	typedef empirical_distribution::tag::cdf<T1> tag_;
        typedef typename
            boost::accumulators::detail::template 
            	extractor_result<AccSet,tag_>::type type; 
    };

}
namespace extract
{

    template<typename T1,typename AccSet,typename T>
    typename detail::empirical_distribution
        ::result_of::template cdf<T1,AccSet>::type
  	cdf(AccSet const& acc,const T& x)
    { 
        namespace ac = boost::accumulators;
        namespace ns = detail::empirical_distribution;
    	typedef ns::tag::cdf<T1> tag_;
        return ac::extract_result<tag_>( acc, (ac::sample = x) );
  	}

}// extract
}// empirical_distribution
}// detail
}// statistics
}// boost

#endif
