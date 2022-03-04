///////////////////////////////////////////////////////////////////////////////
// distribution::survival::response::right_truncated::event_factory.hpp   		 //
//                                                                           //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_FACTORY_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_DISTRIBUTION_SURVIVAL_RESPONSE_RIGHT_TRUNCATED_FACTORY_HPP_ER_2009
#include <stdexcept>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/statistics/detail/math/constant/shortcut.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/event.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/censoring_time.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/entry_time.hpp>
#include <boost/statistics/detail/distribution/survival/record/key/failure_time.hpp>
#include <boost/statistics/detail/distribution/survival/record/function/time_since_entry.hpp>

namespace boost {
namespace statistics{
namespace detail{
namespace distribution{
namespace survival {
namespace response {

    // returns a event at a given time of analysis
    template<typename T,typename B = bool>
    class event_factory{
        typedef statistics::detail::math::constant::shortcut<T> const_;

        typedef std::string str_;

        typedef record::tag::entry_time     tag_et_;
        typedef record::tag::failure_time   tag_ft_;
        typedef record::tag::censoring_time tag_ct_;
        
        template<typename M>
        struct has_ct
            : boost::fusion::result_of::has_key<M,tag_ct_>{};

        public:
        typedef event<T,B> result_type;
        
        event_factory():t_(static_cast<T>(0)){}
        template<typename T1>
        event_factory(const T1& t):t_(t){}

        template<typename M>
        typename boost::enable_if< has_ct<M>, result_type >::type
        operator()(const M& record)const
        {
            return this->impl(
                time_since_entry(record,this->time()),
                boost::fusion::at_key<tag_ft_>(record),
                boost::fusion::at_key<tag_ct_>(record)
            );
        }

        template<typename M>
        typename boost::disable_if< has_ct<M>, result_type >::type
        operator()(const M& record)const
        {
            T tmp = record::time_since_entry(record,this->time());
            return this->impl(
                tmp,
                boost::fusion::at_key<tag_ft_>(record)
            );
        }
        
        const T& time()const{ return this->t_; }
        
        private:

        // no const for dt intended
        result_type impl(T dt,const T& ft,const T& ct)const 
        {
            static const str_ msg = "event_factory::impl(%1%,%2%,%3%)";
            dt = (ct<dt)? ct : dt;
            
            if(!(dt < static_cast<T>(0)))
            {
                bool b = !( ft > dt );
                T rt = b ? ft : dt;
                return result_type(b, rt);
            }else{
                str_ str = ( boost::format(msg) % dt % ft % ct ).str();
                throw std::runtime_error( str );
            }
        }

        result_type impl(T dt,const T& ft)const
        {
            return this->impl(dt,ft,const_::inf_else_highest);
        }
        
        T t_;
    };

}// response
}// survival
}// distribution
}// detail
}// statistics
}// boost

#endif
