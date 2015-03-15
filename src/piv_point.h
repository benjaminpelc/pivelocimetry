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

	private:
		std::shared_ptr<CCF> _ccf;
	
};

PIVPoint::PIVPoint(int xCoord, int yCoord, const std::unique_ptr<PivOptions>& options) :
	_ccf(std::make_shared<CCF>(17, 17))
	// _ccf(new CCF(options->get_windowHeight() + 1, options->get_windowWidth() + 1))
{
	std::cout << "In PIV point" << std::endl;
	
	// CCF _ccf = CCF( options->get_windowHeight() + 1, options->get_windowWidth() + 1);

	// std::cout << *_ccf << std::endl;
}

// void PIVPoint::printCcf()
// {
// 	std::cout << *_ccf << std::endl;
// 	// return _ccf->get_elementAt(j, i);
// }

std::shared_ptr<CCF>& PIVPoint::get_ccf()
{
	return _ccf;;
}

PIVPoint::~PIVPoint() {};

#endif
