#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/matrix2.h"

TEST_CASE( "Matrix2 Double Init", "Initiate Matrix2<double>(3,5,3.2)"){
	
	Matrix2<double> m(3, 5, 3.2);	
	
	SECTION( "All elements should be equal to 3.2" ) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 5; i++) {
				REQUIRE(m.get_elementAt(j,i) == 3.2);
				m.set_elem(j, i, (j+1)*(i+1));
			}
		}
	}

	SECTION( "The number of elements should be equal to 15" ) {
		REQUIRE( m.numElems() == 15 );
	}

	SECTION( "Element by index should equal correct value" ) {
		CHECK( m.getElem(0) == 1.0);
		CHECK( m.getElem(1) == 2.0);
		CHECK( m.getElem(7) == 6.0);
		CHECK( m.getElem(14) == 15.0);
	}

	
}
