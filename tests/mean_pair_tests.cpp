#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"
#include <utility>

using namespace bpu;
using PairII = std::pair<int, int>;

/*
 * template<typename TFirst, typename TSecond, typename Container>
 * std::pair<TFirst, TSecond> mean_pairs(Container&& c)
 */

TEST_CASE( "BPU::mean_pair", "Integers" ){

	std::vector<std::pair<int, int>> v(3);
	auto expected = std::make_pair<int, int>(2, 4);

	v[0] = std::make_pair<int, int>(1, 3);
	v[1] = std::make_pair<int, int>(2, 4);
	v[2] = std::make_pair<int, int>(3, 5);
	
	SECTION( "mean should equal (2, 4)" ) {
		auto result = mean_pairs<int, int>(v);
		CHECK(result == expected);
		CHECK(result.first == expected.first);
		CHECK(result.second == expected.second);
	}
	
	SECTION( "mean should equal (2.75, 4.75)" ) {
		v.push_back(std::make_pair<int, int>(5, 7));
		auto expected = std::make_pair<double, double>(2.75, 4.75);
		auto result = mean_pairs<double, double>(v);
		CHECK(result == expected);
		CHECK(result.first == expected.first);
		CHECK(result.second == expected.second);
	}
}
