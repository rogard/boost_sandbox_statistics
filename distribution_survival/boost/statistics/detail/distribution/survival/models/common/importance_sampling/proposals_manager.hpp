/////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::models::common::importance_sampling::proposals_manager.hpp  //
//                                                                           		   //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                		   //
//  Software License, Version 1.0. (See accompanying file                    		   //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         		   //
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_PROPOSALS_MANAGER_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_MODELS_IMPORTANCE_SAMPLING_PROPOSALS_MANAGER_HPP_ER_2009
#include <boost/typeof/typeof.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/statistics/detail/traits/remove_cvref.hpp>
#include <boost/statistics/detail/distribution_common/meta/value.hpp>
#include <boost/statistics/detail/distribution_common/meta/random/distribution.hpp>
#include <boost/statistics/detail/distribution_common/meta/random/generator.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace importance_sampling{

    template<typename D>
	class proposals_manager{
        typedef typename distribution::meta::value<D>::type val_;
        typedef distribution::meta::random_distribution<D> meta_random_;
        typedef typename meta_random_::type random_;
        typedef typename random_::result_type par_value1_;
		typedef typename statistics::detail::traits::remove_cvref<
        	par_value1_
        >::type par_value_;
    
		public:
        proposals_manager(const D& dist):dist_(dist){}
		proposals_manager(const proposals_manager& that):dist_(that.dist_){}
        
		// Tags
        struct tag{
			struct parameter{};
			struct log_pdf{};
        };

		typedef typename tag::parameter tag_par_;
		typedef typename tag::log_pdf tag_lpdf_;

    	typedef typename boost::fusion::map<
        	boost::fusion::pair<tag_par_,par_value_>,
            boost::fusion::pair<tag_lpdf_,val_>
    	> proposal_;    

    	typedef std::vector<proposal_> proposals_type;

        // Generate posterior sample

		const D& distribution()const{ return this->dist_; }

		template<typename U,typename N>
		void refresh(U& urng,N n){
        	BOOST_AUTO(
            	gen,
                distribution::make_random_generator(urng,this->dist_)
            );
            this->proposals_.clear();
			this->proposals_.reserve(n);
            for(unsigned i = 0; i<n; i++)
            {
        		par_value_ p = gen();
            	val_ lpdf = log_unnormalized_pdf(this->dist_,p);
            	this->proposals_.push_back(
                	boost::fusion::make_map<tag_par_,tag_lpdf_>(p,lpdf)
            	);
            }
            
		}
        
        const proposals_type& operator()()const{ return this->proposals_; }
        
        private:
        proposals_type proposals_;
		D dist_;
	};

}// importance_sampling
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif