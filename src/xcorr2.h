#ifndef XCORR2_H
#define XCORR2_H

/*
 * XCorr2.h
 * Container class for 2D cross-correlation fucntions
 *
 */

#include "ccf.h"
#include "int_map.h"
#include "matrix2.h"
#include <math.h>
#include <memory>

class XCorr2
{
	public:
		static void xCorr2n(CCF::Sptr& ccf, IntMap::Pair& imPair,
				std::pair<int, int>& coordPair, std::pair<int, int>& window);
	private:
};

// template<typename T>
void XCorr2::xCorr2n(CCF::Sptr& ccf, IntMap::Pair& imPair, std::pair<int, int>& coordPair, std::pair<int, int>& window)
{
	IntMap::Uptr& m1 = imPair.first;
	IntMap::Uptr& m2 = imPair.second;

	int mw = m1->cols();
	int mh = m1->rows();

	int ccfRows = ccf->rows(),
		ccfCols = ccf->cols(),
		imRows = window.second,
		imCols = window.first,
		mOffset = imRows + (int) floor((ccfRows/2.0 - imRows)),
		nOffset = imCols + (int) floor((ccfCols/2.0 - imCols)),
		xOff = coordPair.first - (int) (window.first / 2.0) + 1,
		yOff = coordPair.second - (int) (window.second / 2.0) + 1;

	// Pointers to image first pixels
	auto im1p = m1->begin(), im2p = m2->begin();

	// Pixel averages and correlation bits
	double  bitProd, m1Avg, m2Avg, denom1, denom2; 

	// m and n are the row and column of the ccf (respectively)
	int mMin = mOffset > 0 ? -mOffset : 0;
	int nMin = nOffset > 0 ? -nOffset : 0;
	
	// Correlation function coordinates and iterator. 
	int ctr = 0, m, n;

	// Overlapping regions
	int tOffyMin, tOffyMax, tOffxMin, tOffxMax, numPix;

	std::for_each(ccf->begin(), ccf->end(), [&](auto& ccfp) {
			
		m = ctr/ccfCols + mMin;
		n = (ctr++)%ccfCols + nMin;

		// Reset all counters
		m1Avg = m2Avg = bitProd = denom1 = denom2 = 0.0;

		// Overlapping window limits plus window offset in image plane
		tOffyMin = (m < 0 ? -m : 0) + yOff;
		tOffyMax = (m + imRows > imRows ? imRows - m : imRows) + yOff;
		tOffxMin = (n < 0 ? -n : 0) + xOff;
		tOffxMax = (n + imCols > imCols ? imCols - n : imCols) + xOff;

		// Number of pixels in overlapping region 
		numPix = (tOffyMax - tOffyMin) * (tOffxMax - tOffxMin);

		// Calculate the overlapping segment averages
		for (int j = tOffyMin ; j < tOffyMax; j++) {
			for (int i = tOffxMin; i < tOffxMax; i++) {
				m1Avg += (double) *(im1p + j * mw +  i );
				m2Avg += (double) *(im2p + (j + m) * mw + i + n);
			}
		}

		// Divide by the number of elements in each overlapping region
		m1Avg /= (double) numPix;
		m2Avg /= (double) numPix;

		// For each element in the overlapping regions sum the piecewise products of the elements minus the region average. Also calculate the two denominators
		for (int j = tOffyMin ; j < tOffyMax; j++) {
			for (int i = tOffxMin; i < tOffxMax; i++) {
				bitProd += ((double) *(im1p + j*mw + i) - m1Avg) * ((double) *(im2p + (j + m)*mw + i + n) - m2Avg);
				denom1 += ((double) *(im1p + j*mw + i) - m1Avg) * ((double) *(im1p + j*mw +  i) - m1Avg);
				denom2 += ((double) *(im2p + (j +  m)*mw +  i + n) - m2Avg) * ((double) *(im2p + (j + m)*mw +  i + n) - m2Avg);
			}
		}

		// Put everything in and do not divide by zero
		ccfp =  denom1 > 0 && denom2 > 0 ? bitProd / sqrt(denom1 * denom2) : -1.0;
	});
}
#endif
