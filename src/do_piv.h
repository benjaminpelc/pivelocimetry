/* Class DoPiv
 *
 * Main engine of the program, do the actual PIV */

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
	std::pair<int, int> windowSize{options->get_windowWidth(), options->get_windowHeight()};
	
	/* Set an iterator to the start of the piv points vector */
	auto it = _vp.begin();
	/* Double looping through each coordinate is ugly and tiresome.
	 * Rather than individual x and y coordinate vectors modify grid 
	 * to return a vector of column major coordinates 
	 */
	auto p = g->get_coordPairsVector().begin();
	int xc, yc;
	while (it != _vp.end() && p != g->get_coordPairsVector().end()) {
		/* Should probably break these inner contents into s sub-method 
		 * to increase readability 
		 * something along the lines of:
		 *
		 * void doPointPiv(it, i1, i2, xy, yc, wX, wY)
		 *
		 * if we put image pairs in a container and make some 
		 * tuples can reduce it to:
		 *
		 * void doPointPiv(it, I, X, W)
		 *
		 * */
		it->set_coords(*p);
		XCorr2::xCorr2n(it->get_ccf(), i1, i2, *p, windowSize);

		/* Find some peaks from the correlation function and fill piv point's
		 * peaks vector */
		it->get_ccf()->findPeaks(it->get_peaks(), 7);

		/* Get the subpixel displacements */
		SubPixlel::gauss(it->get_ccf(), it->get_peaks(), it->get_displacementsVector());
		it++, p++;
	}
	// std::cout << _vp[0].get_peaks()[0].get_val() << std::endl;
	// std::cout << *_vp[0].get_ccf() << std::endl;
	// std::cout << _vp[0].get_displacementsVector()[0].get_displacementX() << std::endl;
	// std::cout << _vp[0].get_displacementsVector()[0].get_displacementY() << std::endl;

	// std::cout << _vp[10].get_xCoord() << std::endl;
	// std::cout << _vp[10].get_yCoord() << std::endl;
	// std::cout << "Vectors calculated: " << _vp.size() << std::endl;
	// std::cout << *_vp[0].get_ccf() << std::endl;
	
	// for (auto p : _vp) {
	// 	std::cout << "x, y, u, v: " << p.get_xCoord() << ", " << p.get_yCoord() 
	// 		<< ", " << p.get_displacementsVector()[0].get_displacementX()
	// 		<< ", " << p.get_displacementsVector()[0].get_displacementY() << std::endl;
	// }
	
	std::cout << "Total vectors calculated: " << _vp.size() << std::endl;
}

DoPiv::~DoPiv() {}

#endif
