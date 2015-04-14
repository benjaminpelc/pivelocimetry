#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../lib/Mat2.hpp"

TEST_CASE("Matrix2 Double Init", "Initiate Matrix2<double>(3,5,3.2)") {

  Mat2<double> m(3, 5, 3.2);

  SECTION("Checking dimensions. Size will be equal to 15") {
    CHECK(m.size() == 15);
    CHECK(m.rows() == 3);
    CHECK(m.cols() == 5);
  }

  CHECK(m.at(7) == 3.2);
  CHECK(m.at(1, 2) == 3.2);

  int counter = 0;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 5; i++) {
      m.setElem(j, i, counter++);
    }
  }

  SECTION("Check get index") {
    CHECK(m.getIndex(1, 3) == 8);
    CHECK(m.getIndex(2, 3) == 13);
  }

  SECTION("All elements should be equal to index minus 1") {
    counter = 0;
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 5; i++) {
        REQUIRE(m.at(j, i) == counter++);
      }
    }
  }

  SECTION("All elements should have value equal to index") {
    counter = 0;
    for (auto &n : m) {
      CHECK(n == counter++);
    }
  }
}

TEST_CASE("Mat2: Equality") {
  auto m_a = Mat2<int>(2, 3, 4);
  auto m_b = Mat2<int>(2, 3, 4);
  auto m_c = m_a;

  SECTION("m_a should equal m_b") { CHECK(m_a == m_b); }

  SECTION("m_a should equal m_c") {
    m_c[0] = 9;
    CHECK(m_a != m_c);
  }
}

TEST_CASE("Mat2::sum") {
  auto m_a = Mat2<int>(2, 2, 3);
  SECTION("sum should equal 12") { CHECK(m_a.sum() == 12); }

  auto m_b = Mat2<float>(3, 2, 3.1415);
  SECTION("sum should equal 18.849") { CHECK(m_b.sum() == 18.849f); }
}

// TEST_CASE ( "Mat2:: < ") {
// 	auto m_a = Mat2<int>(2,2,3);
// 	auto m_b = Mat2<int>(2,2,4);
// 		m_b[2] = 1;
// 	SECTION( "m_a should be less than m_b" ) {
// 		CHECK(m_a < m_b);
// 	}
// 	SECTION( "m_a should not be less than m_b" ) {
// 		m_b.setElem(1,1, 1);
// 		CHECK((m_a < m_b));
// 	}
// }
