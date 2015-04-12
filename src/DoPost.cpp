#include "DoPost.hpp"

namespace PivEng {

DoPost::DoPost(std::vector<PivEng::PivPoint>& pointsVector, int gridCols, const double threshold)
{
	auto primary_disps = get_primary_disp_ptrs(pointsVector);

	/* Do with radius of just one for now */
	int rad{2}, num_neighbours{0};

	const int gridRows = pointsVector.size() / gridCols;

	auto lims = Limits{};

	int idx_i{0}, i{0}, j{0};


	double u_median_residual{0.0}, u_neighs_median{0.0}, u_fluct_0{0.0};
	double v_median_residual{0.0}, v_neighs_median{0.0}, v_fluct_0{0.0};

	for(j = 0; j < gridRows; j++) {
		for(i = 0; i < gridCols; i++) {
			idx_i = PivEng::subsrcipts_to_index(i, j, gridRows);
			auto current_disp = primary_disps[idx_i];
			update_limits(lims, i, j, rad, gridCols, gridRows);

			num_neighbours = lims.num_indexes() - 1;

			auto u_neighbours = std::vector<double>(num_neighbours, 0.0);
			auto v_neighbours = std::vector<double>(num_neighbours, 0.0);

			get_neighbours(i, j, lims, gridRows, primary_disps, u_neighbours, v_neighbours);

			u_neighs_median = bpu::median<double>(u_neighbours);
			v_neighs_median = bpu::median<double>(v_neighbours);

			u_fluct_0 = current_disp->get_u() - u_neighs_median;
			v_fluct_0 = current_disp->get_v() - v_neighs_median;

			u_median_residual = get_median_residual(u_neighbours, u_neighs_median);
			v_median_residual = get_median_residual(v_neighbours, v_neighs_median);

			/* Check if the normalised fluctuation value exceeds the threshold
		 	 * value (typically 2.0). If so, flag the displacement as invalid.
		 	 * Itterate through displacements calculated from subsequant CCF peaks
		 	 * if this displacement is also out of range, flag as invalid */
			if (above_thresh(u_fluct_0, u_median_residual, threshold) ||
					above_thresh(v_fluct_0, v_median_residual, threshold) ) {

				current_disp->set_valid(false);
				auto& dvs = pointsVector[idx_i].dispsVec();
				dvs[0].set_valid(false);

				for_each(dvs.begin() + 1, dvs.end(),[&](auto& d) {
							if (above_thresh(d.get_u() - u_neighs_median, u_median_residual, threshold) || above_thresh(d.get_v() - v_neighs_median, v_median_residual, threshold) )
								d.set_valid(false);
						});
			}
			// std::cout << "Normalised fluct: " << normFluct << std::endl;
		}
	}

}

double DoPost::get_median_residual(std::vector<double>& neighbours, const double neighbours_median)
{
	for(auto& neighbour : neighbours) {
		neighbour = std::abs(neighbour - neighbours_median);
	}	
	return bpu::median_modify_container<double>(neighbours);
}

bool DoPost::above_thresh(const double element_residual, const double neighbours_median_residual, const double thresh)
{
	return std::abs(element_residual / (neighbours_median_residual + 0.1)) > thresh;
}

std::vector<Disp*> DoPost::get_primary_disp_ptrs(std::vector<PivEng::PivPoint>& points_vector)
{
	auto primary_disps = std::vector<Disp*>(points_vector.size());
	auto primary_disps_itr = primary_disps.begin();
	std::for_each(points_vector.begin(), points_vector.end(), [&primary_disps_itr](auto& pivPoint){
				*(primary_disps_itr++) = &pivPoint.dispsVec()[0];
			});
	return primary_disps;
}

void DoPost::update_limits(Limits& lims, const int i, const int j, const int rad, const int grid_cols, const int grid_rows)
{
		lims.i_min = std::max(0, i- rad);
		lims.i_max = std::min(i + rad, grid_cols - 1);
		lims.j_min = std::max(0, j - rad);
		lims.j_max = std::min(j + rad, grid_rows - 1);
}

void DoPost::get_neighbours(const int i, const int j, const Limits& lims, const int grid_rows, const std::vector<Disp*>& primary_disps, 
		std::vector<double>& u_neighbours,
		std::vector<double>& v_neighbours)
{
	auto u_neighbour_itr = u_neighbours.begin();
	auto v_neighbour_itr = v_neighbours.begin();

	auto ii = 0, jj = 0, idx_ii = 0;
	auto num_neighbours = 0;

	auto validNeighbour = [&] () {
		return (ii != i || jj != j) && primary_disps[idx_ii]->is_valid();
	};

	for (jj = lims.j_min; jj <= lims.j_max; jj++) {
		for (ii = lims.i_min; ii <= lims.i_max; ii++) {
			idx_ii = PivEng::subsrcipts_to_index(ii, jj, grid_rows);
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

DoPost::~DoPost() {}

}
