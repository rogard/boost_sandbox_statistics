//////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::importance_sampling::log_ratio_pdf_generator.hpp //
//                                                                           		//
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                		//
//  Software License, Version 1.0. (See accompanying file                    		//
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         		//
//////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_GENERATOR_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_GENERATOR_HPP_ER_2009
#include <boost/fusion/include/at_key.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {

	// Usage:
    // Let [b,e) contain a sequence of maps, each element of which contains
    // a value x and the lpdf 
    // generated it
    // std::transform(b,e,out,make_log_ratio_pdf<TagP,TagLPdf>(dist));
    // 
    template<typename TagX,typename TagLpdf,typename D>
    class log_ratio_pdf_generator{
    	public:

		typedef typename distribution::meta::value<D>::type result_type;

		log_ratio_pdf_generator(const D& dist):dist_(dist){}
		log_ratio_pdf_generator(const log_ratio_pdf_generator& that)
        :dist_(that.dist_){}
        
        template<typename M>
        result_type operator()(const M& map)const
        {
            result_type p = boost::fusion::at_key<TagX>(map);
            result_type l = boost::fusion::at_key<TagLpdf>(map);
            result_type log_r = log_unnormalized_pdf(this->dist_,p); 
            log_r -= l; 
            return log_r;
        }
        
        private:
		const D& dist_;     
    };

	template<typename TagX,typename TagLpdf,typename D>
    log_ratio_pdf_generator<TagX,TagLpdf,D>
	make_log_ratio_pdf_generator(const D& dist)
    {
		typedef log_ratio_pdf_generator<TagX,TagLpdf,D> result_;
        return result_(dist);
	}

}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif
