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
		PIVPoint(int xCoord, int yCoord, const PivOptions::Uptr& options);
		~PIVPoint();

		CCF::Sptr& get_ccf();
		Peak::PeaksVec& get_peaks();
		Displacement::DispVec& get_displacementsVector();

		void set_xCoord(int x);
		void set_yCoord(int y);
		void set_coords(Grid::CoordPair& coords);

		int x();
		int y();
		
		Displacement& get_primaryDisplacement();
		void printToOfstream(std::ofstream& file);
		

	private:
		CCF::Sptr _ccf;
		Peak::PeaksVec _peaksVector;
		Displacement::DispVec _dispsVec;
		int _i, _j;
};

PIVPoint::PIVPoint(int xCoord, int yCoord, const PivOptions::Uptr& options) :
	_ccf(std::make_shared<CCF>(options->winHeight() + 1, options->winWidth() + 1)),
	_peaksVector(options->numPeaks()),
	_dispsVec(options->numPeaks()),
	_i(xCoord),
	_j(yCoord)
{}

CCF::Sptr& PIVPoint::get_ccf()
{
	return _ccf;
}

Peak::PeaksVec& PIVPoint::get_peaks()
{
	return _peaksVector;
}

Displacement::DispVec& PIVPoint::get_displacementsVector()
{
	return _dispsVec;
}


Displacement& PIVPoint::get_primaryDisplacement()
{
	return _dispsVec[0];
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
	if (_dispsVec[0].valid()) {
	file << _i << "\t" << _j << "\t"
		 << _dispsVec[0].x() << "\t"
		 << _dispsVec[0].y() << "\t"
		 << std::endl;
	}
}
		

void PIVPoint::set_xCoord(int x)
{
	_i = x;
}

void PIVPoint::set_yCoord(int y)
{
	_j = y;
}

void PIVPoint::set_coords(std::pair<int, int>& coords)
{
	_i = coords.first;
	_j = coords.second;
}


int PIVPoint::x()
{
	return _i;
}

int PIVPoint::y()
{
	return _j;
}

PIVPoint::~PIVPoint() {};

#endif
