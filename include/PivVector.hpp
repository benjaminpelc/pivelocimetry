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

  // Default constructor
  // Values default to zero when no arguments are provided.
  PivVector();

  // Constructor with individual coordinate and displacement arguments
  //  -- x0, y0 : vector grid coordinates.
  //  -- u0, v0 : orthogonal vector displacement components
  PivVector(const double x0, const double y0, const double u0, const double v0);

  // Constructor with individual coordinates and a Disp object as the
  // displacement argument.
  //  -- x0, y0 : vector grid coordinates.
  //  -- disp_in : displacement vector.
  PivVector(const double x0, const double y0, const Disp& disp_in);
  ~PivVector();

  // Getters
  // Self-explanatory. Return each of the vector spatial coordinates and
  // displacement vector components and the displacement vector magnitude.
  double get_x() const;
  double get_y() const;
  double get_u() const;
  double get_v() const;
  double get_magnitude();

private:
  // Vector displacement 
  Disp velocities;

  // Vector spatial coordinates
  double x, y;
};
}
#endif
