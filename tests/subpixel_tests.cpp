/*
 * compile with:
 * g++ -std=c++14 -o grid_test grid_tests.cpp ../src/grid.h ../src/pivoptions.cpp ../src/int_map.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include "../tests/catch.hpp"

#include <string>
#include <memory>
#include "../src/subpix.h"

TEST_CASE( "SubPixel: gauss3"){

	SECTION( "Symmetrical case" ) {
		double a = 0.5, b = 1.0, c = 0.5;
		double correct = 0.0;		

    	CHECK(SubPixel::gauss3(a, b, c) == 0.0);
    }
    /*
	 * return  ( log(a) - log(c)    ) /
	 * 		(
	 * 			 2*log(a) - 4*log(b) + 2*log(c)
	 * 		); 
     */
	
	/* 512 x 512 test image, 16 x 16 pixel windows with 8 pixel overlap */
}
