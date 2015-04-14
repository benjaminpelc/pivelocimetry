#include <iostream>
#include "../lib/Mat2.hpp"

Mat2<double> foo() {
  auto xz = Mat2<double>(2678, 2776, 2.13);
  return xz;
}

int main(int argc, char **argv) {
  auto m = Mat2<double>(3, 5, 3.1415);

  /* Test subscript notation */
  auto firstElem = m[0];
  std::cout << "First elem should be 3.1415: " << firstElem << std::endl;

  m[3] = 1.01;
  std::cout << "m[3] should equal 1.01: " << m[3] << std::endl;

  if (m.size() != 15)
    std::cout << "m.size() should equal 15" << std::endl;

  std::cout << m.at(1) << std::endl;

  auto mCopy = Mat2<double>(m);
  auto zz = Mat2<double>(12, 33, 1.10);

  std::cout << "mCopy == m: " << (mCopy == m) << std::endl;
  std::cout << "mCopy == zz: " << (mCopy == zz) << std::endl;

  std::cout << "mCopy[3] should equal 1.01: " << mCopy[3] << std::endl;

  m[4] = 9.99;
  std::cout << "mCopy should not == m: " << (mCopy == m) << std::endl;

  std::cout << "m[4] should = 9.99: " << m[4] << std::endl;
  std::cout << "mCopy[4] should = 3.1415: " << mCopy[4] << std::endl;

  mCopy = m;

  std::cout << "mCopy[4] should equal 9.99: " << mCopy[4] << std::endl;

  auto z = Mat2<double>(3, 3, 0.1);

  std::cout << "z != m: " << (z != m) << std::endl;
  std::cout << "mCopy != m: " << (mCopy != m) << std::endl;
  std::cout << "m != mCopy: " << (m != mCopy) << std::endl;

  z = std::move(m);

  // std::cout << "m[4] should not be a thing: " << m[4] << std::endl;
  std::cout << "z[4] should equal 9.99: " << z[4] << std::endl;

  auto cv = std::move(z);
  std::cout << cv[4] << std::endl;

  return 0;
}
