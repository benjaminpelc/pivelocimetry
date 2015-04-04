#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"

using namespace bpu;

TEST_CASE( "BPU::Median - Vectors", "Test median template function"){

	SECTION( "Single element container" ) {
		std::vector<double> v{9.9};

		SECTION( "Median should equal 9.9" ) {
			CHECK(median<double>(v) == 9.9);
		}
	}

	SECTION( "Empty container" ) {
		std::vector<double> v;

		SECTION( "Median should be null" ) {
			CHECK(median<double>(v) == 0);
		}
	}
	
	SECTION( "Odd length sorted int vector") {
		std::vector<int> v{1, 2, 3, 4, 5};

		SECTION( "Median should equal 3" ) {
			CHECK(median<int>(v) == 3);
		}
	}

	SECTION( "Even length sorted int vector") {
		std::vector<int> v{1, 2, 3, 4, 5, 6};

		SECTION( "Median should equal 4") {
			CHECK(median<int>(v) == 4);
		}

		SECTION( "Median should equal 3.5" ) {
			CHECK(median<double>(v) == 3.5);
		}
	}

	SECTION( "Odd length unsorted double vector") {
		std::vector<double> v{9.43, 5.01, 2.34, 4.43, 1.34, 3.94, 0.33};

		SECTION( "Median should equal 3.94" ) {
			CHECK(median<double>(v) == 3.94);
		}
		SECTION( "Median should equal 4" ) {
			CHECK(median<int>(v) == 4);
		}
	}

	SECTION( "Even length unsorted double vector") {
		std::vector<double> v{9.43, 5.01, 2.34, 4.43, 1.34, 3.94, 0.33, 0.35};
		auto expected = (2.34 + 3.94) / 2;

		SECTION( "Median should equal 3.14" ) {
			CHECK(median<double>(v) == expected);
		}
	}

	SECTION( "Should take rvalue" ) {
		SECTION( "Median should be 4" ) {
			auto med = median<int>(std::vector<int>{1,4,6,2,5});
			CHECK(med == 4);
		}
	}

	SECTION( "Does not modify container" ) {
		std::vector<double> v{9.43, 5.01, 2.34, 4.43, 1.34, 3.94, 0.33, 0.35};
		auto vCopy = v;
		SECTION( "Vector before should equal vector after" ) {
			median<double>(v);
			CHECK(vCopy == v);
		}
	}

	SECTION( "Accepts const container" ) {
		const std::vector<int> v{1,2,3,5};
		SECTION( "Median should equal 2.5" ) {
			CHECK(median<double>(v) == 2.5);
		}
	}
}
