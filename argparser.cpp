#include <iostream>
#include <algorithm>

#include "bppiv_clap.h"

int main(int argc, char** argv)
{
	std::cout << "Command line argument parsing" << std::endl;

	/* if args, do something */
	if (argc > 1) {
		PivClap pclap(argc, argv);
		// std::for_each(clap.begin(), clap.end(), [](auto a){ std::cout << "An arg" << std::endl; }  );

		if (pclap.hasFlag("-p")) { std::cout << "Has print flag" << std::endl; }
		if (pclap.hasParam("-p")) { std::cout << "Has param" << std::endl; }

		if (pclap.hasFlag("-c")) {
			if (pclap.hasParam("-c")) {
				std::cout << "Has config flag with option" << std::endl;
			} else {
				std::cout << "Usage: -c requires argument" << std::endl;
			}
		}
	}

	return 0;
}
