#include <iostream>

#include "../lib/Mat2.hpp"
#include "../src/Disp.hpp"
#include "../src/PivVector.hpp"
#include "../src/Peak.hpp"
#include "../src/PivPoint.hpp"


using namespace PivEng;

int main(int argc, char** argv)
{
	Mat2<double> d17(17, 17);
	Mat2<int> i6(6, 6);

	std::cout << "Mat2<double> 17x17:\t" << sizeof(d17) << std::endl;
	std::cout << "Mat2<int> 6x6:     \t" << sizeof(i6) << std::endl;

	Disp disp{};
	std::cout << "Disp:              \t" << sizeof(disp) << std::endl;

	PivVector piv_vector{};
	std::cout << "PivVector:         \t" << sizeof(piv_vector) << std::endl;

	Peak peak{};
	std::cout << "Peak:              \t" << sizeof(peak) << std::endl;

	PivPoint piv_point{};
	std::cout << "PivPoint:          \t" << sizeof(piv_point) << std::endl;


	return 0;
}
