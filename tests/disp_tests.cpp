#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Disp.hpp"

using namespace PivEng;

TEST_CASE( "Disp::Disp", "Default" ) {
	
	auto d = Disp();

	SECTION( "u should equal 0" ) {
		CHECK(d.get_u() == 0);
	}

	SECTION( "v should equal 0" ) {
		CHECK(d.get_v() == 0);
	}
	
	SECTION( "valid should be flase" ) {
		CHECK(d.is_valid() == false);
	}
}

TEST_CASE( "Disp::Disp with args", "With args" ) {
	
	auto d = Disp(3.1, -0.02, true);

	SECTION( "u should equal 3.1" ) {
		CHECK(d.get_u() == 3.1);
	}

	SECTION( "v should equal -0.02" ) {
		CHECK(d.get_v() == -0.02);
	}
	
	SECTION( "valid should be flase" ) {
		CHECK(d.is_valid() == true);
	}
}

TEST_CASE( "Disp::get_magnitude()") {
	auto d = Disp(3.1, -0.02, true);
	auto expected = sqrt(3.1 * 3.1 + (-0.02 * -0.02));
	SECTION( "Magnitude should equal " ) {
		CHECK(d.get_magnitude() == expected);
	}
	
}
