//////////////////////////////////////////////////////////////////////////////
// unit_test_fun.hpp                                                        //
//                                                                          //
//  (C) Copyright 2009 Erwann Rogard                                        //
//  Use, modification and distribution are subject to the                   //
//  Boost Software License, Version 1.0. (See accompanying file             //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)        //
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_KOLMOGOROV_SMIRNOV_UNIT_TEST_FUN_HPP_ER_2009
#define BOOST_STATISTICS_DETAIL_NON_PARAMETRIC_KOLMOGOROV_SMIRNOV_UNIT_TEST_FUN_HPP_ER_2009
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/statistics/detail/non_parametric/kolmogorov_smirnov/statistic.hpp>

namespace boost{
namespace statistics{
namespace detail{
namespace kolmogorov_smirnov{

        template<typename D>
    	struct unit_test_fun{

            typedef typename D::value_type value_type;
        
            typedef boost::numeric::bounds<value_type> bounds_;

            unit_test_fun() : ks0( bounds_::highest() ){}
		
            template<typename AccSet>
            void operator()(const AccSet& acc,const D& d,std::ostream& os)const{
                namespace ns = boost::statistics::detail::kolmogorov_smirnov;
            	value_type ks1 = ns::statistic<value_type>( acc, d );
                bool ok = false; // (ks1 - ks0) < bounds_::smallest(); 
                BOOST_WARN( ok );
                os 
                    << '('
                    << boost::accumulators::extract::count(acc) 
                    << ','
                    << ks1
                    << ','
                    << ok
                    << ')'
                    << std::endl;	    
                
                // Warn not check for 2 reasons:
                // - The inequality is only probabilistic
                // - For very large sample size, numeric error may dominate
                
                this->ks0 = ks1;
                
            }
            
            private:
            mutable value_type ks0;
    	};

}// kolmogorov_smirnov
}// detail
}// statistics
}// boost

#endif
