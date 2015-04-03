#include <iostream>
#include "../src/IntMap.hpp"

int main(int argc, char** argv)
{
	std::cout << "Hello, all" << std::endl;

	auto i1 = IntMap(8, 8);

	auto ctr(0);
	for(auto& i : i1) {
		i += ctr++;
	}

	for(auto& i : i1) {
		std::cout << i << std::endl;
	}

	auto i2 = i1;

	return 0;
}
