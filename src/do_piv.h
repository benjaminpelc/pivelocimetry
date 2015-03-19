/* Class DoPiv
 *
 * Main engine of the program, do the actual PIV */

#ifndef DO_PIV_H
#define DO_PIV_H

#include <fstream>
#include <algorithm>

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

		DoPiv(PivOptions::Uptr& options, IntMap::Pair& imPair, Grid::Uptr& g);
		void print();
		void write(const std::string filename);

		~DoPiv();

	private:
		void doPivPoint(PIVPoint& pivPoint, Grid::CoordPair& coordPair, IntMap::Pair& images, std::pair<int, int>& winSize);
		int _numX,
			_numY;
		PivPointVec _pivPoints;
};

/* Create a vector of PIVPoints when the object is instantiated, 
 * give constructor to instantiate CCF at correct size, 
 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done 
 *
 * Once vector points have been initiated loop through each point with 
 * an individual pair of interrogation region coordinates and do the PIV 
 * calculation for each point */
DoPiv::DoPiv(PivOptions::Uptr& options, IntMap::Pair& imPair, Grid::Uptr& g) :  
		_numX(g->numX()),
    	_numY(g->numY()),
		_pivPoints(g->numPoints(), PIVPoint(-1, -1, options))
{
	/* Loop through each grid point: */
	/* The number of points is the same as the number of coordinates. Always */
	/* Set an iterator to the start of the piv points vector */	
	auto coordPair = g->coordsVec().begin();
	for (auto& vectorPoint : _pivPoints) {
		doPivPoint(vectorPoint, *(coordPair++), imPair, options->winSize());
	}
}

void DoPiv::doPivPoint(PIVPoint& pivPoint, Grid::CoordPair& coordPair, IntMap::Pair& images, std::pair<int, int>& winSize)
{
	/* Steps to do the PIV analysis for the current interrogation window 
	 * 1) set the pivPoint coordinates
	 * 2) do the cross-correlation
	 * 3) find the correlation function peaks
	 * 4) calculate the total displacements using sub-pixel peak fitting
	 */

	/* The ccf and peaks are referenced multiple times so create 
	 * pointers to clean up a little */
	CCF::Sptr& ccf        = pivPoint.get_ccf();
	Peak::PeaksVec& peaks = pivPoint.get_peaks();

	/* Store coords and do the cross-correlation */
	pivPoint.set_coords(coordPair);
	XCorr2::xCorr2n(ccf, images, coordPair, winSize);

	/* Here the maximum search value needs replacing with variable */
	ccf->findPeaks(peaks, 7);
	SubPixlel::gauss(ccf, peaks, pivPoint.get_displacementsVector());
}

void DoPiv::write(const std::string filename)
{
	/* Write out the PIV vectors in the format 
	 * x	y	u	v	
	 * 
	 * Use tab delimiter. Modify this to use specified delimeter */
	std::ofstream outfile(filename);

	/* Use for each passing each point to a lambda which calls the 
	 * point to be printed to the ofstream. Be sure to pass by reference as 
	 * usual. */ 
	std::for_each(_pivPoints.begin(), _pivPoints.end(), [&outfile](auto &pivPoint){ 
						pivPoint.printToOfstream(outfile);
				});

	outfile.close();
}

void DoPiv::print()
{
	/* Print the points and the displacements to screen
	 *
	 * todo:
	 * Tidy this up */
	for (auto p : _pivPoints) {
		std::cout << "x, y, u, v: " << p.x() << ", " << p.y() 
			<< ", " << p.get_displacementsVector()[0].x()
			<< ", " << p.get_displacementsVector()[0].y() << std::endl;
	}
	std::cout << "Total vectors calculated: " << _pivPoints.size() << std::endl;
}

DoPiv::~DoPiv() {}

#endif
