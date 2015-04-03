#include <iostream>
#include "../lib/Mat2.hpp"

int main(int argc, char** argv)
{
	auto m = Mat2<double>(3, 5, 3.1415);

	std::cout << m.getElem(1) << std::endl;

	return 0;
}
