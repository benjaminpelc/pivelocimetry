// Disp.hpp
// Displacement vector class header file. Contains u and v components
// of velocity and a bool flag indicating the validity.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_PIV_ENGINE_DISPLACEMENT_H
#define BPPIV_PIV_ENGINE_DISPLACEMENT_H

#include <vector>
#include <cmath>

namespace PivEng {

class Disp {
public:
  using DispVec = std::vector<Disp>;

  Disp();
  Disp(const double u_in, const double v_in, const bool valid_in);
  ~Disp();

  // set_displacement
  // Set the displacement vector properties.
  //  -- u_in : u displacement component
  //  -- v_in : v displacement component
  //  -- valid_in : is the vector valid or not?
  void set_displacement(const double u_in, const double v_in,
                        const bool valid_in);

  // set_valid
  // Toggle the validity of the displacement vector
  //  -- valid_in : is the vector valid or not?
  void set_valid(const bool valid_in);

  // get_u
  // Return the u displacement component
  double get_u() const;

  // get_v
  // Return the v displacement component
  double get_v() const;

  // get_magnitude
  // Return the displacement vectory magnitude.
  double get_magnitude();

  // is_valid
  // Return the validity of the vector
  bool is_valid() const;

private:
  // u, v
  // Displacement vector components in the x and y directions. Default
  // to 0 if no arguments are passed to the constructor.
  double u{0.0}, v{0.0};

  // magnitude
  // Resultant displacement magnitude
  double magnitude;

  // valid
  // Is the current displacement vector valid? Default to false.
  bool valid{false};

  // magnitude_available
  // The madnitude is not calculated until it is required and then it is
  // cashed. magnitude_available tells us if it has been calculated yet.
  bool magnitude_available{false};
};
}

#endif
