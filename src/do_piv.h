#ifndef DO_PIV_H
#define DO_PIV_H

#include "pivoptions.h"
#include "int_map.h"
#include "grid.h"
#include "xcorr2.h"
#include "piv_point.h"

class DoPiv
{
	public:
		DoPiv(std::unique_ptr<PivOptions>& options,
			  std::unique_ptr<IntMap>& i1,
			  std::unique_ptr<IntMap>& i2,
			  std::unique_ptr<Grid>& g);

		~DoPiv();

	private:
		int _noVectorsX,
			_noVectorsY;
		std::vector<PIVPoint> vp;
};

/* Create a vector of PIVPoints when the object is instantiated, 
 * give constructor to instantiate CCF at correct size, 
 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done */
DoPiv::DoPiv(std::unique_ptr<PivOptions>& options,
			  std::unique_ptr<IntMap>& i1,
			  std::unique_ptr<IntMap>& i2,
			  std::unique_ptr<Grid>& g) 
	:
		_noVectorsX(g->get_noPointsX()),
		_noVectorsY(g->get_noPointsY()),
		vp(g->get_totalGridPoints(), PIVPoint(-1, -1, options))
{
	/* Loop through each grid point:
	 * 1) Set the correct coordinates
	 * 2) Do the PIV */
	// int iNow, jNow;
	int wX = options->get_windowWidth(),
		wY = options->get_windowHeight();
	// for (int j = 0; j < g->get_noPointsY(); j++) {
	// 	for (int i = 0; i < g->get_noPointsX(); i++) {
	// 		iNow = g->get_xCoord(i);
	// 		jNow = g->get_yCoord(j);
	// 		vp[i*j].set_xCoord(iNow);			
	// 		vp[i*j].set_yCoord(jNow);			
	// 		XCorr2::xCorr2n(vp[i*j].get_ccf(), i1, i2, iNow, jNow, wX, wY);
	// 	}
	// }
	
	/* Set an iterator to the start of the piv points vector */
	auto it = vp.begin();
	for (auto el : g->get_xCoordVector() ) {
		for (auto yel : g->get_yCoordVector() ) {
			std::cout << el << " " << yel << std::endl;
			it->set_xCoord(el);
			it->set_yCoord(yel);
			XCorr2::xCorr2n(it->get_ccf(), i1, i2, el, yel, wX, wY);

			std::cout << "From big vec x: " << it->get_xCoord() << std::endl;
			std::cout << "From big vec y: " << it->get_yCoord() << std::endl;
			it++;
		}
	}

	std::cout << vp[10].get_xCoord() << std::endl;
	std::cout << vp[10].get_yCoord() << std::endl;


	std::cout << "Vectors calculated: " << vp.size() << std::endl;
	std::cout << *vp[0].get_ccf() << std::endl;
}

DoPiv::~DoPiv() {}

#endif
