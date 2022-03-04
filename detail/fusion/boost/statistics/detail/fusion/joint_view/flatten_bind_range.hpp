///////////////////////////////////////////////////////////////////////////////
// fusion::detail::joint_view::flatten_bind_range.hpp                 	 	 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_FUSION_JOINT_VIEW_FLATTEN_BIND_RANGE_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_FUSION_JOINT_VIEW_FLATTEN_BIND_RANGE_HPP_ER_2010
#include <vector>
#include <boost/type_traits.hpp>
#include <boost/range.hpp>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/statistics/detail/fusion/joint_view/bind_iterator.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace fusion{
namespace joint_view{
namespace result_of{
                        
    // Maps {x[i]:i=1,...,n} and {{y[i][j]:j=1,...,n[j]} : i=1,...,n}
    // to {joint_view(x[i],y[i][j]) : i=1,...,n; j=1,...,n[i]}
    template<typename ItX,typename ItArY>
    struct flatten_bind_range{
                            
        template<typename It>
        struct it_value : boost::remove_cv<
        	typename boost::remove_reference<
        		typename boost::iterator_reference<It>::type
        	>::type
        >{};

        template<typename X,typename Ry>
        struct fun
        {
            typedef 
            	detail::fusion::joint_view::result_of::bind_range<X,Ry> meta_;
            typedef typename meta_::type result_type;
            
            fun(){}
            
            template<typename T>
            result_type operator()(const T& tuple)const{
                return meta_::call(
                    boost::get<0>(tuple),
                    boost::get<1>(tuple)
                );
            }

        };
       
        typedef fun<	
            typename it_value<ItX>::type,
            typename it_value<ItArY>::type
        > fun_;
                            
        typedef boost::tuple<ItX,ItArY> 						it_tuple_;
        typedef boost::zip_iterator<it_tuple_> 					zip_it_;
        typedef boost::transform_iterator<fun_,zip_it_>			t_it_;
        typedef boost::flatten_iterator<t_it_>					flat_it_;
        typedef boost::iterator_range<flat_it_> 				type;
                            
        static type call(ItX b_x,ItX e_x,ItArY b_y,ItArY e_y){
            zip_it_ 	zip_it_b( it_tuple_(b_x,b_y) );
            zip_it_ 	zip_it_e( it_tuple_(e_x,e_y) );
            t_it_ 		t_it_b(zip_it_b,fun_());                                
            t_it_ 		t_it_e(zip_it_e,fun_());                                
            flat_it_ 	flat_it_b(t_it_b,t_it_e); 
            flat_it_ 	flat_it_e(t_it_e,t_it_e); 
            return type( flat_it_b, flat_it_e );
        };
	};
}
                    
    template<typename ItX,typename ItArY>
    typename detail::fusion::joint_view
    	::result_of::flatten_bind_range<ItX,ItArY>::type
    flatten_bind_range(ItX b1,ItX e1,ItArY b2,ItArY e2){
        typedef detail::fusion::joint_view::result_of
        	::flatten_bind_range<ItX,ItArY> meta_;
        return meta_::call(b1,e1,b2,e2);    
    }
                
}// joint_view
}// fusion
}// detail
}// statistics
}// boost

#endif



