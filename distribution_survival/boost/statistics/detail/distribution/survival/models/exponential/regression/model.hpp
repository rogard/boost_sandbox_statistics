

/*

    template<typename T,typename Tag>
    class regression_model_impl
    {
        public:        
          
        template<typename P,typename M>
        void set_parameter(const P& p,const M& betas){
            boost::fusion::at_key<Tag>(betas) = p;
        }

        template<typename X,typename M>
        T cross_prod(const X& x,const M& betas)const
        {
            typedef boost::fusion::vector<const X&, const M&> vec_;
            typedef zip_view<vec_> view_;
            view_ view(vec_(x,betas));

            return boost::fusion::accumulate(view, static_cast<T>(0), f);
        }
			                  
    };
    

	template<typename Tag>
	class regression_model2 : public regression_model_impl<T,Tag>
    {
    
        template<typename Args>
        set_parameter(const Args& args)
        {
			boost::shared_features::extract_result<Betas>(args)        
        }
                
    };
    
*/
    
    