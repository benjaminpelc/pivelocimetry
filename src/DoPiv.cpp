#include "DoPiv.hpp"

namespace PivEng {
DoPiv::DoPiv(PivOptions& options, const IntMap::Pair& imPair, Grid& g) :  
		m_ccfs(g.numPoints(), CCF(options.winHeight() + 1, options.winWidth() + 1)),
		m_points(g.numPoints(), PivPoint(-1, -1, options)),
		m_numX(g.numX()),
    	m_numY(g.numY())
{
	/* Create a vector of PivPoints when the object is instantiated, 
 	 * give constructor to instantiate CCF at correct size, 
 	 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done 
 	 *
 	 * Once vector points have been initiated loop through each point with 
 	 * an individual pair of interrogation region coordinates and do the PIV 
 	 * calculation for each point */

	/* Loop through each grid point: */
	/* The number of points is the same as the number of coordinates. Always */
	/* Set an iterator to the start of the piv points vector */	
	// auto coordPairPtr = g.coordsVec().begin();
	auto im1firstPix = imPair.first->begin();
	auto im2firstPix = imPair.second->begin();

	auto ccfBatch = [&](int beg, int end) {
		for (auto ctr = 0 + beg; ctr != 0 + end; ctr++) {
			XCorr2::xCorr2n(m_ccfs[ctr], 512, im1firstPix, im2firstPix, g[ctr].first, g[ctr].second);
			m_points[ctr].set_coords(g[ctr]);
			doPivPoint(m_points[ctr], m_ccfs[ctr]);
		}
	};

	// ccfBatch(0, g.numPoints());
	std::thread t1{ccfBatch, 0, g.numPoints()/2};
	ccfBatch(g.numPoints()/2, g.numPoints());
	t1.join();
}

DoPiv::PivPointVec& DoPiv::pointsVector()
{
	return m_points;
}

void DoPiv::doPivPoint(PivPoint& pivPoint, CCF& ccf)
{
	/* Steps to do the PIV analysis for the current interrogation window 
	 * 1) set the PivPoint coordinates
	 * 2) do the cross-correlation
	 * 3) find the correlation function peaks
	 * 4) calculate the total displacements using sub-pixel peak fitting */

	/* The ccf and peaks are referenced multiple times so create 
	 * pointers to clean up a little */
	// CCF* ccf        = pivPoint.get_ccf();
	Peak::PeaksVec& peaks = pivPoint.peaks();

	/* Store coords and do the cross-correlation */
	// XCorr2::xCorr2n(*ccf, 512, im1firstPix, im2firstPix, pivPoint.x(), pivPoint.y());

	/* Here the maximum search value needs replacing with variable */
	ccf.findPeaks(peaks, 7);
	SubPixel::gauss(ccf, peaks, pivPoint.dispsVec());
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
			<< std::setprecision(3) << std::fixed
			<< std::setw(8) 
			<< "\t" << p.primaryDisp().u
			<< "\t" << p.primaryDisp().v 
			<< "\t" << sqrt(pow(p.dispsVec()[0].u, 2) + pow(p.dispsVec()[0].v, 2)) 
			<< "\t" << p.primaryDisp().valid << std::endl;
	}
	std::cout << "Total vectors calculated: " << m_points.size() << std::endl;
}

DoPiv::~DoPiv() {}

}
