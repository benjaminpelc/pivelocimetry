#ifndef BPPIV_DO_POST_PROCESSING_H
#define BPPIV_DO_POST_PROCESSING_H

#include "PivPoint.hpp"
#include "utils.hpp"

#include "../lib/bpu.hpp"
#include <algorithm>

namespace PivEng {

struct Limits {

  Limits() : i_min{0}, i_max{0}, j_min{0}, j_max{0} {};
  Limits(const int iin, const int iax, const int jin, const int jax)
      : i_min{iin}, i_max{iax}, j_min{jin}, j_max{jax} {};
  ~Limits(){};

  int num_indexes() const { return (i_max - i_min + 1) * (j_max - j_min + 1); };

  int i_min, i_max, j_min, j_max;
};

struct NeighboursInfo {
  double neighs_median{0.0}, fluct_0{0.0}, median_residual{0.0};
  double test_value() const {
    return std::abs(fluct_0 / (median_residual + 0.1));
  };
};

class DoPost {
public:
  /* Constructor
   * Input: Vector of PivPoints by reference
   * 		  Number of columns
   */
  DoPost(std::vector<PivEng::PivPoint> &pointsVector, int gridCols,
         const double threshold = 2.0);
  ~DoPost();

private:
  void interpolate_if_no_valid_disp(const NeighboursInfo &u,
                                    const NeighboursInfo &v,
                                    std::vector<Disp> &dvs);
  double get_median_residual(std::vector<double> &neighbours,
                             const double neighbours_median);

  bool above_thresh(const double element_residual,
                    const double neighbours_median_residual,
                    const double thresh);
  double test_value(const NeighboursInfo &neigh_info);

  std::vector<Disp *>
  get_primary_disp_ptrs(std::vector<PivEng::PivPoint> &pointsVector);
  void update_limits(Limits &lims, const int i, const int j, const int rad,
                     const int grid_colums, const int grid_rows);

  void get_neighbours(const int i, const int j, const Limits &lims,
                      const int grid_cols,
                      const std::vector<Disp *> &primary_disps,
                      std::vector<double> &u_neighbours,
                      std::vector<double> &v_neighbours);

  NeighboursInfo get_neighbours_info(std::vector<double> neighbours,
                                     const double current_disp);

  void mark_invalid_check_lower_peaks(Disp *current_disp, NeighboursInfo &u,
                                      NeighboursInfo &v, std::vector<Disp> &dvs,
                                      const double threshold);
};
}
#endif
