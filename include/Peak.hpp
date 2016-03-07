/* Struct Peak
 *
 * Container class for a correlation function peak,
 * Contains two integer correlation function coordinates and
 * the  correlation function value at those coordinates.
 * Contains a validity flag which can be switched on/off as
 * appropriate */

#ifndef BPPIB_PIV_ENGINE_PEAK_H
#define BPPIB_PIV_ENGINE_PEAK_H

#include <vector>

namespace PivEng {

struct Peak {
  typedef std::vector<Peak> PeaksVec;

  Peak() : val(-1.0), i(-1), j(-1), valid(false){};
  Peak(const int ic, const int jc, const double v, const bool torf)
      : val(v), i(ic), j(jc), valid(torf){};
  ~Peak(){};

  void setPeak(const int ic, const int jc, const double v, const bool torf) {
    val = v;
    i = ic;
    j = jc;
    valid = torf;
  };

  double val;
  int i, j;
  bool valid;

  void set_value(const double peak_value) { val = peak_value; };

  double get_value() const { return val; };
  int get_i() const { return i; };
  int get_j() const { return j; };
};
}
#endif
