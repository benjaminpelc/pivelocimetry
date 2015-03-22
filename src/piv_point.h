/* Class PIVPoint
 * 
 * Here we will store all the wonderful things that each PIV 
 * point must have. This is more a container class with setters 
 * and getters rather than any functionality of its own
 *
 * Currently, each point has:
 * 1) A CCF 
 * 2) A vector of peak objects 
 * 3) A vector of displacement objects 
 * 4) A pair of pixel coordinates */

#ifndef PIV_POINT_H
#define PIV_POINT_H

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>

#include "pivoptions.h"
#include "ccf.h"
#include "int_map.h"
#include "peak.h"
#include "displacement.h"

class PIVPoint
{
	public:
		PIVPoint(int xCoord, int yCoord, PivOptions& options);
		~PIVPoint();

		CCF* get_ccf();
		PivEng::Peak::PeaksVec& get_peaks();
		PivEng::Displacement::DispVec& get_displacementsVector();

		void set_xCoord(int x);
		void set_yCoord(int y);
		void set_coords(PivEng::Grid::CoordPair& coords);

		int x();
		int y();
		
		PivEng::Displacement& get_primaryDisplacement();
		void printToOfstream(std::ofstream& file);
		

	private:
		CCF::Sptr m_ccf;
		PivEng::Peak::PeaksVec m_peaksVector;
		PivEng::Displacement::DispVec m_dispsVec;
		int m_i, m_j;
};

PIVPoint::PIVPoint(int xCoord, int yCoord, PivOptions& options) :
	m_ccf(std::make_shared<CCF>(options.winHeight() + 1, options.winWidth() + 1)),
	m_peaksVector(options.numPeaks()),
	m_dispsVec(options.numPeaks()),
	m_i(xCoord),
	m_j(yCoord)
{}

CCF* PIVPoint::get_ccf()
{
	return m_ccf.get();
}

PivEng::Peak::PeaksVec& PIVPoint::get_peaks()
{
	return m_peaksVector;
}

PivEng::Displacement::DispVec& PIVPoint::get_displacementsVector()
{
	return m_dispsVec;
}


PivEng::Displacement& PIVPoint::get_primaryDisplacement()
{
	return m_dispsVec[0];
}

void PIVPoint::printToOfstream(std::ofstream& file)
{
	/* write the point to file in 
	 * x y u v 
	 * tab delimited format 
	 *
	 * todo
	 * 1) Specifiy delim
	 * 2) Specify precision
	 * 3) Add things like peak ratios and whatnot */
	if (m_dispsVec[0].valid()) {
	file << m_i << "\t" << m_j << "\t"
		 << m_dispsVec[0].x() << "\t"
		 << m_dispsVec[0].y() << "\t"
		 << std::endl;
	}
}
		

void PIVPoint::set_xCoord(int x)
{
	m_i = x;
}

void PIVPoint::set_yCoord(int y)
{
	m_j = y;
}

void PIVPoint::set_coords(std::pair<int, int>& coords)
{
	m_i = coords.first;
	m_j = coords.second;
}


int PIVPoint::x()
{
	return m_i;
}

int PIVPoint::y()
{
	return m_j;
}

PIVPoint::~PIVPoint() {};

#endif
