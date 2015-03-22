/* Class DoPiv
 *
 * Main engine of the program, do the actual PIV 
 * */

#ifndef BBPIV_DO_PIV_H
#define BPPIV_DO_PIV_H

#include <fstream>
#include <algorithm>
#include <iomanip>

#include "pivoptions.h"
#include "int_map.h"
#include "grid.h"
#include "xcorr2.h"
#include "piv_point.h"
#include "subpix.h"

namespace PivEng {

class DoPiv
{
	public:
		typedef std::vector<PIVPoint> PivPointVec;

		DoPiv(PivOptions& options, IntMap::Pair& imPair, Grid& g);
		void print();
		void write(const std::string filename);

		~DoPiv();

	private:
		void doPivPoint(PIVPoint& pivPoint, Grid::CoordPair& coordPair, IntMap::Pair& images, std::pair<int, int>& winSize);
		int m_numX,
			m_numY;
		PivPointVec m_points;
};

DoPiv::DoPiv(PivOptions& options, IntMap::Pair& imPair, Grid& g) :  
		m_numX(g.numX()),
    	m_numY(g.numY()),
		m_points(g.numPoints(), PIVPoint(-1, -1, options))
{
	/* Create a vector of PIVPoints when the object is instantiated, 
 	 * give constructor to instantiate CCF at correct size, 
 	 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done 
 	 *
 	 * Once vector points have been initiated loop through each point with 
 	 * an individual pair of interrogation region coordinates and do the PIV 
 	 * calculation for each point */

	/* Loop through each grid point: */
	/* The number of points is the same as the number of coordinates. Always */
	/* Set an iterator to the start of the piv points vector */	
	auto coordPair = g.coordsVec().begin();

	for_each(m_points.begin(), m_points.end(), [&](auto& p) {
				this->doPivPoint(p, *(coordPair++), imPair, options.winSize());
			});
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
	CCF* ccf        = pivPoint.get_ccf();
	Peak::PeaksVec& peaks = pivPoint.peaks();

	/* Store coords and do the cross-correlation */
	pivPoint.set_coords(coordPair);
	XCorr2::xCorr2n(*ccf, images, coordPair);

	/* Here the maximum search value needs replacing with variable */
	ccf->findPeaks(peaks, 7);
	SubPixel::gauss(*ccf, peaks, pivPoint.dispsVec());

}

void DoPiv::write(const std::string filename)
{
	/* Write out the PIV vectors in the format 
	 * x	y	u	v	
	 * Use tab delimiter. Modify this to use specified delimeter */
	std::ofstream outfile(filename);

	/* Use for each passing each point to a lambda which calls the 
	 * point to be printed to the ofstream. Be sure to pass by reference as 
	 * usual. */ 
	std::for_each(m_points.begin(), m_points.end(), [&outfile](auto &point){ 
						point.printToOfstream(outfile);
				});

	outfile.close();
}

void DoPiv::print()
{
	/* Print the points and the displacements to screen
	 *
	 * todo:
	 * Tidy this up */
	for (auto p : m_points) {
		std::cout << std::setw(6) << std::left 
			<< p.x() << "\t" << p.y() 
			<< std::setprecision(4) << std::fixed
			<< std::setw(8) 
			<< "\t" << p.dispsVec()[0].x()
			<< "\t " << p.dispsVec()[0].y() 
			<< "\t " << sqrt(pow(p.dispsVec()[0].x(), 2) + pow(p.dispsVec()[0].y(), 2)) << std::endl;
	}
	std::cout << "Total vectors calculated: " << m_points.size() << std::endl;
}

DoPiv::~DoPiv() {}

}

#endif
