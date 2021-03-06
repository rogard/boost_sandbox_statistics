///////////////////////////////////////////////////////////////////////////////////
// distribution::common::functor::derivative_derivative_log_unnormalized_pdf.hpp //
//                                                                           	 //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                	 //
//  Software License, Version 1.0. (See accompanying file                    	 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         	 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_FUNCTOR_DERIVATIVE_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_COMMON_FUNCTOR_DERIVATIVE_LOG_UNNORMALIZED_PDF_HPP_ER_2009
#include <boost/mpl/assert.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace functor{

    template<typename D>
    class derivative_log_unnormalized_pdf_
    {

        BOOST_MPL_ASSERT(( boost::mpl::not_< boost::is_reference<D> >)); 
        // use reference::wrapper if a ref is needed

        public:
        typedef D distribution_type;
        typedef typename common::meta::value<D>::type result_type;

        derivative_log_unnormalized_pdf_(){}
        derivative_log_unnormalized_pdf_(const D& d):d_(d){}
        derivative_log_unnormalized_pdf_(
        	const derivative_log_unnormalized_pdf_& that
        ):d_(that.d_){}
        derivative_log_unnormalized_pdf_& operator=(
        	const derivative_log_unnormalized_pdf_& that
        )
        {
            if(&that!=this)
            {
                d_ = that.d_;
            }
            return (*this);
        }

        template<typename X>
        result_type 
        operator()(const X& x)const{
            return derivative_log_unnormalized_pdf( this->distribution(), x );
        }
    
        const D& distribution()const{ return this->d_; }
    
        private:
        D d_;
    
    };

}// functor
}// distribution
}// detail
}// statistics
}// boost

#endif
