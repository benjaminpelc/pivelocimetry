#include "DoPost.hpp"

namespace PivPost {

DoPost::DoPost(std::vector<PivEng::PivPoint>& pointsVector, int gridCols)
{
	std::cout << gridCols << std::endl;

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
	int rad = 1;
	valid[11 * gridCols + 3] = false;

	auto ctr = 0;
	for(bool v : valid) {
		if(!v) {
			std::cout << "Invalid at (" << ctr % gridCols << ", " << ctr / gridCols << ")" << std::endl;
		}
		ctr++;
	}


	int gridRows = pointsVector.size() / gridCols;
	int idx = 0;

	auto neighs = [gridCols, gridRows, rad, &us, &valid](int j, int i) {

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
				std::cout << std::fixed << std::setprecision(3) << us[jj * gridCols + ii] << "\t";
				if ((ii != i || jj != j) && valid[jj * gridCols + ii] ) {
					*(neighsPtr++) = us[jj * gridCols + ii];
					nNeighs++;
				}
			}
			std::cout << std::endl;
		}
		neighs.resize(nNeighs);

		std::cout << nNeighs << std::endl;
		for (auto n : neighs)
			std::cout << n << ", ";
		std::cout << std::endl;
	};

	for(int j = 0; j < gridRows; j++) {
		for(int i = 0; i < gridCols; i++) {
			idx = j * gridCols + i;
			if (!valid[idx])
				neighs(j, i);
			if (idx == 0)
				neighs(j, i);
		}
	}


	
}

DoPost::~DoPost() {}

}
