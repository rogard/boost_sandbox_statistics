///////////////////////////////////////////////////////////////////////////////
// chi_square_summand.hpp                                                    //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_AUX_CHI_SQUARE_SUMMAND_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_PEARSON_CHISQ_INDEPENDENCE_AUX_CHI_SQUARE_SUMMAND_HPP_ER_2010
#include <cmath>
#include <boost/mpl/size.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/count_matching.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/pearson_chisq/common/chi_square_summand.hpp>

namespace boost { 
namespace statistics{
namespace detail{
namespace contingency_table{
namespace pearson_chi_square_statistic{
namespace independence_between_aux{

    template<typename T1,typename Keys,typename AccSet>
    struct chi_square_summand
    {

        typedef typename AccSet::weight_type size_;
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
            return pearson_chi_square_statistic::chi_square_summand<T1>( 
                conv_::convert( n ) / conv_::convert( denom ), 
                cell.second 
            );
        }
    
        struct prod_fun{
            
            prod_fun(size_& n) : n_( n ){}
            
            template<typename T> 
            void operator()(const T& k)const{ this->n_ *= k; }
            
            mutable size_& n_;
        };
    
        const AccSet& acc;
        size_ denom;

    };

}// independence_between_aux
}// pearson_chi_square_statistic
}// contingency_table
}// detail
}// statistics
}// boost

#endif
