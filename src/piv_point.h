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

		std::shared_ptr<CCF>& get_ccf();
		Peak::PeaksVec& get_peaks();
		Displacement::DispVec& get_displacementsVector();

		void set_xCoord(int x);
		void set_yCoord(int y);

		int get_xCoord();
		int get_yCoord();

	private:
		std::shared_ptr<CCF> _ccf;
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

std::shared_ptr<CCF>& PIVPoint::get_ccf()
{
	return _ccf;
}

std::vector<Peak>& PIVPoint::get_peaks()
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
