
//#include <cmath>
#include <stdexcept>
#include <fstream>
#include <ostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <algorithm>
#include <ext/algorithm> // is_sorted
#include <iterator>
#include <functional>

#include <boost/typeof/typeof.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/type_traits.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/timer.hpp>
#include <boost/range.hpp>
#include <boost/utility.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/math/tools/precision.hpp>
#include <boost/standard_distribution/distributions/normal.hpp>         //prior
#include <boost/standard_distribution/distributions/exponential.hpp>    //data

#include <boost/statistics/empirical_cdf/algorithm/sequential_kolmogorov_smirnov_distance.hpp>

#include <boost/dist_random/include.hpp>

#include <boost/statistics/model/include.hpp>
#include <boost/statistics/survival/data/include.hpp>
#include <boost/statistics/survival/model/models/exponential/include.hpp>


namespace boost{
namespace statistics{
namespace survival{
namespace data{
namespace random{

template<typename T = double, unsigned k = 2>
struct default_normal_exponential{
    typedef math::normal_distribution<T>                    prior_;
    typedef surv::model::exponential::model<T>              model_;
    typedef T                                               par_;
    typedef default_simulation_batches<
        k,
        T,
        prior_,
        par_
    > type;
};


    xm_mngr_ xm_mngr;
    {
        typedef std::vector<val_>                               vals_;
        vals_ x_vals;
        {
            using namespace boost::assign;
            x_vals += -0.5, 0.5;
        }
        BOOST_ASSERT(size(x_vals) == k);
        xm_mngr = xm_mngr_(
            boost::begin( x_vals ),
            boost::end( x_vals ),
            model_()
        );
    }
    {
        ofs_    ofs(xm_mngr_path.c_str());
        oa_     oa(ofs);
        oa      << xm_mngr;
        ofs.flush();
        ofs.close();
    }



}// random
}// data
}// survival
}// statistics
}// boost