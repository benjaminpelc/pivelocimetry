// PivVector.cpp
// Implementation of PivVector class. Contains a Disp vector as well as
// the spatial coordinates.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "PivVector.hpp"

namespace PivEng {
PivVector::PivVector() : velocities(), x(0.0), y(0.0) {}

PivVector::PivVector(const double x0, const double y0, const double u0,
                     const double v0)
    : velocities(u0, v0, true), x(x0), y(y0) {}

PivVector::PivVector(const double x0, const double y0, const Disp &disp_in)
    : velocities(disp_in), x(x0), y(y0) {}

double PivVector::get_x() const {
  return x;
}

double PivVector::get_y() const {
  return y;
}

double PivVector::get_u() const {
  return velocities.get_u();
}

double PivVector::get_v() const {
  return velocities.get_v();
}

double PivVector::get_magnitude() {
  return velocities.get_magnitude();
}

PivVector::~PivVector() {}
}
