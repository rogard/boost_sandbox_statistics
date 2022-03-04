///////////////////////////////////////////////////////////////////////////////
// range_ex::chain::chain2.hpp                              				 //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_RANGE_EX_CHAIN2_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_RANGE_EX_CHAIN2_HPP_ER_2010
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/statistics/detail/range_ex/chain/nest.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace range{

	template<typename Vec>
	class chain2_impl{

		typedef chain2_impl<Vec> this_;
		//typedef typename result_of::nest_chain<Vec>::type lhs_;
        
        template<typename T>
        struct next_vec 
        	: boost::fusion::result_of::push_back<const Vec,T>{};

        template<typename T>
        struct result_impl
        {
        	typedef typename next_vec<T>::type next_vec_;
        	typedef chain2_impl<next_vec_> type;
            static type call(const this_& that,const T& arg){
            	const Vec& old = that.vec();
                next_vec_ nv = 
                	boost::fusion::push_back(old,arg);
            	return type(
                	nv
                );
            }
        };

		public:

		explicit chain2_impl(const Vec& vec):vec_(vec){}

        template<typename S>
    	struct result{};
        
    	template<typename F,typename T>
    	struct result<F(const T&)> : result_impl<T>{};
            
        template<typename T>
        typename result_impl<T>::type
        operator()(const T& arg)const{
        	typedef result_impl<T> meta_;
			return meta_::call(*this,arg);
        }


		//operator lhs_()const{
        //	return nest_chain(vec);
        //}
        
        const Vec& vec()const{ return this->vec_; }

		private:
    
    	Vec vec_;
    
    };
    
template<typename T>
chain2_impl<boost::fusion::vector<const T&> >
chain2(const T& a){
	typedef boost::fusion::vector<const T&> vec_;
    typedef chain2_impl<vec_> res_;
    vec_ vec(a);
	return res_(vec);
};

}// range
}// detail
}// statistics
}// boost

#endif