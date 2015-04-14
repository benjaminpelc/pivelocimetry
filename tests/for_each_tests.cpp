#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/bpu.hpp"
// #include <algorithm>
using namespace bpu;

TEST_CASE("Bpu::for_each") {

  std::vector<int> xs{1, 2, 3, 4, 5, 6, 7};
  auto sum = 0;
  auto p = [&sum](auto &x) { return sum += x; };
  auto neg = [](auto &x) { x = -x; };

  SECTION("sum should equal 28") {
    for_each(xs, p);
    CHECK(sum == 28);
  }

  SECTION("element should have changed sign") {
    for_each(xs, neg);
    CHECK(xs.front() == -1);
    CHECK(xs.back() == -7);
  }
}
