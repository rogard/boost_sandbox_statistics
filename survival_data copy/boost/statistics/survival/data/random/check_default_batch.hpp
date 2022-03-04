



    template<unsigned k,typename It>
    void check_batch(It b_r,It e_r,){
        typedef model::model_covariate_parameter_<model_type,x_type,parameter_type>       
        mcp_;
            typedef surv::data::meta_failure_distribution<model_>   meta_fd_;
            typedef meta_fd_::type                                  fd_;
            if(n_ks_data>0){   
                ofs_ks << (format("batch %1%, ")%i).str() << std::endl;
                for(unsigned i = 0; i<k; i++){
                    ofs_ks << (format("x[%1%] : ")%i).str();
                    fts.clear();
                    
                    surv::data::failure_times<k>(
                        boost::begin(pr_mngr.records()),
                        boost::end(pr_mngr.records()),
                        i,
                        std::back_inserter(fts)
                    );
                    mcp_ mcp(
                        xm_mngr.model_wrapper(),
                        xm_mngr.x_values()[i],
                        par
                    );
                    fd_ fail_dist = surv::data::make_failure_distribution(mcp);

                    kss.clear();
                    statistics::empirical_cdf
                     ::sequential_kolmogorov_smirnov_distance(
                        fail_dist,
                        boost::begin( fts ),
                        boost::end( fts ),
                        n_ks_data,
                        std::back_inserter( kss )
                    );
 
                    if(n_ks_data>1){
                        // Desired result: kss[0] > kss.back();
                        ofs_ks << kss[0] << ',' << kss.back();
                    }
                    ofs_ks << std::endl;
                    ofs_ks.flush();
                }
            }
        }
    }
