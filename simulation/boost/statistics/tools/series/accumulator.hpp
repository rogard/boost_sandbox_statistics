///////////////////////////////////////////////////////////////////////////////
// accumulator.hpp                                                           //
//                                                                           //
//  Copyright 2010 Erwann Rogard. Distributed under the Boost                //
//  Software License, Version 1.0. (See accompanying file                    //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)         //
///////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_TOOLS_DETAIL_SERIES_ACCUMULATOR_HPP_ER_2010
#define BOOST_STATISTICS_TOOLS_DETAIL_SERIES_ACCUMULATOR_HPP_ER_2010
#include <boost/type_traits/remove_reference.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/statistics/tools/series/traits.hpp>
#include <boost/statistics/tools/series/assign_data.hpp>

namespace boost{ 
namespace statistics{
namespace detail{
namespace series{

    // This is an accumulater_set<> bound two objets : one generating the 
    // cumulative sample size (S), the other generating data (G) to be accumu-
    // lated. The features of interest are specified by an mpl vector F. Each 
    // nullary call generates a new set of samples which are passed to the accu-
    // mulator and the features of interest are then evaluated and returned in a 
    // data-structure.
    template<typename F,typename S,typename G>
    class accumulator{

        typedef typename G::distribution_type random_;
        typedef typename boost::remove_reference<
            S::result_type
        >::type size_;

        public:
        typedef typename boost::remove_reference<
            typename random_::result_type>::type sample_type; 
        typedef F features_type;
        typedef boost::accumulators::accumulator_set<
            sample_type,features_type> accumulator_type;

        typedef typename detail::series::data_of<
            acc_,features_type>::type result_type;

        accumulator():n_( 0 ){}

        accumulator(const S& s,const G& g)
        :n_series_( s ),gen_( g ),n_( 0 ){}

        accumulator(const Args& args,const S& s,const G& g)
        :acc_( args ),n_series_( s ),gen_( g ),n_( 0 ){}
    
        result_type operator()()const
        {   
            this->generate_accumulate();
            result_type result;
            detail::series::assign_data<F>( this->acc_, result );
            return result;
        }

        template<typename Args>
        result_type operator()(const Args& args)const
        {   
            this->generate_accumulate();
            result_type result;
            detail::series::assign_data<F>( this->acc_, args,result );
            return result;
        }
    
        private:
        void generate_accumulate()const{
            size_ new_n = this->series_(); 
            for(size_ i = this->n_; i<new_n; i++){ this->acc( this->gen() ); } 
            this->n_ = new_n;
        }

        A acc_;
        S n_series_;
        G gen_;
        size_ n_;
    };

    template<typename F,typename Args,typename S,typename G>
    detail::series::accumulator<F,S,G>
    make_accumulator(const S& series,const G& gen)
    {
        typedef detail::series::accumulator<F,S,G> result_;
        return result_(series,gen);
    }

    template<typename F,typename Args,typename S,typename G>
    detail::series::accumulator<F,S,G>
    make_accumulator(const Args& args,const S& series,const G& gen)
    {
        typedef detail::series::accumulator<F,S,G> result_;
        return result_(series,gen);
    }

}// accumulator
}// detail
}// statistics
}// boost

#endif
