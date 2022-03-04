


namespace map2{

	template<typename K,typename V>
	class element{
    	typedef first_type{};
    	typedef second_type{};
    
    	typedef boost::fusion::map<
        	boost::fusion::pair<first_type,K>,
            boost::fusion::pair<second_type,V>
        > type;
    };
    
	template<typename K,typename V>
	class container{
    	typedef first_type{};
    	typedef second_type{};
    
    	typedef boost::fusion::map<
        	boost::fusion::pair<first_type,K>,
            boost::fusion::pair<second_type,V>
        > type;
    };

}