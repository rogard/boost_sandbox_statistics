///////////////////////////////////////////////////////////////////////////////
// statistics::detail::fusion::joint_view::binder2.hpp                        //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_FUSION_JOINT_VIEW_BINDER2_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_FUSION_JOINT_VIEW_BINDER2_HPP_ER_2009
#include <vector>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/joint_view.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace fusion{
namespace joint_view{

	// binds a sequence of type Seq1 to a sequence of arbitrary type. Its value
    // is the floor(i1/n)'s element of a stored vector where i1 is the
    // number of calls and n a pre-specified number. i1 is reset to n when
    // it reaches n.
    //
    // This class won't be necessary when concat(range1,range2) becomes avail. 
    // See boost.user mailing list 4/5/09.
	template<
    	typename Seq1, 
        bool is_left = true
    >
	class binder2
    {
    	typedef std::vector<Seq1> vec_seq1_type;
    	typedef typename boost::range_size<vec_seq1_type>::type size_;
    
    	typedef boost::is_reference<Seq1> meta_is_ref_;
		BOOST_MPL_ASSERT(( boost::mpl::not_< meta_is_ref_ > ));

		typedef typename boost::add_const<Seq1>::type c_seq1_;

		template<typename T0,typename T1,template<typename,typename> class F>
        struct meta_
         : boost::mpl::eval_if_c< 
        	is_left,
            boost::mpl::identity< F<T0,T1> >,
            boost::mpl::identity< F<T1,T0> >
        >{};

		template<typename Seq2>
        struct meta_view_ : meta_<
        	c_seq1_,
        	typename boost::add_const<Seq2>::type,
            boost::fusion::joint_view
        >{};
    
		public:

		typedef Seq1 seq1_type;

		template<typename S>
        struct result{};

		template<typename F,typename Seq2>
        struct result<F(const Seq2&)> : meta_view_<Seq2>{};

		binder2(){}
        template<typename It1,typename N>
		binder2(It1 b_seq1,It1 e_seq1,N n) 
        	: vec_seq1_(b_seq1,e_seq1), i_(0), n_(n){}    	
        binder2(const binder2& that) 
        	: vec_seq1_(that.vec_seq1_),i_(that.i_),n_(that.n_){}

		binder2& operator=(const binder2& that)
        {
        	if(&that!=this)
            {
            	this->vec_s1_ = that.vec_seq1;
                this->i_ = that.i_;
                this->n_ = that.n_;
            }
        	return (*this);
        }

		template<typename Seq2>
		typename boost::lazy_enable_if_c<
        	is_left,
			meta_view_<Seq2>
        >::type
        operator()(const Seq2& seq2)const
        {
        	typedef typename meta_view_<Seq2>::type view_;
        	return view_(this->vec_seq1_[this->post_incr()],seq2);
		}

		template<typename Seq2>
		typename boost::lazy_disable_if_c<
        	is_left,
			meta_view_<Seq2>
        >::type
        operator()(const Seq2& seq2)const
        {
        	typedef typename meta_view_<Seq2>::type view_;
        	return view_(seq2,this->vec_seq1_[this->post_incr()]);
		}

		const size_& n()const{ return this->n_; }

        private:
		size_ post_incr()const{ 
        	if(this->i_ == this->n()){ this->i_ = 0; }
            return (this->i_)++;
        }
		vec_seq1_type vec_seq1_;
        mutable size_ i_;
        size_ n_;
    };

}// joint_view
}// fusion
}// detail
}// statistics
}// boost

#endif