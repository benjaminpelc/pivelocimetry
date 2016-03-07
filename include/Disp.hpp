/* Class: Disp
 * Namespace: PivEng
 *
 * Author: B. Pelc
 * Date: 22/03/2015
 */

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

  void set_displacement(const double u_in, const double v_in,
                        const bool valid_in);
  void set_valid(bool valid_in);

  double get_u() const;
  double get_v() const;
  double get_magnitude();
  bool is_valid() const;

private:
  double u{0.0}, v{0.0};
  double magnitude;
  bool valid{false};
  bool magnitude_available{false};
};
}

#endif
