#include <iostream>

//#include <libs/statistics/detail/non_parametric/example/frequency_int.h>
//#include <libs/statistics/detail/non_parametric/example/kolmogorov_smirnov.h>
//#include <libs/statistics/detail/non_parametric/test/contingency_table1.h>
//#include <libs/statistics/detail/non_parametric/test/contingency_table2.h>
#include <libs/statistics/detail/non_parametric/example/contingency_table1.h>

int main()
{
	//example_frequency_int(std::cout);
	//example_kolmogorov_smirnov( std::cout, 00.1, 0, 10, 0, 5);
	//example_kolmogorov_smirnov( std::cout, 01.0, 0, 10, 0, 5);
	//example_kolmogorov_smirnov( std::cout, 10.0, 0, 10, 0, 5);
	//test_contingency_table1();
	//test_contingency_table2();
	example_contingency_table1();

    return 0;
}