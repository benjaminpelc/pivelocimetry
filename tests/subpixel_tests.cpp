/*
 * compile with:
 * g++ -std=c++14 -o grid_test grid_tests.cpp ../src/grid.h
 *../src/pivoptions.cpp ../src/int_map.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include "../tests/catch.hpp"

#include <string>
#include <memory>
#include "../src/SubPix.hpp"

using namespace PivEng;

TEST_CASE("SubPixel: gauss3") {

  SECTION("Symmetrical case") {
    double a = 0.5, b = 1.0, c = 0.5;
    double correct = 0.0;

    CHECK(gauss3(&a, &b, &c) == 0.0);
  }
}
