#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"
#include <utility>

using namespace bpu;
using PairII = std::pair<int, int>;

TEST_CASE( "BPU::subtract_and_abs - Vector of integers" ){
	std::vector<int> a{1, 2, 3, 4, 5};
	std::vector<int> expected{2, 1, 0, 1, 2};
	bpu::subtract_and_abs(a, 3);

	SECTION( "First elemend should equal 2" ) {
		CHECK(a.front() == 2);
	}
	
	SECTION( "Integer vector" ) {
		CHECK(a == expected);
	}
	
}

TEST_CASE( "BPU::subtract_and_abs - Vector of doubles" ){
	std::vector<double> a{1.23, 2.32, 3, 4.43, 5.4};
	std::vector<double> expected(a);
	
	for(auto& e : expected)
		e = std::abs(e - 3.1);

	bpu::subtract_and_abs(a, 3.1);

	SECTION( "First elemend should equal 1.87" ) {
		CHECK(a.front() == std::abs(1.23 - 3.1));
	}
	
	SECTION( "Last elemend should equal 2.3" ) {
		CHECK(a.back() == std::abs(5.4 - 3.1));
	}

	SECTION( "Integer vector" ) {
		CHECK(a == expected);
	}
	
}
