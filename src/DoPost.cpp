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

	/* For each grid point do something */
	std::for_each(pointsVector.begin(), pointsVector.end(), [&uPtr, &validBeginPtr](auto& pivPoint){
				*(uPtr++) = pivPoint.dispsVec()[0].u;
				*(validBeginPtr++) = pivPoint.dispsVec()[0].valid;
			});

	/* Do with radius of just one for now */
	int rad = 2;

	auto ctr = 0;
	int gridRows = pointsVector.size() / gridCols;
	// int idx = 0;
	auto normalisedFluct = [](double u0, double medianRes) -> double {
		return std::abs(u0 / (medianRes + 0.1));
	};

	auto neighs = [&](int j, int i) {

		int iMin = std::max(0, i- rad);//i - rad < 0 ? 0 : i - rad;
		int iMax = std::min(i + rad, gridCols - 1);// ? gridCols - 1 : i + rad; 

		int jMin = std::max(0, j - rad);// < 0 ? 0 : j - rad;
		int jMax = std::min(j + rad, gridRows - 1);// ? gridRows - 1 : j + rad; 

		int nNeighs = (iMax - iMin + 1) * (jMax - jMin + 1) - 1;
		std::vector<double> neighs(nNeighs, 0.0);
		nNeighs = 0;
		auto neighsPtr = neighs.begin();

		for (int jj = jMin; jj <= jMax; jj++) {
			for (int ii = iMin; ii <= iMax; ii++) {
				// std::cout << std::fixed << std::setprecision(3) << us[jj * gridCols + ii] << "\t";
				if ((ii != i || jj != j) && valid[jj * gridCols + ii] ) {
					*(neighsPtr++) = us[jj * gridCols + ii];
					nNeighs++;
				}
			}
			// std::cout << std::endl;
		}
		neighs.resize(nNeighs);

		auto median = bpu::median(neighs);
		auto fluct0 = (us[j * gridCols + i] - median);

		for (auto& n : neighs) {
			n = std::abs(n - median);
		}

		auto medianRes = bpu::median(neighs);


		double normFluct = std::abs(fluct0 / (medianRes + 0.1));
		std::cout << "normFluct:\t" << normFluct << std::endl;
		std::cout << "normalisedFluct:\t" << normalisedFluct(fluct0, medianRes) << std::endl;

		if (normalisedFluct(fluct0, medianRes) > 2.0) {

			valid[j * gridCols + i] = false;
			auto& dvs = pointsVector[ctr].dispsVec();
			dvs[0].valid = false;

			for_each(dvs.begin() + 1, dvs.end(),[&](auto& d) {
						if (normalisedFluct(d.u - median, medianRes) > 2)
							d.valid = false;
					});
		}

		// std::cout << "Normalised fluct: " << normFluct << std::endl;

	};

	for(int j = 0; j < gridRows; j++) {
		for(int i = 0; i < gridCols; i++) {
			// idx = j * gridCols + i;
			neighs(j, i);
			// if (idx == 0)
				// neighs(j, i);
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
