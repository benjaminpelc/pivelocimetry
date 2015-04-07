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

TEST_CASE( "Disp::set_displacement" ) {
	auto d = Disp(1.0, 2.0, true);

	SECTION( "Values should be same as constructor" ) {
		CHECK(d.get_u() == 1.0);
		CHECK(d.get_v() == 2.0);
	}

	SECTION( "Values should equal new values" ) {
		d.set_displacement(3.0, 4.0, true);
		CHECK(d.get_u() == 3.0);
		CHECK(d.get_v() == 4.0);
	}
}

TEST_CASE( "Disp::get_magnitude()") {
	auto d = Disp(3.1, -0.02, true);
	auto expected = sqrt(3.1 * 3.1 + (-0.02 * -0.02));
	SECTION( "Magnitude should equal " ) {
		CHECK(d.get_magnitude() == expected);
	}
	
}

TEST_CASE( "Copy constructor" ) {
	auto d = Disp(1.0, 2.0, true);
	auto b(d);

	SECTION( "b.get_u should equal 1.0" ) {
		CHECK(b.get_u() == 1.0);
	}
	
	SECTION( "b.get_v should equal 2.0" ) {
		CHECK(b.get_v() == 2.0);
	}

	SECTION( "d should remain unchanged" ) {
		b.set_displacement(3.0, 3.0, false);
		CHECK(d.get_u() == 1.0);
		CHECK(d.get_v() == 2.0);
		CHECK(b.get_u() == 3.0);
		CHECK(b.get_v() == 3.0);
	}
}
