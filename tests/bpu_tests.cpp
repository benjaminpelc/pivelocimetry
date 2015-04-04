#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"

using namespace bpu;

TEST_CASE( "BPU::Median - Vectors", "Test median template function"){
	
	SECTION( "Odd length sorted int vector") {
		/* Some input data pretending to be some args. Simulate case with
	 	 * no arguments. The only element in argv is program name */
		std::vector<int> v{1, 2, 3, 4, 5};

		SECTION( "Median should equal 3" ) {
			CHECK(median(v) == 3);
		}
	}

	SECTION( "Odd length sorted int vector") {
		/* Some input data pretending to be some args. Simulate case with
	 	 * no arguments. The only element in argv is program name */
		std::vector<int> v{1, 2, 3, 4, 5, 6};

		SECTION( "Median should equal 3" ) {
			CHECK(median(v) == 3);
		}
	}
}
