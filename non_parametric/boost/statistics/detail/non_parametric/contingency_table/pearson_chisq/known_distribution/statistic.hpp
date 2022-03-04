///////////////////////////////////////////////////////////////////////////////
// statistic.hpp                                                             //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_KNOWN_DISTRIBUTION_STATISTIC_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_KNOWN_DISTRIBUTION_STATISTIC_HPP_ER_2010
#include <cmath>
#include <boost/mpl/size.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/accumulators/statistics/detail/weighted_count.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/chisq_summand_formula.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/count_matching.hpp>


namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{
namespace known_distribution_aux{

    template<typename T1,typename Keys,typename AccSet>
    struct chi_square_summand
    {

        typedef std::size_t size_;
        typedef typename boost::mpl::size<Keys>::type keys_count_;
        
        template<typename N> 
        chi_square_summand(const AccSet& a, const N& total_count) 
            : acc( a ) , denom( 
                pow( total_count, keys_count_::value - 1)
            ){}

        template<typename C>        
        T1 operator()(const C& cell)const
        {
            namespace ct = contingency_table;
            typedef boost::mpl::detail::wrapper< 
                 boost::mpl::vector1< boost::mpl::_ >
            > op_;
            typedef boost::numeric::converter<T1,size_> conv_;
            size_ n = 1;
        	boost::mpl::for_each<Keys,op_>( 
                ct::make_fun_count_matcher(acc, cell.first, prod_fun( n ) )
            );
            return pearson_chi_square_statistic::chi_square_summand_formula<T1>( 
                conv_::convert( n ) / conv_::convert( denom ), 
                cell.second 
            );
        }
    
        struct prod_fun{
            
            prod_fun(size_& n) : n_( n ){}
            
            template<typename T> 
            void operator()(const T& k)const{ 
                this->n_ *= k; 
            }
            
            mutable size_& n_;
        };
    
        const AccSet& acc;
        size_ denom;

    };

}// known_distribution_aux

    template<typename T1,typename Keys,typename AccSet>
    T1 value(
        const boost::mpl::detail::wrapper<
            pearson_chi_square_statistic::tag::independence_between<Keys>
        >& hypothesis,
        const AccSet& acc
    )
    {
        namespace ct = contingency_table;
        namespace ns = ct::pearson_chi_square_statistic::known_distribution_aux;
        typedef typename ct::result_of::extract::cells<
            Keys,AccSet>::type ref_cells_;
        typedef typename boost::remove_reference<ref_cells_>::type cells_;
        typedef typename boost::range_reference<cells_>::type ref_cell_;
        typedef ns::chi_square_summand<T1,Keys,AccSet> summand_;
        typedef std::size_t size_;
        
        ref_cells_ ref_cells = ct::extract::cells<Keys>( acc );
        size_ n_obs = boost::accumulators::extract::weighted_count( acc );       
        
        summand_ summand(acc, n_obs);
        typedef boost::numeric::converter<T1,size_> conv_;
        
        T1 result = conv_::convert( 0 );
        BOOST_FOREACH(ref_cell_ ref_cell, ref_cells )
        {
            result += summand( ref_cell );
        }
        
        return result;        
    }
