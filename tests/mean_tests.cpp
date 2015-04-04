#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"

using namespace bpu;

TEST_CASE( "BPU::mean", "Integers" ){

	std::vector<int> v{1,4,3,2,3,5,3,4};
	auto expectedInt = 3;
	auto expectedDouble = 25.0/8;

	SECTION( "mean should equal 3" ) {
		CHECK(mean<int>(v) == expectedInt);
	}
	
	SECTION( "mean should equal 3.125" ) {
		CHECK(mean<double>(v) == expectedDouble);
	}
	
}

TEST_CASE( "BPU::mean single element container", "Single element" ){

	std::vector<double> v{3.141};
	auto expectedInt = 3;
	auto expectedDouble = 3.141;

	SECTION( "mean should equal 3" ) {
		CHECK(mean<int>(v) == expectedInt);
	}
	
	SECTION( "mean should equal 3.141" ) {
		CHECK(mean<double>(v) == expectedDouble);
	}
	
}
