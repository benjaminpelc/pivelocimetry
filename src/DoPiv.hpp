/* Class DoPiv
 *
 * Main engine of the program, do the actual PIV 
 * */

#ifndef BPPIV_DO_PIV_H
#define BPPIV_DO_PIV_H

#include <fstream>
#include <algorithm>
#include <iomanip>
#include <thread>



#include "PivOptions.hpp"
#include "IntMap.hpp"
#include "Grid.hpp"
#include "XCorr2.hpp"
#include "PivPoint.hpp"
#include "SubPix.hpp"
#include "find_peaks.hpp"
#include "../lib/Mat2.hpp"

#include "../lib/alias.hpp"

namespace PivEng {

class DoPiv
{
	public:
		typedef std::vector<PivPoint> PivPointVec;

		DoPiv(PivOptions& options, const IntMap::Pair& imPair, Grid& g);
		void print();
		void write(const std::string filename);
		PivPointVec& pointsVector();

		~DoPiv();

	private:
		int m_num_points;
		std::vector<Mat2<double>> m_ccfs;
		PivPointVec m_points;
};

}
#endif
