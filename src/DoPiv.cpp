#include "DoPiv.hpp"

namespace PivEng {
DoPiv::DoPiv(PivOptions& options, const IntMap::Pair& imPair, Grid& g) :  
		m_num_points(g.size()),
		m_ccfs(m_num_points, CCF(options.winHeight() + 1, options.winWidth() + 1)),
		m_points(m_num_points, PivPoint(-1, -1, options))
{
	/* Create a vector of PivPoints when the object is instantiated, 
 	 * give constructor to instantiate CCF at correct size, 
 	 * for now set coordinate to (-1, -1) to indicate that the piv has not yet been done 
 	 *
 	 * Once vector points have been initiated loop through each point with 
 	 * an individual pair of interrogation region coordinates and do the PIV 
 	 * calculations for each point */

	/* Loop through each grid point: */
	auto im1Beg = imPair.first->begin();
	auto im2Beg = imPair.second->begin();
	auto imCols = imPair.first->cols();

	// for (auto& p : m_points)


	auto ccfBatch = [&](int beg, int end) {
		PairII x;
		CCF* ccf = nullptr;
		PivPoint* p = nullptr;

		for (auto idx = beg; idx != end; idx++) {
			x = g[idx];
			ccf = &m_ccfs[idx];
			p = &m_points[idx];

			XCorr2::xCorr2n(*ccf, imCols, im1Beg, im2Beg, x.first, x.second);
			doPivPoint(*p, *ccf);
		}
	};

	// ccfBatch(0, g.size());
	std::thread t1{ccfBatch, 0, m_num_points/2};
	ccfBatch(m_num_points/2, m_num_points);
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

	Disp* pv = nullptr;

	for (auto& p : m_points) {
		pv = &p.primaryDisp();
		std::cout
			<< p.x() << "\t" << p.y() 
			<< std::setprecision(3) << std::fixed
			<< "\t" << pv->u
			<< "\t" << pv->v 
			<< "\t" << sqrt(pow(pv->u, 2) + pow(pv->v, 2)) 
			<< "\t" << pv->valid << std::endl;
	}
	std::cout << "Total vectors calculated: " << m_points.size() << std::endl;
}

DoPiv::~DoPiv() {}

}
