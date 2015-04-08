#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/bpu.hpp"
// #include <algorithm>
using namespace bpu;

TEST_CASE( "Bpu::collect_unique"){
	
	std::vector<int> xs{1, 7, 2, 3, 1, 3, 5, 1, 5, 7, 2, 1, 5, 6, 7};
	auto uxs = collect_unique(xs.begin(), xs.end());
	
	SECTION( "length of uxs should be 7" ) {
		CHECK(uxs.size() == 6);
	}
	
	SECTION( "first element should be 1" ) {
		CHECK(uxs.front() == 1);
	}
	
	SECTION( "last element should be 7" ) {
		CHECK(uxs.back() == 7);
	}
	
}

TEST_CASE( "Bpu::collect_unique with pred"){
	
	std::vector<int> xs{1, 2, 3, 1, 2, 4, -2};
	auto sq = [](auto x) -> double { return sqrt(x); };
	auto db = [](auto x) { return x * x; };
	auto uxs1 = collect_unique(xs.begin(), xs.end(), sq);
	auto uxs2 = collect_unique(xs.begin(), xs.end(), db);
	auto uxs3 = collect_unique(xs, db);
	std::vector<int> ex{1, 4, 9, 16};

	SECTION( "length uxs1 should equal 4" ) {
		CHECK(uxs1.size() == 5);
	}

	SECTION( "length uxs1 should equal 4" ) {
		CHECK(uxs2.size() == 4);
	}
	
	SECTION( "length uxs3 should equal 4" ) {
		CHECK(uxs3.size() == 4);
	}

	SECTION( "uxs3 should equal expected" ) {
		CHECK(uxs3 == ex);
	}
	
}
