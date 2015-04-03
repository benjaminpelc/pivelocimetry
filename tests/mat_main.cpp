#include <iostream>
#include "../lib/Mat2.hpp"

int main(int argc, char** argv)
{
	auto m = Mat2<double>(3, 5, 3.1415);

	/* Test subscript notation */
	auto firstElem = m[0];
	std::cout << "First elem should be 3.1415: " << firstElem << std::endl;

	m[3] = 1.01;
	std::cout << "m[3] should equal 1.01: " << m[3] << std::endl;

	if (m.size() != 15)
		std::cout << "m.size() should equal 15" << std::endl;

	std::cout << m.getElem(1) << std::endl;


	auto mCopy = Mat2<double>(m);

	std::cout << "mCopy[3] should equal 1.01: " << mCopy[3]  << std::endl;

	return 0;
}
