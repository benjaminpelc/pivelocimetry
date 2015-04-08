#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/bpu.hpp"
using namespace bpu;

TEST_CASE( "Bpu::collect_unique"){
	
	auto p1 = std::make_pair(1, 11.432);
	auto p2 = std::make_pair(2, 3.1415);

	auto result = add_pairs(p1, p2);
	auto expected = std::make_pair(3, 11.432 + 3.1415);

	SECTION( "first should equal 3" ) {
		CHECK(result.first == 3);
	}
	SECTION( "second should equal 14.5735" ) {
		CHECK(result.second == 11.432 + 3.1415);
	}
	
	SECTION( "result should equal expected" ) {
		CHECK(result == expected);
	}
	
	
}
