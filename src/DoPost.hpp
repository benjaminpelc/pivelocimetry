#ifndef BPPIV_DO_POST_PROCESSING_H
#define BPPIV_DO_POST_PROCESSING_H

#include "PivPoint.hpp"
#include "../lib/bpu.hpp"
#include <algorithm>

namespace PivPost {
class DoPost
{
	public:
		/* Constructor 
		 * Input: Vector of PivPoints by reference 
		 * 		  Number of columns
		 */
		DoPost(std::vector<PivEng::PivPoint>& pointsVector, int gridCols);
		
		/* Destructor */
		~DoPost();

	private:

};
}
#endif
