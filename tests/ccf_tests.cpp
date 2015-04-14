#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/Mat2.hpp"
// #include <algorithm>

TEST_CASE("Test CCF", "Initialisation") {

  Mat2<double> c(17, 17);

  SECTION("All elements should be equal to -1.0") {
    std::for_each(c.begin(), c.end(), [](auto el) { CHECK(el == -1.0); });
  }
}

TEST_CASE("Set elements", "Use setElem to set correlation values") {
  Mat2<double> c(17, 17);

  c.setElem(2, 4, 0.998);
  c.setElem(5, 14, 0.810);
  c.setElem(13, 9, 0.321);

  SECTION("Set some peaks and check values") {
    REQUIRE(c.at(2, 4) == 0.998);
    REQUIRE(c.at(5, 14) == 0.810);
    REQUIRE(c.at(13, 9) == 0.321);
  }
}

TEST_CASE("CCF::offsetX, CCF::offsetY") {

  SECTION("Offset should = 4") {
    Mat2<double> m_a(9, 9);
    CHECK(m_a.offsetX() == 4);
  }

  SECTION("Offset should = 4") {
    Mat2<double> m_a(10, 10);
    CHECK(m_a.offsetX() == 4);
  }
}

// TEST_CASE( "Peak finder", "Find peaks")
// {
// 	CCF c(17, 17);
// 	Peak::PeaksVec ps(3);
//
// 	c.setElem(2, 4, 0.998);
// 	c.setElem(2, 3, 0.230);
// 	c.setElem(2, 5, 0.136);
// 	c.setElem(1, 4, 0.0972);
// 	c.setElem(3, 4, 0.082);
//
// 	c.setElem(5, 14, 0.810);
// 	c.setElem(13, 9, 0.321);
//
// 	c.findPeaks(ps, 7);
//
// 	Peak p1 = ps[0];
// 	Peak p2 = ps[1];
// 	Peak p3 = ps[2];
//
// SECTION( "First peak should be 0.998" ) {
// 	CHECK(p1.get_value() == 0.998 );
// }
//
// SECTION( "First peak should be 0.810" ) {
// 	CHECK(p2.get_value() == 0.810 );
// }
//
// SECTION( "First peak should be 0.321" ) {
// 	CHECK(p3.get_value() == 0.321 );
// }
//
//
// SECTION( "First peak should have coords (i, j) = (4, 2)" ) {
// 	CHECK(p1.get_i() == 4);
// 	CHECK(p1.get_j() == 2);
// }
//
// SECTION( "Second peak should have coords (i, j) = (14, 5)" ) {
// 	CHECK(p2.get_i() == 14);
// 	CHECK(p2.get_j() == 5);
// }
//
// SECTION( "Third peak should have coords (i, j) = (9, 13)" ) {
// 	CHECK(p3.get_i() == 9);
// 	CHECK(p3.get_j() == 13);
// }
// }
