///////////////////////////////////////////////////////////////////////////////
// count_matching.hpp                                                        //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_COUNT_MATCHING_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_COUNT_MATCHING_HPP_ER_2010
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/cells.hpp>
#include <boost/mpl/detail/wrapper.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace contingency_table{

  	template<typename Keys,typename AccSet,typename T>
    std::size_t count_matching(AccSet const& acc,const T& sample){
        namespace ns = contingency_table;
        return ns::extract::cells<Keys>( acc )[ sample ];
    }

    // A: accumulator set
    // S: sample
    // F: unary functor
    template<typename A,typename S,typename F>
    struct fun_count_matcher{
            
        typedef std::size_t size_;
        typedef void result_type;
    
        fun_count_matcher(const A& a,const S& s, const F& f)
            :acc( a ), sample( s ), fun( f ){}
        
        template<typename Keys>
        void operator()(const boost::mpl::detail::wrapper<Keys>& u)const{
            namespace ns = contingency_table;
            this->fun(
                ns::count_matching<Keys>(
                    this->acc,
                    this->sample
                )
            );
        }
        
        private:
        const A& acc;
        const S& sample;
        F fun;
    };

    template<typename A,typename S,typename F>
    fun_count_matcher<A,S,F> 
    make_fun_count_matcher(const A& a,const S& s, const F& f){
        namespace ns = contingency_table;
        typedef ns::fun_count_matcher<A,S,F> result_;
        return result_(a, s, f);
    }

}// contingency_table
}// detail
}// statistics
}// boost

#endif
