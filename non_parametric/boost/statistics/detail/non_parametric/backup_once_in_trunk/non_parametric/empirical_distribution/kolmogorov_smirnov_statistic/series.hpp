///////////////////////////////////////////////////////////////////////////////
// series.hpp                                                                //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_SERIES_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_EMPIRICAL_DISTRIBUTION_KOLMOGOROV_SMIRNOV_STATISTIC_SERIES_HPP_ER_2010
#include <cmath>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/statistics/detail/non_parametric/empirical_distribution/kolmogorov_smirnov_statistic/value.hpp>

namespace boost{ 
namespace statistics{
namespace detail{
namespace empirical_distribution{
namespace kolmogorov_smirnov_statistic{

template<typename T1>
struct series_data
{
    typedef std::size_t size_type; 
    series_data(){} 
    size_type count; T1 value;
};

template<typename T>
std::ostream&
operator<<(std::ostream& os,const series_data<T>& data)
{
    return os << '('<< data.count << ',' << data.value << ')';
}


// Generates a series_data whose value is the Kolmogorov-Smirnov statistic
// for distribution dist, at each of the sample sizes 
//    offset + {base^i : i = first_p,...,last_p };
// Each sample is drawn from gen(). 
template<typename D,typename G,typename It>
void series(
    const D& dist,
    G& gen,
    long offset,    // 1
    long base,      // 10
    int first_p,   // 0
    int last_p,    // 5
    It iter
){
    namespace ac = boost::accumulators;
    namespace ed = boost::statistics::detail::empirical_distribution;
	namespace ks = ed::kolmogorov_smirnov_statistic;
    typedef typename D::value_type val_;
    typedef std::size_t size_;
    typedef ks::tag::value<val_> tag_;
    typedef series_data<val_> series_data_;
    typedef typename G::result_type sample_;
    typedef ac::stats<tag_> stats_;
    typedef ac::accumulator_set<sample_,stats_> acc_;
    acc_ acc;

    typedef boost::numeric::converter<long double,long> int_float_;
    typedef boost::numeric::converter<long, long double> float_int_;
    
    long m = float_int_::convert( 
        std::pow( int_float_::convert( base ), first_p )
    );
    long new_count;
    series_data_ series_data;
    series_data.count = 0;
 
    for(long p = first_p; p < last_p; p++){
        new_count = ( offset + m );
        for( long i = series_data.count; i < new_count; i++ ){ acc( gen() ); }
        series_data.count = new_count;
        series_data.value = ks::extract::value<val_>( acc, dist );
        ( *iter ) = series_data;
        m *= base;
    }
        
}

}// kolmogorov_smirnov_statistic
}// empirical_distribution
}// detail
}// statistics
}// boost

#endif

