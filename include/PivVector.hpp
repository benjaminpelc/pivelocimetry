// PivVector.hpp
// Header forPivVector class. Contains a Disp vector as well as
// the spatial coordinates.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_VECTOR_2D_2C_H
#define BPPIV_VECTOR_2D_2C_H

#include <cmath>
#include "Disp.hpp"

namespace PivEng {

class PivVector {
public:
  PivVector();
  PivVector(const double x0, const double y0, const double u0, const double v0);
  PivVector(const double x0, const double y0, const Disp& disp_in);
  ~PivVector();

  double get_x() const;
  double get_y() const;
  double get_u() const;
  double get_v() const;

  double get_magnitude();

private:
  Disp velocities;
  double x, y;
};
}
#endif
