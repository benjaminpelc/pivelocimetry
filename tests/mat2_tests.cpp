#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Mat2.h"

TEST_CASE( "Matrix2 Double Init", "Initiate Matrix2<double>(3,5,3.2)"){
	
	Mat2<double> m(3, 5, 3.2);	

	SECTION( "Checking dimensions. Size will be equal to 15") {
		CHECK(m.size() == 15);
		CHECK(m.rows() == 3);
		CHECK(m.cols() == 5);
	}

	CHECK( m.getElem(7) ==3.2); 
	CHECK( m.getElem(1, 2) ==3.2); 
	
	int counter = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 5; i++) {
			m.setElem(j, i, counter++);
		}
	}

	SECTION( "Check get index") {
		CHECK(m.getIndex(1, 3) == 8 );
		CHECK(m.getIndex(2, 3) == 13 );
	}
	
	SECTION( "All elements should be equal to index minus 1" ) {
		counter = 0;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 5; i++) {
				REQUIRE(m.getElem(j,i) == counter++);
			}
		}
	}

	SECTION( "All elements should have value equal to index") {
		counter = 0;
		for(auto &n : m) { CHECK(n == counter++); }
	}
	
}
