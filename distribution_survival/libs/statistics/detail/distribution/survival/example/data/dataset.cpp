///////////////////////////////////////////////////////////////////////////////////////////
// distribution::survival::example::data::dataset.cpp                                    //
//                                                                                       //
//  Copyright 2009 Erwann Rogard. Distributed under the Boost                            //
//  Software License, Version 1.0. (See accompanying file                                //
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                     //
///////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <ostream>
#include <fstream>
#include <stdexcept>
#include <string> //needed?
#include <algorithm>
#include <iterator>
#include <boost/typeof/typeof.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/range.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp> 
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/fusion/container/generation/make_map.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/statistics/detail/math/function/versatile_equal.hpp>

#include <boost/statistics/detail/distribution/model/tag/response.hpp>
#include <boost/statistics/detail/distribution/model/tag/covariate.hpp>

#include <boost/statistics/detail/distribution/survival/record/key/include.hpp>
#include <boost/statistics/detail/distribution/survival/response/types/right_truncated/include.hpp>
#include <boost/statistics/detail/distribution/survival/record/function/include.hpp>

#include <libs/statistics/detail/distribution/survival/example/data/dataset.h>

void example_data_dataset(std::ostream& out)
{
    out << "-> example_data_dataset : ";
    
    // Steps shown in this example:
    //
    // Records creation
    // Events creation
    // I/O
    // Statistics
    
    using namespace boost;
    namespace stat = boost::statistics::detail;
    namespace ds = stat::distribution::survival;
    namespace dm = stat::distribution::model;

    typedef unsigned val_; // do not modify, results depend on it.

    // Record
    typedef dm::tag::covariate          tag_x_;
    typedef dm::tag::response           tag_y_;
    typedef ds::record::tag::entry_time      tag_et_;
    typedef ds::record::tag::failure_time    tag_ft_;
    typedef fusion::result_of::make_map<
        tag_et_,tag_ft_,val_,val_>::type record_;
    typedef std::vector<record_> records_;

    // Reponse
    typedef ds::response::event<val_> y_;
    typedef std::vector<y_> ys_;
    typedef ds::response::event_factory<val_> factory_;

    // I/O
    typedef boost::archive::text_oarchive oa_;
    typedef boost::archive::text_iarchive ia_;

    // Constants
    const unsigned n_record = 4; 
    const val_ entry_bound = n_record - 1;
    const val_ fail_time = 2;
    // [ Records ]
    records_ records;
    for(val_ i = 0; i<n_record; i++){
        records.push_back(
            boost::fusion::make_map<tag_et_,tag_ft_>(i,fail_time)
        );
    }

    out << " records : ";
    for(val_ i = 0; i<n_record; i++){
        out << ds::record::description( records[i] ) << ' ';
    }

    // [ Responses ]
    {
        ys_ ys;

        std::transform(
            boost::begin(records),
            std::lower_bound(
                 boost::begin(records),
                 boost::end(records),
                 boost::fusion::make_map<tag_et_>(entry_bound),
                 ds::record::less_than()
            ),
            std::back_inserter(ys),
            factory_(entry_bound)
        );

        // Analysis for n_record = 4 and entry_bound = 3;
        // et: entry time
        // ft: failure time
        // dt: time since entry
        //     et      ft      dt     ft<=dt  min(ft,dt)
        //      0       2       3       1       2
        //      1       2       2       1       2
        //      2       2       1       0       1
        //      3       2       0       NA      NA

        BOOST_ASSERT(boost::size(ys) == entry_bound);

        // [ Mean ]
    
        out << "mean events : " << std::endl;
    
        typedef ds::response::mean_event<val_> me_;
        // Analysis for n_record = 4 and entry_bound = 3;
        //      j       ft<=dt  min(ft,dt)  
        //      1       1       2
        //      2       1       2
        //      1       0       1
        // -------------------------------
        //      1       1/2=0   3/2 = 1         // Remember, val_ = unsigned,
        //      2       1       2               // not a float
        
    }
    {
    	// Mean events
        unsigned n_i = n_record / 2;
        for(unsigned j = 0; j<2; j++){
            records_ rs;
            for(unsigned i = 0; i<n_i; i++){
                rs.push_back( records[j + i*2] );
            }
            BOOST_ASSERT( boost::size(rs) == 2 );

            ys_ es;
            std::transform(
                boost::begin( rs ),
                std::lower_bound(
                    boost::begin( rs ),
                    boost::end( rs ),
                    boost::fusion::make_map<tag_et_>(entry_bound),
                    ds::record::less_than()
                ),
                std::back_inserter(es),
                factory_(entry_bound)
            );
			typedef ds::response::mean_event<val_> me_;
            me_ me = std::for_each( boost::begin(es), boost::end(es), me_() );
            out << me << std::endl;
        }
    }
    
    out << "<-" << std::endl;
}
