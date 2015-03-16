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
		void set_coords(std::pair<int, int>& coords);

		int get_xCoord();
		int get_yCoord();

	private:
		CCF::Sptr _ccf;
		Peak::PeaksVec _peaksVector;
		Displacement::DispVec _displacementsVector;
		int _i, _j;
	
};

PIVPoint::PIVPoint(int xCoord, int yCoord, const PivOptions::Uptr& options) :
	_ccf(std::make_shared<CCF>(options->get_windowHeight() + 1, options->get_windowWidth() + 1)),
	_peaksVector(options->get_noPeaks()),
	_displacementsVector(options->get_noPeaks()),
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
	return _displacementsVector;
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


int PIVPoint::get_xCoord()
{
	return _i;
}

int PIVPoint::get_yCoord()
{
	return _j;
}

PIVPoint::~PIVPoint() {};

#endif
