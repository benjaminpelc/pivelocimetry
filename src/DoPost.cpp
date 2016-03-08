// DoPost.cpp
// Implementation of DoPost class. Do vector post-processing after DoPIV has
// calculated initial vectors. Remove spurious/outlying/non-calculated vectors
// and replace with interpolated ones.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "DoPost.hpp"

namespace PivEng {

DoPost::DoPost(std::vector<PivEng::PivPoint> &pointsVector, int grid_cols,
               const double threshold) {
  auto primary_disps = get_primary_disp_ptrs(pointsVector);

  int rad{2}, num_neighbours{0};

  const int grid_rows = pointsVector.size() / grid_cols;

  auto lims = Limits{};

  int idx_i{0};

  for (auto j = 0; j < grid_rows; j++) {
    for (auto i = 0; i < grid_cols; i++) {

      idx_i = PivEng::subsrcipts_to_index(i, j, grid_cols);
      auto current_disp = primary_disps[idx_i];
      update_limits(lims, i, j, rad, grid_cols, grid_rows);

      num_neighbours = lims.num_indexes() - 1;

      auto u_neighbours = std::vector<double>(num_neighbours, 0.0);
      auto v_neighbours = std::vector<double>(num_neighbours, 0.0);

      get_neighbours(i, j, lims, grid_cols, primary_disps, u_neighbours,
                     v_neighbours);

      auto u_info = get_neighbours_info(u_neighbours, current_disp->get_u());
      auto v_info = get_neighbours_info(v_neighbours, current_disp->get_v());

       // Check if the normalised fluctuation value exceeds the threshold
       // value (typically 2.0). If so, flag the displacement as invalid.
       // Itterate through displacements calculated from subsequant CCF peaks
       // if this displacement is also out of range, flag as invalid.
      if (u_info.test_value() > threshold || v_info.test_value() > threshold) {
        auto &dvs = pointsVector[idx_i].dispsVec();
        mark_invalid_check_lower_peaks(current_disp, u_info, v_info, dvs,
                                       threshold);
        interpolate_if_no_valid_disp(u_info, v_info, dvs);
      }
    }
  }
}

void DoPost::interpolate_if_no_valid_disp(const NeighboursInfo &u,
                                          const NeighboursInfo &v,
                                          std::vector<Disp> &dvs) {
  auto fv = std::find_if(dvs.begin(), dvs.end(),
                         [](const auto &dv) { return dv.is_valid(); });
  if (fv == dvs.end()) {
    dvs.push_back(Disp(u.neighs_median, v.neighs_median, true));
  }
}

void DoPost::mark_invalid_check_lower_peaks(Disp *current_disp,
                                            NeighboursInfo &u,
                                            NeighboursInfo &v,
                                            std::vector<Disp> &dvs,
                                            const double threshold) {
  current_disp->set_valid(false);

  for_each(dvs.begin() + 1, dvs.end(), [&](auto &d) {
    u.fluct_0 = d.get_u() - u.neighs_median;
    v.fluct_0 = d.get_v() - v.neighs_median;

    if (u.test_value() > threshold || v.test_value() > threshold)
      d.set_valid(false);
  });
}

double DoPost::get_median_residual(std::vector<double> &neighbours,
                                   const double neighbours_median) {
  for (auto &neighbour : neighbours) {
    neighbour = std::abs(neighbour - neighbours_median);
  }
  return bpu::median_modify_container<double>(neighbours);
}

// double DoPost::test_value(const double element_residual, const double
// neighbours_median_residual)
// {
// 	return std::abs(element_residual / (neighbours_median_residual + 0.1));
// }

double DoPost::test_value(const NeighboursInfo &neigh_info) {
  return std::abs(neigh_info.fluct_0 / (neigh_info.median_residual + 0.1));
}

std::vector<Disp *>
DoPost::get_primary_disp_ptrs(std::vector<PivEng::PivPoint> &points_vector) {
  auto primary_disps = std::vector<Disp *>(points_vector.size());
  auto primary_disps_itr = primary_disps.begin();
  std::for_each(points_vector.begin(), points_vector.end(),
                [&primary_disps_itr](auto &pivPoint) {
                  *(primary_disps_itr++) = &pivPoint.dispsVec()[0];
                });
  return primary_disps;
}

void DoPost::update_limits(Limits &lims, const int i, const int j,
                           const int rad, const int grid_cols,
                           const int grid_rows) {
  lims.i_min = std::max(0, i - rad);
  lims.i_max = std::min(i + rad, grid_cols - 1);
  lims.j_min = std::max(0, j - rad);
  lims.j_max = std::min(j + rad, grid_rows - 1);
}

void DoPost::get_neighbours(const int i, const int j, const Limits &lims,
                            const int grid_cols,
                            const std::vector<Disp *> &primary_disps,
                            std::vector<double> &u_neighbours,
                            std::vector<double> &v_neighbours) {
  auto u_neighbour_itr = u_neighbours.begin();
  auto v_neighbour_itr = v_neighbours.begin();

  auto ii = 0, jj = 0, idx_ii = 0;
  auto num_neighbours = 0;

  auto validNeighbour = [&]() {
    return (ii != i || jj != j) && primary_disps[idx_ii]->is_valid();
  };

  for (jj = lims.j_min; jj <= lims.j_max; jj++) {
    for (ii = lims.i_min; ii <= lims.i_max; ii++) {
      idx_ii = PivEng::subsrcipts_to_index(ii, jj, grid_cols);
      if (validNeighbour()) {
        *(u_neighbour_itr++) = primary_disps[idx_ii]->get_u();
        *(v_neighbour_itr++) = primary_disps[idx_ii]->get_v();
        num_neighbours++;
      }
    }
  }
  u_neighbours.resize(num_neighbours);
  v_neighbours.resize(num_neighbours);
}

NeighboursInfo DoPost::get_neighbours_info(std::vector<double> neighbours,
                                           const double current_disp) {
  auto stats = NeighboursInfo();

  stats.neighs_median = bpu::median<double>(neighbours);
  stats.fluct_0 = current_disp - stats.neighs_median;
  stats.median_residual = get_median_residual(neighbours, stats.neighs_median);

  return stats;
}

DoPost::~DoPost() {}
}
