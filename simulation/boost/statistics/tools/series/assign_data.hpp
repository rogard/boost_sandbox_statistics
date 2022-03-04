///////////////////////////////////////////////////////////////////////////////
// assign_data.hpp                                                           //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_TOOLS_DETAIL_SERIES_ASSIGN_DATA_HPP_ER_2010
#define BOOST_STATISTICS_TOOLS_DETAIL_SERIES_ASSIGN_DATA_HPP_ER_2010
#include <boost/mpl/foreach.hpp>
#include <boost/mpl/detail/wrapper.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/statistics/tools/series/data_field.hpp>
#include <boost/statistics/tools/series/traits.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace series{

    // Each call to the unary functor extracts the specified feature from the
    // accumulator (A) and assigns it to the internally refererenced data (D).
    template<typename A,typename D>
    struct data_assigner{
    
        data_assigner(const A& acc,D& data)
        :acc_( acc ),data_( data ){}
        
        template<typename Tag> 
        void operator()(const boost::mpl::wrapper<Tag>& feature)const
        {
            namespace ns = boost::accumulators;
            get_field<Tag>( data ) = ns::extract_result<Tag>( this->acc );
        }

        template<typename Tag,typename Args> 
        void operator()(
            const boost::mpl::wrapper<Tag>& feature,const Args& args)const
        {
            namespace ns = boost::accumulators;
            get_field<Tag>( data ) = ns::extract_result<Tag>( this->acc, args );
        }
    
        private:
        const &A acc_;
        mutable D& data_
    
    };

    // Extracts the features specified by the mpl vector F from the accumulator
    // of type A, and assigns them to the data-structure D.
    template<typename F,typename A,typename D>
    void assign_data(const A& acc,D& data){
        typedef data_assigner<F,A,D> assigner_;
        typedef boost::mpl::detail::wrapper<boost::mpl::_> op_; 
        boost::mpl::for_each<S,op_>(assigner_(acc,data));
    };

    template<typename F,typename A,typename D>
    void assign_data(const A& acc,const A1&,D& data){
        typedef data_assigner<F,A,D> assigner_;
        typedef boost::mpl::detail::wrapper<boost::mpl::_> op_; 
        boost::mpl::for_each<S,op_>(assigner_(acc,data));
    };


}// series
}// detail
}// statistics
}// boost

#endif