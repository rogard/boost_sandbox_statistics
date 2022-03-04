#ifndef BOOST_STATISTICS_DETAIL_RANGE_TMP_HPP_ER_2010
#define BOOST_STATISTICS_DETAIL_RANGE_TMP_ER_2010

namespace boost{
namespace statistics{
namespace detail{
namespace range{


struct tmp{

	template<typename Seq>
	struct result_impl :  boost::remove_cv<
        	typename boost::remove_reference<
				typename boost::fusion::result_of::at_c<const Seq,0>::type
            >::type
        >{};

	template<typename S>
    struct result{};
    
    template<typename F,typename Seq>
    struct result<F(const Seq&)>: result_impl<Seq>{}; 

//	typedef boost::mpl::int_<0> 				tag1_;
//	typedef boost::fusion::pair<tag1_,double> 	pair1_;
//  typedef boost::fusion::map<pair1_>			map1_;
//	typedef map1_ result_type;

	template<typename Seq>
    typename result_impl<Seq>::type
    operator()(const Seq& seq)const{
    	return boost::fusion::at_c<0>(seq);
    }

};

}// range
}// detail
}// statistics
}// boost

#endif
