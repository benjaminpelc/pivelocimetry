/*
 * compile with:
 * g++ -std=c++14 -o grid_test grid_tests.cpp ../src/grid.h ../src/pivoptions.cpp ../src/int_map.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include "../tests/catch.hpp"

#include <string>
#include <memory>
#include "../src/int_map.h"
#include "../src/pivoptions.h"
#include "../src/grid.h"

TEST_CASE( "Grid: Square Image"){
	
	/* 512 x 512 test image, 16 x 16 pixel windows with 8 pixel overlap */

	PivOptions::Uptr opt(new PivOptions());
	IntMap::Uptr im(new IntMap(512, 512));

	Grid g(opt, im);

	SECTION( "Number of x grid points should equal 63") {
		CHECK(g.numX() == 63);
	}

	SECTION( "Number of y grid points should equal 63") {
		CHECK(g.numY() == 63);
	}

	SECTION( "Length of x coordinate vector should equal 63" ) {
		CHECK(g.xVector().size() == 63);
	}
	
	SECTION( "Length of y coordinate vector should equal 63" ) {
		CHECK(g.yVector().size() == 63);
	}
	
	SECTION( "Total grid points should equal 3969" ) {
		CHECK(g.numPoints() == 3969);
	}
	
	auto coordsVec = g.coordsVec();

	SECTION( "Coord pair vector should have size 3969" ) {
		CHECK(coordsVec.size() == 3969);
	}
	
	SECTION( "First coords should be (7, 7)" ) {
		CHECK(coordsVec[0].first == 7);
		CHECK(coordsVec[0].second == 7);
	}
	
	SECTION( "Point 2364 should be (7, 7)" ) {
		CHECK(coordsVec[2364].first == 271);
		CHECK(coordsVec[2364].second == 303);
	}

	SECTION( "Should be ordered by row then column (x1, y1), (x2, y1)..." ) {
		CHECK(coordsVec[0].second == coordsVec[1].second);
	}
}

TEST_CASE( "Grid: Rectangular Image"){
	
	/* 512 x 256 test image, 16 x 16 pixel windows with 8 pixel overlap */

	PivOptions::Uptr opt(new PivOptions());
	IntMap::Uptr im(new IntMap(512, 256));

	Grid g(opt, im);

	SECTION( "Number of x grid points should equal 31") {
		CHECK(g.numX() == 31);
	}

	SECTION( "Number of y grid points should equal 63") {
		CHECK(g.numY() == 63);
	}

	SECTION( "Length of x coordinate vector should equal 63" ) {
		CHECK(g.xVector().size() == 31);
	}
	
	SECTION( "Length of y coordinate vector should equal 63" ) {
		CHECK(g.yVector().size() == 63);
	}
	
	SECTION( "Total grid points should equal 1956" ) {
		CHECK(g.numPoints() == 1953);
	}
	
	auto coordsVec = g.coordsVec();

	SECTION( "Coord pair vector should have size 1953" ) {
		CHECK(coordsVec.size() == 1953);
	}
	
	SECTION( "First coords should be (7, 7)" ) {
		CHECK(coordsVec[0].first == 7);
		CHECK(coordsVec[0].second == 7);
	}
	
	SECTION( "Point 273  should be (7, 7)" ) {
		CHECK(coordsVec[273].first == 207);
		CHECK(coordsVec[273].second == 71);
	}
	

}
