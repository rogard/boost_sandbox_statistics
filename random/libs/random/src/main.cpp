#include <iostream>
#include <boost/array.hpp>
//#include <libs/random/example/poisson_speed.hpp>
//#include <libs/random/example/poisson_convergence.hpp>
#include <boost/random/poisson_ext/devroye/q_function/cross_check.hpp>
#include <boost/random/poisson_ext/devroye/q_function/self_checking.hpp>
#include <boost/random/poisson_ext/devroye/crtp/crtp.hpp>

//#include <boost/random/poisson_ext/devroye/detail/test_convergence.hpp>

	std::string say_int(int){ return "int"; }
	std::string say_int(long int){ return "long int"; }
	std::string say_int(...){ return "unknown"; }

int main(){

	// Also see sandbox/statistics/distribution_toolkit
	typedef std::string str_;
	typedef long int int_; // either of int or long int (important for high mean)

    std::cout << "result_type = " << say_int(int_()) << std::endl;

    using namespace boost::random::poisson::devroye;

     //boost::random::poisson::devroye::q::cross_check<double,int_>(4,1,10,0.001);

     typedef boost::numeric::converter<double,int_> conv_;
     typedef boost::math::policies::policy<> pol_;
     typedef q::self_checking<q::using_sum> self_;

     boost::random::poisson::devroye::q::fun<double,int_>(200,1000,pol_(),conv_(),self_());

    // mean *= factor1 at each of n1 iterations
/*
	{
    	int mean = 1;		
    	const int n1 = 7;	
    	const int factor1 = 4;

    	example_poisson_speed<int_>(
        	std::cout,
        	10 * 1000, 	// sample size	
        	n1,				
        	mean,			
        	factor1			
    	);
    }
	{
    	int mean = 1;		
		// sample_sz *= factor2 at each of n2 iterations
    	int sample_sz = 1;			
    	const int n1 = 7;	
    	const int factor1 = 10;
		const int n2 = 5; 	
		const int factor2 = 100;   

		std::cout << "poisson convergence{ " << std::endl;
    	std::cout << "(sample size,statistic) :" << std::endl;
		for(int i = 0; i<n1; i++){
    		example_poisson_convergence<int_>(
        		std::cout,
        		mean,		
        		n2,			
        		sample_sz, 	
        		factor2		
    		);
        	mean *= factor1;
    	}
		std::cout << "} " << std::endl;
	}
*/
    return 0;
}

