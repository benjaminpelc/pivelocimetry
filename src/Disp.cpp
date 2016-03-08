// Disp.cpp
// Implementation of the displacement vector class. Contains u and v components
// of velocity and a bool flag indicating the validity.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "Disp.hpp"

namespace PivEng {
Disp::Disp() {}

Disp::Disp(const double u_in, const double v_in, const bool valid_in)
    : u(u_in), v(v_in), valid(valid_in) {}

Disp::~Disp() {}

void Disp::set_displacement(const double u_in, const double v_in,
                            const bool valid_in) {
  u = u_in;
  v = v_in;
  valid = valid_in;
}

void Disp::set_valid(bool bool valid_in) {
  valid = valid_in;
}

double Disp::get_u() const { return u; }
double Disp::get_v() const { return v; }

double Disp::get_magnitude() {
  if (magnitude_available) {
    return magnitude;
  } else {
    magnitude = sqrt(u * u + v * v);
    magnitude_available = true;
    return magnitude;
  }
}

bool Disp::is_valid() const { return valid; }
}
