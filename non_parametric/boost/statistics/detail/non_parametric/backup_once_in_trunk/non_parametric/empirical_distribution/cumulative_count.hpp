///////////////////////////////////////////////////////////////////////////////
// count_less_equal_than.hpp                                                 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_CUMULATIVE_COUNT_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_CUMULATIVE_COUNT_HPP_ER_2010

#include <boost/range.hpp>
#include <boost/numeric/conversion/converter.hpp>

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
namespace impl{

    // T can be an integer or a float
    template<typename T,typename Comp = std::less<T> >
	class cumulative_count : public boost::accumulators::accumulator_base
    {
        typedef Comp comp_;
        typedef std::size_t size_;
        typedef boost::accumulators::dont_care dont_care_;

        public:

        typedef size_ result_type;
        typedef T sample_type;

        cumulative_count(dont_care_){}

        void operator()(dont_care_){}
		
        template<typename Args>
        result_type result(const Args& args)const{
            namespace ns = statistics::detail::empirical_distribution;
            typedef ns::tag::ordered_sample tag_;
            return this->result_impl(
                boost::accumulators::extract_result<tag_>(
                    args[ boost::accumulators::accumulator ]
                ),
                args[ boost::accumulators::sample ]
            ); 
        }

        private:
		
        template<typename Map>
        result_type result_impl(
            Map& map, 
            const sample_type& x
        )const{
           return std::for_each(
                boost::const_begin(map),
                this->bound(map,x),
                accumulator()
           ).value; 
        }

        template<typename Map>
        typename boost::range_iterator<const Map>::type
        bound(
            const Map& map,
            const sample_type& x
        )const{
            return map.upper_bound(x);
        }

        struct accumulator{
            mutable size_ value;
        	
            accumulator():value(0){}
            accumulator(const accumulator& that)
            	:value(that.value){}
            
            template<typename Data>
            void operator()(const Data& data)const{
            	value += data.second;
            }
        
        };
    };
    
}
namespace tag
{
    struct cumulative_count: boost::accumulators::depends_on<
        empirical_distribution::tag::ordered_sample
    >
    {
        struct impl{
            template<typename T,typename W>
            struct apply{
                typedef empirical_distribution::impl::cumulative_count<T> type;
            };
        };
    };
}
namespace result_of{

    template<typename AccSet>
    struct cumulative_count{
    	typedef empirical_distribution::tag::cumulative_count tag_;
        typedef typename
            boost::accumulators::detail::template 
            	extractor_result<AccSet,tag_>::type type; 
    };

}
namespace extract
{

    template<typename AccSet,typename T>
    typename detail::empirical_distribution::result_of::template 
        cumulative_count<AccSet>::type
  	cumulative_count(AccSet const& acc,const T& x)
    { 
        namespace ns = detail::empirical_distribution;
    	typedef ns::tag::cumulative_count tag_;
        return boost::accumulators::extract_result<tag_>(
            acc,
            (boost::accumulators::sample = x)
        );
  	}

}// extract
}// empirical_distribution
}// detail
}// statistics
}// boost

#endif
