#ifndef PIV_POINT_H
#define PIV_POINT_H

#include <memory>
#include <iostream>
#include <vector>

#include "pivoptions.h"
#include "ccf.h"
#include "int_map.h"

class PIVPoint
{
	public:
		PIVPoint(int xCoord, int yCoord, const std::unique_ptr<PivOptions>& options);
		~PIVPoint();
		// void printCcf();

		std::shared_ptr<CCF>& get_ccf();

		void set_xCoord(int x);
		void set_yCoord(int y);

	private:
		std::shared_ptr<CCF> _ccf;
		int _i, _j;
	
};

PIVPoint::PIVPoint(int xCoord, int yCoord, const std::unique_ptr<PivOptions>& options) :
	_ccf(std::make_shared<CCF>(options->get_windowHeight() + 1, options->get_windowWidth() + 1)),
	_i(xCoord),
	_j(yCoord)
{
	
}

std::shared_ptr<CCF>& PIVPoint::get_ccf()
{
	return _ccf;;
}

void PIVPoint::set_xCoord(int x)
{
	_i = x;
}

void PIVPoint::set_yCoord(int y)
{
	_j = y;
}

PIVPoint::~PIVPoint() {};

#endif
