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
		void doPivPoint(PivPoint& pivPoint, CCF& c);
		// void doPivPoint(PivPoint& pivPoint, uint16_t* im1firstPix, uint16_t* im2firstPix);
		std::vector<CCF> m_ccfs;
		PivPointVec m_points;
		// int m_numX, m_numY;
};

}
#endif
