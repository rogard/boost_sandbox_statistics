///////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::importance_sampling::log_ratio_pdf_statistics.hpp //
//                                                                           		 //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                		 //
//  Software License, Version 1.0. (See accompanying file                    		 //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         		 //
///////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_STATISTICS_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_STATISTICS_HPP_ER_2009
#include <boost/fusion/include/make_map.hpp>
#include <boost/statistics/detail/importance_sampling/statistics/percentage_effective_sample_size.hpp> //
#include <boost/statistics/detail/math/constant/shortcut.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{

	template<typename T>
	struct log_ratio_pdf_statistics{
        typedef accumulator::tag::percentage_effective_sample_size tag_ess_;
        typedef accumulator::tag::proportion_less_than tag_plt_; 
        typedef boost::accumulators::stats<tag_ess_,tag_plt_> stats_;
        typedef boost::accumulators::accumulator_set<T,stats_> acc_; 

		public:

		log_ratio_pdf_statistics(){}
    
    	template<typename It_w,typename T1>
        void operator()(It_w b_w,It_w e_w,const T1& eps)
    	{
    		typedef T val_;
        	acc_ a = std::for_each(
            	b_w,
            	e_w,
            	acc_(( accumulator::keyword::threshold = eps ))
        	);
            this->ess_ = boost::accumulators::extract_result<tag_ess_>(a);
            this->plt_ = boost::accumulators::extract_result<tag_plt_>(a);
		}

    	template<typename It_w,typename T1>
        void operator()(It_w b_w,It_w e_w){
			return (*this)(b_w,e_w,boost::math::tools::epsilon<T>());
		}

		T ess()const{ return this->ess_; }
		T percent_lt_eps()const{ return this->plt_; }
        
        private:
        T ess_,plt_;
    };
    
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif