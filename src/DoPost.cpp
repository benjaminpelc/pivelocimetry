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
	// uint16_t rad = 1;
	auto ctr = 0;
	for(bool v : valid) {
		if(!v) {
			std::cout << "Invalid at (" << pointsVector[ctr].x() << ", " << pointsVector[ctr].y() << ")" << std::endl;
			std::cout << "Invalid at (" << ctr % gridCols << ", " << ctr / gridCols << ")" << std::endl;
		}
		ctr++;
	}


	
}

DoPost::~DoPost() {}

}
