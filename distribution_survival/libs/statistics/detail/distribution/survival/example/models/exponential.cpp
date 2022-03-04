////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::example::data::exponential.cpp                             //
//                                                                                    //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                         //
//  Software License, Version 1.0. (See accompanying file                             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                  //
////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <algorithm>
#include <string>
#include <ext/algorithm>
#include <fstream>

#include <boost/mpl/int.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/range.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility.hpp>

#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/make_map.hpp>

#include <boost/statistics/detail/math/constant/shortcut.hpp>

#include <boost/statistics/detail/fusion/joint_view/bind_iterator.hpp>

#include <boost/statistics/detail/distribution_common/meta/random/generator.hpp>
#include <boost/statistics/detail/distribution_toolkit/distributions/normal/include.hpp>

#include <boost/statistics/detail/fusion/joint_view/bind_iterator.hpp>

#include <boost/statistics/detail/distribution/survival/record/key/include.hpp>
#include <boost/statistics/detail/distribution/survival/record/random/generate.hpp> 	

#include <boost/statistics/detail/distribution/survival/response/common/factory2.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/include.hpp>
#include <boost/statistics/detail/distribution/survival/response/common/generator.hpp>

#include <boost/statistics/detail/distribution/survival/models/common/meta/include.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/cg.hpp>
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/manager.hpp> 
#include <boost/statistics/detail/distribution/survival/models/common/importance_sampling/proposals_manager.hpp> 

#include <boost/statistics/detail/distribution/survival/models/exponential/scalar/include.hpp>

#include <libs/statistics/detail/distribution/survival/example/models/exponential.h>

void example_model_exponential(
    long n_runs,                 // = 5e4; 
    long n_r,     // records     // = 
    long n_mod,                  // = 1e3;
    long n_p,     // proposals   // = 1e4; 
    long n_t,     // targets     // = 1e4;
    double time_analysis,        // = const_::inf_;
    std::string out_path,        // = "/Users/erwann/projets/2009/Xcode/survival/build/Release/
    std::ostream& out
)
{

    out << "-> example_model_exponential : ";

    out.flush();
    
    // Steps shown in this example:
    //
    // Given a likelihood model, a covariate level, and a prior.
    // for each of a set of runs,
    // - samples a parameter, p, from the prior
    // - samples failure times given the model at p
    // - sample from the posterior distribution using importance sampling
    // - computes importance sampling statistics such as ESS
    // - saves the cook-gelman statistic for that run
    
    using namespace boost;
    using namespace statistics;
    namespace stat = boost::statistics::detail;
    namespace is = stat::importance_sampling;
    namespace dist = stat::distribution;
    namespace ds = dist::survival;
    namespace dm = dist::model;
	namespace jv = stat::fusion::joint_view;

    typedef std::string                 str_;
    typedef std::ofstream               ofs_;

    typedef dm::tag::covariate          tag_x_; // nec?
    typedef dm::tag::response           tag_y_; // nec?
    
    typedef ds::record::tag::entry_time tag_et_;
    typedef ds::record::tag::failure_time tag_ft_;
    typedef dm::tag::dataset            tag_dset_;
    typedef dm::tag::model              tag_m_;
    typedef dm::tag::prior              tag_pr_;
    typedef mt19937                     urng_;

    // Cg
    const str_ cg_path = out_path + "cg";
    ofs_ ofs_cg( cg_path.c_str() ); 

    typedef double val_;
	typedef stat::math::constant::shortcut<val_> const_;
    typedef boost::math::normal_distribution<val_> prior_; // prior
	typedef ds::importance_sampling::proposals_manager<prior_> proposals_mngr_;

    const val_ max_log      = 100.0;
    const val_ prior_mu     = 0.0;
    const val_ prior_sigma  = 5.0;
    const val_ x_val        = -1.0;
    const val_ et_val       = 0.0;  // entry_time
    typedef val_ p_; // parameter
    typedef dist::survival::response::event<val_> y_val_; // response
    typedef std::vector<val_> 	vec_val_;
    typedef std::vector<p_> 	vec_p_;
    
    typedef boost::fusion::result_of::make_map<tag_ft_,val_>::type 	ft_;
    typedef boost::fusion::result_of::make_map<tag_et_,val_>::type 	et_;
    typedef boost::fusion::result_of::make_map<tag_x_,val_>::type 	x_;

    typedef std::vector<ft_> vec_ft_;

    typedef ds::response::factory2<y_val_> 		factory2_;
    typedef ds::response::generator<factory2_> 	y_gen_;
    typedef std::vector<y_gen_::y_>				vec_y_;

    typedef proposals_mngr_::tag::parameter tag_par_;
    typedef proposals_mngr_::tag::log_pdf  	tag_lpdf_;
    typedef boost::fusion::result_of::make_map<
    	tag_par_,tag_lpdf_,p_, val_
    >::type p_lpdf_;    
    typedef std::vector<p_lpdf_> proposals_;
    typedef ds::exponential_model<val_> model_;

    // typedef detail::fusion::joint_view::result_of::flatten_bind_range;

    urng_ urng;
    prior_ prior(prior_mu,prior_sigma);
    proposals_mngr_ proposals_mngr(prior);
    proposals_mngr.refresh(urng,n_p);
    
    model_ model;
    et_ et(boost::fusion::make_pair<tag_et_>(et_val));
    // Note that a dataset with alternating covariate values say 
    // -1,-1,-1, 1, 1, 1 can be created with joint_view::flatten_range
    
	x_ x(boost::fusion::make_pair<tag_x_>(x_val));

    vec_ft_	vec_ft;	// failure times
    vec_ft.reserve(n_r);
    vec_val_	vec_w;   // importance weights
    vec_p_ 		targets;   
    vec_y_		vec_y; vec_y.reserve(n_r);
    p_ p;
    {
        BOOST_AUTO(g_p,dist::make_random_generator(urng,prior));
        for(unsigned i_run = 0; i_run<n_runs; i_run++)
        {
            {   // sample records given (x,model)
                p = g_p(); 
                model.set_parameter( p );
                vec_ft.clear();
                ds::record::generate_n(
                	std::back_inserter(vec_ft), 
                    n_r, urng, model, 
                    boost::fusion::at_key<tag_x_>(x)
                );
            } 
            {	
				
                // Generate responses
                vec_y.clear(); 
                ds::response::generator<factory2_>::call(
                	std::back_inserter(vec_y),
                	et_val,
                    boost::begin(vec_ft),
                    boost::end(vec_ft),
                    time_analysis
                );

                // Generate posterior sample
				typedef ds::importance_sampling_manager<	
                	tag_par_,tag_lpdf_,val_> is_mngr_;
                is_mngr_ is_mngr(max_log);

				typedef boost::range_iterator<vec_y_>::type it_y_; 
				typedef jv::result_of::bind_iterator<x_,it_y_>::type it_xy_;
                it_xy_ xy_b = jv::bind_iterator(x,boost::begin(vec_y));
                it_xy_ xy_e = jv::bind_iterator(x,boost::end(vec_y));

                is_mngr.refresh(
                	std::back_inserter( targets ),
                    n_t,
					xy_b, 
                    xy_e,
        			boost::begin(proposals_mngr()), 	
                    boost::end(proposals_mngr()),
                    prior, model,
                    urng
                );
                                
                if(i_run%n_mod == 0)
                {
                    const str_ str = "i = %1%, %2%";
                    boost::format f(str);
                    f % i_run  % is_mngr.description(); 
                    out << f.str() << std::endl;
                    out.flush();
                }
            }
            {
                ofs_cg 
                	<< ds::cg(boost::begin(targets),boost::end(targets),p) 
                    << ' ';
                ofs_cg.flush();
            }
        }// runs
    }

    out << "<-" << std::endl;
}
