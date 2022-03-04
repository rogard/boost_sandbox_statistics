///////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::common::importance_sampling::manager.hpp  //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_MANAGER_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_MANAGER_HPP_ER_2009
#include <algorithm>
#include <vector>
#include <string>
#include <boost/format.hpp>
#include <boost/range.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/importance_sample.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/log_ratio_pdf_generate.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/log_ratio_pdf_statistics.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
	
    template<typename TagPar,typename TagLpdf,typename T = double>
	class importance_sampling_manager{
    	typedef std::string str_;
        typedef boost::format format_;
    	typedef std::vector<T> vec_val_;
        typedef importance_sampling::prepare_weights<T> pw_;
		typedef survival::log_ratio_pdf_statistics<T> stats_;
        
        public:

		typedef TagPar 	tag_par_;
        typedef TagLpdf tag_lpdf_;

		template<typename T1>
		importance_sampling_manager(const T1& max_log):pw(max_log){}
        
        template<
        	typename ItT,typename N_t,
        	typename ItD,typename It_p_lpdf,
            typename Pr,typename M,
            typename U
        >
        void refresh(
        	ItT it_targets,
            N_t n_t,
        	ItD b_d,
            ItD e_d,
            It_p_lpdf b_p_lpdf,
            It_p_lpdf e_p_lpdf,
            const Pr& prior,
            const M& model,
            U& urng
        )
        {
            vec_w.clear();
            generate_log_ratio_pdf<tag_par_,tag_lpdf_>(
                std::back_inserter(vec_w),
                prior, model,
                b_d, e_d,
        		b_p_lpdf, e_p_lpdf
            );
            this->pw(boost::begin(this->vec_w),boost::end(this->vec_w));
            survival::importance_sample<tag_par_>(
                it_targets,
                n_t,
                b_p_lpdf,
                e_p_lpdf,
                this->vec_w,
                urng
            );
        }

		template<typename T1>
		const stats_&  update_stats(const T1& eps)const{
            this->stats(
            	boost::begin(this->vec_w),
                boost::end(this->vec_w),
                eps
            );
            return this->stats;
        }
        
        template<typename T1>
		str_ description(const T1& eps)const{
			static const str_ str = "pws = %1%, ess = %2%, pc_lt_eps = %3%";
            format_ f(str);
            this->update_stats(eps);
            f% this->pw % this->stats.ess() % this->stats.percent_lt_eps();
            return f.str();
		}
        
		str_ description()const{
        	static const T eps = boost::math::tools::epsilon<T>();
        	return this->description(eps);
        }
        
        private:
    	vec_val_ vec_w; // importance weights
		mutable pw_ pw;
        mutable stats_ stats;
	
    };

}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif