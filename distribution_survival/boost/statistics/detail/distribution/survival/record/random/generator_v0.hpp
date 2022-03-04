///////////////////////////////////////////////////////////////////////////////
// distribution::survival::record::random_generator_v0.hpp                   //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_GENERATOR_V0_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RECORD_GENERATOR_V0_HPP_ER_2009
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/make_map.hpp>

#include <boost/statistics/detail/distribution/survival/record/key/include.hpp>
#include <boost/statistics/detail/distribution/model/key/include.hpp>
#include <boost/statistics/detail/distribution/survival/failure_time/meta/include.hpp>

#include <boost/statistics/detail/distribution/survival/record/random/generator.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace distribution{
namespace survival{
namespace record{
namespace meta{

    template<typename T>
    struct random_generator<0,T>
    {
        // Generates failure times given a model, covariate and a unif
        // random generation

        typedef tag::failure_time tag_ft_;
        typedef typename 
                boost::fusion::result_of::make_map<tag_ft_,T>::type ft_;
        typedef ft_(*fp_)(const T&);
        typedef boost::function<T()> 	gen_val_;
        typedef boost::function<ft_()> 	type;
                
        template<typename X,typename M,typename U>
        static type call(const X& x,const M& m,U& urng)
        {
            return type(
                boost::lambda::bind<ft_>(
                    fp_(boost::fusion::make_map<tag_ft_>),
                        boost::lambda::bind<T>(
                        gen_val_(
                            failure_time::make_random_generator(
                                x,
                                m,
                                urng
                            )
                        )
                    )
                )
            );
        }

        template<typename Map,typename U>
        static type call(const Map& map,U& urng)
        {
            typedef model::tag::covariate 	tag_x_;
            typedef model::tag::model 		tag_m_;
            return call(
                boost::fusion::at_key<tag_x_>(map),
                boost::fusion::at_key<tag_m_>(map),
                urng
            );
        }
    };
        
}// meta
}// record                
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif        
        
