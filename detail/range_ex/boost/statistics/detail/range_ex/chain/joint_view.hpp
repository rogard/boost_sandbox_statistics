///////////////////////////////////////////////////////////////////////////////
// range::chain::joint_view.hpp                 		 					 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_RANGE_EX_CHAIN_JOINT_VIEW_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_RANGE_EX_CHAIN_JOINT_VIEW_HPP_ER_2009
#include <vector>
#include <boost/mpl/void.hpp>
#include <boost/range.hpp>

#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/transform_view.hpp>

#include <boost/statistics/detail/fusion/joint_view/bind_range.hpp>
#include <boost/statistics/detail/range_ex/chain/nest.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace range{

namespace result_of{

    // Seq1 : {e[j]:j=1,...,n}; e[j] is a fusion container
    // Seq2 : {r[j]:j=1,...,n}; r[j] is a range of fusion containers
    //
	// Returns a range formed by chaining {f(e[j],r[j]): j=1,...,n}
    // f(e[j],r[j]) = {joint_view(e[j],r[j][k]):k=1,...,m}
    template<typename Seq1,typename Seq2>
	struct chain_joint_view{

    	struct f{
        	f(){}
			template<typename T>
			struct remove_cref : boost::remove_cv<
            	typename boost::remove_reference<T>::type
            >{};

			template<typename Seq>
        	struct result_impl{

        		typedef typename boost::fusion::result_of::at_c<Seq,0>::type cref0_;
        		typedef typename boost::fusion::result_of::at_c<Seq,1>::type cref1_;
        		typedef typename remove_cref<cref0_>::type at0_;
        		typedef typename remove_cref<cref1_>::type at1_;
        		typedef detail::fusion::joint_view::result_of::bind_range<
                	at0_,at1_
                > meta_;
        		typedef typename meta_::type type;
        		static type call(const Seq& seq){
            		return meta_::call(
                		boost::fusion::at_c<0>(seq),
                		boost::fusion::at_c<1>(seq)
            		);
        		}
    		};
                    
			template<typename S> struct result{};
		
        	template<typename F,typename Seq>
			struct result<F(const Seq&)> : result_impl<Seq>{};

			template<typename Seq>
			typename result_impl<Seq>::type
        	operator()(const Seq& seq)const{
        		typedef result_impl<Seq> meta_;
        		return meta_::call(seq);
        	}

		};
		typedef boost::fusion::result_of::make_vector<
        	const Seq1&,
            const Seq2&
        > seqs_; 
        typedef boost::fusion::zip_view<seqs_> view_;
			
        typedef typename 
            boost::fusion::result_of::transform<view_,f>::type res1_;
                
        typedef typename statistics::detail::range::result_of
            ::nest_chain<res1_>::type type;
			
        static type call(const Seq1& seq1,const Seq2& seq2){
            return statistics::detail::range::nest_chain(
                boost::fusion::transform(
                    boost::fusion::zip_view<seqs_>(
                        boost::fusion::make_vector(seq1,seq2)
                    ),
                    f()
                )
            );
        }
	};

}// result_of


	template<typename Seq1,typename Seq2>
    typename detail::range::result_of::chain_joint_view<Seq1,Seq2>::type
    chain_joint_view(const Seq1& seq_x,const Seq2& seq_ry){
		typedef detail::range::result_of::chain_joint_view<Seq1,Seq2> meta_;
        return meta_::call(seq_x,seq_ry);    
    }

}// range
}// detail
}// statistics
}// boost

#endif