#ifndef DO_PIV_H
#define DO_PIV_H

#include "pivoptions.h"
#include "int_map.h"
#include "grid.h"
#include "xcorr2.h"
#include "piv_point.h"
#include "subpix.h"

class DoPiv
{
	public:
		typedef std::vector<PIVPoint> PivPointVec;

		DoPiv(PivOptions::Uptr& options,
			  IntMap::Uptr& i1,
			  IntMap::Uptr& i2,
			  Grid::Uptr& g);

		~DoPiv();

	private:
		int _noVectorsX,
			_noVectorsY;
		PivPointVec _vp;
};

/* Create a vector of PIVPoints when the object is instantiated, 
 * give constructor to instantiate CCF at correct size, 
 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done */
DoPiv::DoPiv(PivOptions::Uptr& options, IntMap::Uptr& i1, IntMap::Uptr& i2, Grid::Uptr& g) 
	:   _noVectorsX(g->get_noPointsX()),
    	_noVectorsY(g->get_noPointsY()),
		_vp(g->get_totalGridPoints(), PIVPoint(-1, -1, options))
{
	/* Loop through each grid point:
	 * 1) Set the correct coordinates
	 * 2) Do the PIV */
	int wX = options->get_windowWidth(),
		wY = options->get_windowHeight();
	
	/* Set an iterator to the start of the piv points vector */
	auto it = _vp.begin();
	for (auto xc : g->get_xCoordVector() ) {
		for (auto yc : g->get_yCoordVector() ) {
			it->set_xCoord(xc);
			it->set_yCoord(yc);
			XCorr2::xCorr2n(it->get_ccf(), i1, i2, xc, yc, wX, wY);
			
			/* Find some peaks from the correlation function and fill piv point's
			 * peaks vector */
			it->get_ccf()->findPeaks(it->get_peaks(), 7);

			/* Get the subpixel displacements */
			SubPixlel::gauss(it->get_ccf(), it->get_peaks(), it->get_displacementsVector());

			it++;
			// break;
		}
		// break;
	}
	// std::cout << _vp[0].get_peaks()[0].get_val() << std::endl;
	// std::cout << *_vp[0].get_ccf() << std::endl;
	// std::cout << _vp[0].get_displacementsVector()[0].get_displacementX() << std::endl;
	// std::cout << _vp[0].get_displacementsVector()[0].get_displacementY() << std::endl;

	// std::cout << _vp[10].get_xCoord() << std::endl;
	// std::cout << _vp[10].get_yCoord() << std::endl;
	// std::cout << "Vectors calculated: " << _vp.size() << std::endl;
	// std::cout << *_vp[0].get_ccf() << std::endl;
	for (auto p : _vp)
	{
		// std::cout << "x, y, u, v: " << p.get_xCoord() << ", " << p.get_yCoord() 
		// 	<< ", " << p.get_displacementsVector()[0].get_displacementX()
		// 	<< ", " << p.get_displacementsVector()[0].get_displacementY() << std::endl;
	}
	// std::cout << "Total vectors calculated: " << _vp.size() << std::endl;
}

DoPiv::~DoPiv() {}

#endif
