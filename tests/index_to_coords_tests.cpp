#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/utils.hpp"

using namespace PivEng;

TEST_CASE("subsrcipts_to_index") {

  SECTION("index should equal 3") { CHECK(subsrcipts_to_index(1, 1, 2) == 3); }
}
