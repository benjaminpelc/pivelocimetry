#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../lib/bpu.hpp"

using namespace bpu;

TEST_CASE("BPU::mean", "Integers") {

  auto a = 3.0;
  auto b = 3.6;

  SECTION("should equal 3") { CHECK(cast_round_if_integral<int>(a) == 3); }

  SECTION("should == 3.0") { CHECK(cast_round_if_integral<double>(a) == 3.0); }

  SECTION("should == 4") {
    CHECK(cast_round_if_integral<int>(b) == 4);
    ;
  }

  SECTION("should == 3.6") { CHECK(cast_round_if_integral<double>(b) == 3.6); }

  SECTION("Takes rvalues") {
    CHECK(cast_round_if_integral<double>(4.7) == 4.7);
    CHECK(cast_round_if_integral<int>(4.7) == 5);
    CHECK(cast_round_if_integral<int>(5.3) == 5);
  }
}
