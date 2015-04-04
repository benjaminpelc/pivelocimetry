#include "DoPost.hpp"

namespace PivPost {

DoPost::DoPost(std::vector<PivEng::PivPoint>& pointsVector, int gridCols)
{
	// std::cout << gridCols << std::endl;

	auto us = std::vector<double>(pointsVector.size(), 0.0);
	auto valid = std::vector<bool>(pointsVector.size(), false);

	auto uBeginPtr = us.begin();
	auto uPtr = uBeginPtr;

	auto validBeginPtr = valid.begin();

	/* For each grid point get the first displacement values and validity */
	std::for_each(pointsVector.begin(), pointsVector.end(), [&uPtr, &validBeginPtr](auto& pivPoint){
				*(uPtr++) = pivPoint.dispsVec()[0].u;
				*(validBeginPtr++) = pivPoint.dispsVec()[0].valid;
			});

	/* Do with radius of just one for now */
	int rad{2}, nNeighs{0};

	auto ctr = 0;
	int gridRows = pointsVector.size() / gridCols;
	// int idx = 0;
	int idx_i{0}, idx_ii{0},i{0}, j{0}, ii{0}, jj{0},
		iMin{0}, iMax{0}, jMin{0}, jMax{0};

	/* Get linear index from coordinate pair using the number of rows
	 * in the grid */
	auto idx = [gridRows](const int i, const int j) {
		return j * gridRows + i;
	};

	/* Calculate normalised residual of velocity component under inspection,
	 * the central vector u0 */
	auto normalisedFluct = [](double u0, double medianRes) -> double {
		return std::abs(u0 / (medianRes + 0.1));
	};

	/* Is ccf displacement an actual value and is it not the element
	 * under inspection */
	auto validNeighbour = [&] () {
		return (ii != i || jj != j) && valid[idx_ii];
	};

	/* where to seach for neighbouring vectors */
	auto searchBounds = [&] () {
		iMin = std::max(0, i- rad);
		iMax = std::min(i + rad, gridCols - 1);
		jMin = std::max(0, j - rad);
		jMax = std::min(j + rad, gridRows - 1);
	};

	double* neighsPtr = nullptr;
	double medianRes{0.0}, median{0.0}, fluct0{0.0};

	for(j = 0; j < gridRows; j++) {
		for(i = 0; i < gridCols; i++) {
			idx_i = idx(i, j);
			searchBounds();

			nNeighs = (iMax - iMin + 1) * (jMax - jMin + 1) - 1;
			std::vector<double> neighs(nNeighs, 0.0);
			nNeighs = 0;
			neighsPtr = &neighs[0];

			for (jj = jMin; jj <= jMax; jj++) {
				for (ii = iMin; ii <= iMax; ii++) {
					// std::cout << std::fixed << std::setprecision(3) << us[jj * gridCols + ii] << "\t";
					idx_ii = idx(ii, jj);
					if (validNeighbour()) {
						*(neighsPtr++) = us[idx_ii];
						nNeighs++;
					}
				}
				// std::cout << std::endl;
			}
			neighs.resize(nNeighs);

			median = bpu::median<double>(neighs);
			fluct0 = (us[idx_i] - median);

			for (auto& n : neighs) {
				n = std::abs(n - median);
			}

			medianRes = bpu::median<double>(neighs);

			// double normFluct = std::abs(fluct0 / (medianRes + 0.1));
			// std::cout << "normFluct:\t" << normFluct << std::endl;
			// std::cout << "normalisedFluct:\t" << normalisedFluct(fluct0, medianRes) << std::endl;

			/* Check if the normalised fluctuation value exceeds the threshold
		 	 * value (typically 2.0). If so, flag the displacement as invalid.
		 	 * Itterate through displacements calculated from subsequant CCF peaks
		 	 * if this displacement is also out of range, flag as invalid */
			if (normalisedFluct(fluct0, medianRes) > 2.0) {

				valid[idx_i] = false;
				auto& dvs = pointsVector[ctr].dispsVec();
				dvs[0].valid = false;

				for_each(dvs.begin() + 1, dvs.end(),[&](auto& d) {
							if (normalisedFluct(d.u - median, medianRes) > 2)
								d.valid = false;
						});
			}
			// std::cout << "Normalised fluct: " << normFluct << std::endl;
			ctr++;
		}
	}

	// ctr = 0;
	// for(bool v : valid) {
	// 	if(!v) {
	// 		std::cout << "Invalid at (" << ctr % gridCols + 1 << ", " << ctr / gridCols + 1<< ")" << std::endl;
	// 	}
	// 	ctr++;
	// }


	
}

DoPost::~DoPost() {}

}
