#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/ccf.h"

TEST_CASE( "Test CCF", "Initialisation"){
	
	CCF c(9, 9);	
	
	SECTION( "All elements should be equal to -1.0" ) {
		CHECK(c.getElem(1) == -1.0);
	}

	SECTION( "Set some peaks and check values" ) {
		c.setElem(2, 4, 0.998);
		c.setElem(4, 3, 0.810);
		c.setElem(7, 3, 0.321);

		REQUIRE(c.getElem(2, 4) == 0.998);
		REQUIRE(c.getElem(4, 3) == 0.810);
		REQUIRE(c.getElem(7, 3) == 0.321);
	}
}
