#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/bpu.hpp"
// #include <algorithm>
using namespace bpu;

TEST_CASE("Bpu::collect", "Initialisation") {

  std::vector<int> xs{1, 2, 3, 4, 5, 6, 7};
  auto odd_xs =
      collect(xs.begin(), xs.end(), [](auto &x) { return x % 2 != 0; });

  SECTION("Length of odd_xs should be 4") { CHECK(odd_xs.size() == 4); }

  SECTION("Second element should be 3") { CHECK(odd_xs[1] == 3); }

  SECTION("Second element should still be 3") {
    xs[2] = 4;
    CHECK(odd_xs[1] == 3);
  }
}
