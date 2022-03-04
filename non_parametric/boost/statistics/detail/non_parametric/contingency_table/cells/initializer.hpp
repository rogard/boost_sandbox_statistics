///////////////////////////////////////////////////////////////////////////////
// initializer.hpp                                                           //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_INITIALIZER_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_CONTINGENCY_TABLE_CELLS_INITIALIZER_HPP_ER_2010
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/joint_view.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/factor/levels.hpp>
#include <boost/statistics/detail/non_parametric/contingency_table/cells/traits.hpp>

// Usage
//    initialize<Keys>(acc)
// All the cells of contingency table are created and initialized to zero. 

namespace boost{
namespace statistics{
namespace detail{
namespace contingency_table{
namespace cells_aux{

    template<typename K,typename T>
    struct op{
             
        typedef boost::fusion::pair<K,T> pair_; // maybe const T& ?
        typedef boost::fusion::map< pair_ > result_type; 

        op(){}
                   
        result_type operator()(const T& t)const
        {
            return result_type( pair_( t ) );
        }
         
    };
    
    template<typename Keys,typename AccSet,typename V,
        typename F, typename L, bool exit = boost::is_same<F,L>::value 
    >
    struct initializer{

        initializer(AccSet& acc,const V& view)
        :acc_( acc ),view_( view ){}

        typedef typename boost::mpl::next<F>::type next_it_;
        typedef typename boost::mpl::deref<F>::type key_;
        typedef boost::mpl::vector1<key_> vec_key_;
     
        typedef void result_type;
         
        template<typename M>
        void operator()(const M& map)
        {    
        
            namespace ct = statistics::detail::contingency_table;
            typedef boost::fusion::joint_view<const V,const M> next_view_;
            typedef cells_aux::initializer<
                Keys, AccSet, next_view_, next_it_, L> next_;
            next_view_ next_view( this->view_, map ); 
            typedef typename ct::result_of::extract::levels<
                key_,AccSet>::type ref_levels_;
            typedef typename boost::remove_cv<
                typename boost::remove_reference<
                    ref_levels_
                >::type
            >::type levels_;
            typedef typename levels_aux::value_of<key_,AccSet>::type value_;
            typedef cells_aux::op<key_,value_> op_;
            boost::for_each(
                ct::extract::levels<key_>( this->acc_ ) 
                    | boost::adaptors::transformed( op_() ),  
                next_( this->acc_, next_view )
            ); 

        }

        private:
         
        AccSet& acc_;
        const V& view_;

    };

    template<typename Keys, typename AccSet, typename V, typename F, typename L>
    struct initializer<Keys, AccSet, V, F, L, true>
    {
    
        initializer(AccSet& acc, const V& view)
        :acc_( acc ),view_( view ){}
    
        typedef void result_type;

        template<typename M>
        void operator()(const M& map)
        {
            namespace ct = statistics::detail::contingency_table;
            typedef boost::fusion::joint_view<const V,const M> next_view_;
            next_view_ next_view( this->view_, map ); 
            typedef typename ct::cells_traits::mapped_of<
               Keys, AccSet>::type count_;
            typedef boost::numeric::converter<count_,int> converter_;
            count_ zero = converter_::convert( 0 ); 
            ct::extract::cells<Keys>( this->acc_ )[ next_view ] = zero; 

        } 

        private:
        AccSet& acc_;
        const V& view_;
        
    };
    
}// cells_aux

    template<typename Keys,typename AccSet>
    void initialize(AccSet& acc)
    {
        namespace ct = statistics::detail::contingency_table;
        typedef boost::fusion::map<> empty_map_;
        typedef typename boost::mpl::begin<Keys>::type first_it_;
        typedef typename boost::mpl::deref<first_it_>::type key_;
        typedef typename boost::mpl::vector1<key_> vec_key_;
        typedef typename boost::mpl::next<first_it_>::type second_it_;
        typedef typename boost::mpl::end<Keys>::type last_;
        
        typedef cells_aux::initializer<
            Keys, AccSet, empty_map_, second_it_, last_> initializer_;
        empty_map_ empty_map;
        initializer_ initializer( acc, empty_map );
        typedef typename levels_aux::value_of<key_,AccSet>::type value_;
        typedef cells_aux::op<key_,value_> op_;
        op_ op;
        boost::for_each(
            ct::extract::levels<key_>( acc ) 
                | boost::adaptors::transformed( op_() ),
            initializer
        );
        
    }

}// contingency_table
}// detail
}// statistics
}// boost

#endif

