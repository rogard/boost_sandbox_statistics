

namespace ppp{

    template<typename Tag,typename F,typename U>
    struct dispatcher{

        dispatcher(U& u,F f):u_(&u),f_(f){}
        
        template<typename T>
        void operator()(const t& in)const{        
            field_value<Tag>(this->u) = this->f_(
                field_value<Tag>(in);
            );
        }

        U* u_;
        F f_;
        
    };


    template<typename U,typename SeqF>
    struct dispatchers
    {
        
        
    };
        
}

