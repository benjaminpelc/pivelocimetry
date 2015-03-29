/* Class DoPiv
 *
 * Main engine of the program, do the actual PIV 
 * */

#ifndef BPPIV_DO_PIV_H
#define BPPIV_DO_PIV_H

#include <fstream>
#include <algorithm>
#include <iomanip>

#include "PivOptions.hpp"
#include "IntMap.hpp"
#include "Grid.hpp"
#include "XCorr2.hpp"
#include "PivPoint.hpp"
#include "SubPix.hpp"

namespace PivEng {

class DoPiv
{
	public:
		typedef std::vector<PivPoint> PivPointVec;

		DoPiv(PivOptions& options, IntMap::Pair& imPair, Grid& g);
		void print();
		void write(const std::string filename);
		PivPointVec& pointsVector();


		~DoPiv();

	private:
		void doPivPoint(PivPoint& pivPoint, Grid::CoordPair& coordPair, IntMap::Pair& images);
		int m_numX,
			m_numY;
		PivPointVec m_points;
};

}
#endif
