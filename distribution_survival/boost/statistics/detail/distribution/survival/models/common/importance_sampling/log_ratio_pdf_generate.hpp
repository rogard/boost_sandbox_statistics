/////////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::common::importance_sampling::log_ratio_pdf_generate.hpp //
//                                                                           	   		   //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                      		   //
//  Software License, Version 1.0. (See accompanying file                          		   //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)               		   //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_GENERATE_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_LOG_RATIO_PDF_GENERATE_HPP_ER_2009
#include <algorithm>
#include <boost/range.hpp>
#include <boost/statistics/detail/distribution/model/models/likelihood/iid/include.hpp>
#include <boost/statistics/detail/distribution/model/models/posterior/include.hpp>
#include <boost/statistics/detail/distribution/model/key/include.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/log_ratio_pdf_generator.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{

	template<
    	typename TagPar,
        typename TagLpdf,
        typename ItW,
        typename Pr,
        typename M,
        typename ItD,
        typename ItP
    >
	ItW generate_log_ratio_pdf(
    	ItW it_w,
        const Pr& prior,
        const M& model,
        ItD b_d, // dataset
        ItD e_d,
        ItP b_p, // proposals {(p,log_pdfs)}
        ItP e_p
    )
    {
		typedef boost::iterator_range<ItD> dataset_;

        typedef distribution::model::iid_likelihood<M,dataset_> lik_;
        typedef distribution::model::posterior<Pr,lik_> post_;

		dataset_ dataset(b_d,e_d);

        post_ post = post_((
            distribution::model::keyword::prior = prior,
            distribution::model::keyword::model = model,
            distribution::model::keyword::dataset = dataset
        ));
        return std::transform(
            b_p,
            e_p,
            it_w,
        	make_log_ratio_pdf_generator<TagPar,TagLpdf>(post)
        );
	}
    
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif
