// Peak.hpp
// Struct Peak
// Container struct for a correlation function peak,
// Contains two integer correlation function coordinates and
// the correlation function value at those coordinates.
// Contains a validity flag which can be switched on/off as
// appropriate.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIB_PIV_ENGINE_PEAK_H
#define BPPIB_PIV_ENGINE_PEAK_H

#include <vector>

namespace PivEng {

struct Peak {
  typedef std::vector<Peak> PeaksVec;

  // Default constructor
  // Set peak coordinates, value and validity to invalid values.
  Peak() : val(-1.0), i(-1), j(-1), valid(false){};

  // Constructor with specified peak values
  //  -- ic : coordinate of peak in the x direction
  //  -- jc : coordinate of peak in the y direction
  //  -- v : value of the correlation function at the peak location
  //  -- torf : is the peak valid or not? True of false.
  Peak(const int ic, const int jc, const double v, const bool torf)
      : val(v), i(ic), j(jc), valid(torf){};
  ~Peak(){};

  // setPeak
  // set the peak value, coordinates and validity.
  //  -- ic : coordinate of peak in the x direction
  //  -- jc : coordinate of peak in the y direction
  //  -- v : value of the correlation function at the peak location
  //  -- torf : is the peak valid or not? True of false.
  void setPeak(const int ic, const int jc, const double v, const bool torf) {
    val = v;
    i = ic;
    j = jc;
    valid = torf;
  };

  // set_value
  // Set the peak value (the value of the correlation function at the peak
  // location).
  //  -- peak_value : value to set the peak value to
  void set_value(const double peak_value) {
    val = peak_value;
  };

  // get_value
  // Return the value of the peak.
  double get_value() const {
    return val;
  };

  // get_i
  // Return the peak i coordinate.
  int get_i() const {
    return i;
  };

  // get_j
  // Return the peak j coordinate.
  int get_j() const {
    return j;
  };

  // val
  // Contains the peak magnitude
  double val;

  // i, j
  // Integer coordinates in the correlation plane for peak location.
  int i, j;

  // valid
  // Is the peak valid or not (i.e in range or above a pre-defined threshold).
  bool valid;
};
}
#endif
