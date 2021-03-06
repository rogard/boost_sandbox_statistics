///////////////////////////////////////////////////////////////////////////////
// cells_count.hpp                                                           //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_CELLS_COUNT_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_CELLS_COUNT_HPP_ER_2010
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/factor/levels.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace contingency_table{
namespace cells_aux{

    template<typename A>
    struct count{
    
        typedef std::size_t size_;
        typedef void result_type;
    
        count(const A& acc,size_& n)
        :acc_( acc ),n_( n ){}
        
        template<typename Key>
        void operator()(const boost::mpl::detail::wrapper<Key>& u){
             this->n_ *= contingency_table::levels<Key>( this->acc_ ).size();
        }
        
        const A& acc_;
        size_& n_;
    };
}// cells_aux

  	template<typename Keys,typename AccSet>
    std::size_t cells_count(AccSet const& acc){
        namespace ns = statistics::detail; 
        typedef boost::mpl::detail::wrapper<boost::mpl::_> op_; 
        typedef cells_aux::count<AccSet> fun_; 
        std::size_t n = 1;
        boost::mpl::for_each<Keys,op_>(
            fun_( acc, n )
        );
        return n;
    }

}// contingency_table
}// detail
}// statistics
}// boost

#endif