#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/ccf.h"

TEST_CASE( "Test CCF", "Initialisation"){
	
	CCF c(9, 9);	
	
	SECTION( "All elements should be equal to -1.0" ) {
		for (int j = 0; j < 9; j++) {
			for (int i = 0; i < 9; i++) {
				REQUIRE(c.get_elementAt(j,i) == -1.0);
			}
		}
	}

	SECTION( "Set some peaks and check values" ) {
		c.set_elem(2, 4, 0.998);
		c.set_elem(4, 3, 0.810);
		c.set_elem(7, 3, 0.321);

		REQUIRE(c.get_elementAt(2, 4) == 0.998);
		REQUIRE(c.get_elementAt(4, 3) == 0.810);
		REQUIRE(c.get_elementAt(7, 3) == 0.321);
	}
}
