///////////////////////////////////////////////////////////////////////////////
// value.hpp                                                                 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_VALUE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_VALUE_HPP_ER_2010
#include <cmath>
#include <utility>

#include <boost/type_traits.hpp>
#include <boost/range.hpp>

#include <boost/numeric/conversion/converter.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>

#include <boost/foreach.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/binding.hpp>

#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/count.hpp>

#include <boost/statistics/detail/non_parametric/empirical_distribution/ordered_sample.hpp>

namespace boost{ 
namespace statistics{
namespace detail{
namespace empirical_distribution{
namespace kolmogorov_smirnov_statistic{

BOOST_PARAMETER_NAME(benchmark_distribution);

namespace impl{

    // T can be an integer or a float
    template<typename T,typename T1,typename Comp = std::less<T> >
	class value : public boost::accumulators::accumulator_base
    {
        typedef Comp comp_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

        typedef T1 result_type;
        typedef T sample_type;

        value(dont_care_){}

        void operator()(dont_care_){}
		
        template<typename Args>
        result_type result(const Args& args)const{
            namespace ac = boost::accumulators;
            namespace ed = detail::empirical_distribution;
            namespace ks = ed::kolmogorov_smirnov_statistic;
            typedef T1 val_;
            typedef std::size_t size_;
            typedef ac::tag::count tag_n_;
            typedef ed::tag::ordered_sample tag_os_;
            typedef typename parameter::binding<
                Args, ac::tag::accumulator>::type cref_acc_set_;
            typedef typename boost::remove_cv<
               typename boost::remove_reference<
                   cref_acc_set_
                >::type
            >::type acc_set_;
            typedef typename ed::result_of::ordered_sample<
                acc_set_>::type ref_os_; 
            typedef typename boost::remove_const< //in case ref changed to cref
            	typename boost::remove_reference<ref_os_>::type
            >::type os_;
            typedef typename boost::range_reference<os_>::type ref_elem_;
            typedef boost::numeric::converter<val_,size_> converter_;

            ref_os_ ref_os = ac::extract_result<tag_os_>( 
                 args[ ac::accumulator ] );
            val_ m1 = converter_::convert( 0 );
            size_ i = 0;
            size_ n = boost::accumulators::extract::count( 
                args[ ac::accumulator ] );
            
            BOOST_FOREACH(ref_elem_ e,ref_os){
                i += e.second; 
                val_ ecdf = converter_::convert( i ) / converter_::convert( n );
                val_ true_cdf = cdf( 
                    args[ ks::_benchmark_distribution ] , 
                    e.first 
                );
                val_ m2 
                	= (true_cdf > ecdf)?(true_cdf - ecdf) : (ecdf - true_cdf);
                if(m2 > m1){ m1 = m2; } 
            }
            
            return m1;
        }

    };
 
}// impl
namespace tag
{
    template<typename T1 = double>
    struct value: boost::accumulators::depends_on<
        empirical_distribution::tag::ordered_sample,
        accumulators::tag::count
    >
    {
        struct impl{
            template<typename T,typename W>
            struct apply{
                typedef empirical_distribution
                    ::kolmogorov_smirnov_statistic::impl::value<T,T1> type;
            };
        };
    };
}// tag
namespace result_of{

    template<typename T1,typename AccSet,typename D>
    struct value{
    	typedef empirical_distribution
            ::kolmogorov_smirnov_statistic::tag::value<T1> tag_;
        typedef typename
            boost::accumulators::detail::template 
            	extractor_result<AccSet,tag_>::type type; 
    };

}
namespace extract
{

    template<typename T1,typename AccSet,typename D>
    typename kolmogorov_smirnov_statistic::result_of::template 
        value<T1,AccSet,D>::type
  	value(AccSet const& acc,const D& dist)
    { 
        namespace ed = detail::empirical_distribution;
        namespace ks = ed::kolmogorov_smirnov_statistic;
    	typedef ks::tag::value<T1> tag_;
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
