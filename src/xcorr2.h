#ifndef XCORR2_H
#define XCORR2_H

/*
 * XCorr2.h
 * Container class for 2D cross-correlation functions
 *
 */

#include "ccf.h"
#include "int_map.h"
#include "matrix2.h"
#include <math.h>
#include <memory>
#include <vector>

class XCorr2
{
	public:
		static void xCorr2n(CCF& ccf, IntMap::Pair& imPair,
				std::pair<int, int>& coordPair, std::pair<int, int>& window);
	private:
};

// template<typename T>
void XCorr2::xCorr2n(CCF& ccf, IntMap::Pair& imPair, std::pair<int, int>& coordPair, std::pair<int, int>& window)
{
	IntMap::Uptr& m1 = imPair.first;
	IntMap::Uptr& m2 = imPair.second;

	int mw = m1->cols();
	int mh = m1->rows();

	int ccfRows = ccf.rows(),
		ccfCols = ccf.cols(),
		imRows = window.second,
		imCols = window.first,
		mOffset = imRows + (int) floor((ccfRows/2.0 - imRows)),
		nOffset = imCols + (int) floor((ccfCols/2.0 - imCols)),
		xOff = coordPair.first - (int) (window.first / 2.0) + 1,
		yOff = coordPair.second - (int) (window.second / 2.0) + 1;

	// Pointers to image first pixels
	auto im1p = m1->begin(), im2p = m2->begin();

	// Pixel averages and correlation bits
	auto  bitProd = 0.0, m1Avg = 0.0, m2Avg =0.0, denom1=0.0, denom2=0.0; 

	// m and n are the row and column of the ccf (respectively)
	int mMin = mOffset > 0 ? -mOffset : 0;
	int nMin = nOffset > 0 ? -nOffset : 0;
	
	// Correlation function coordinates and iterator. 
	int ctr = 0, m, n;

	// Overlapping regions
	int tOffyMin, tOffyMax, tOffxMin, tOffxMax, numPix;

	// Store all the overlapping pixels as we will be using them twice
	std::vector<std::pair<double, double> > pixels(ccf.size());
	auto firstPixel = pixels.begin();
	int idx, idxShift, pixCtr;

	std::for_each(ccf.begin(), ccf.end(), [&](auto& ccfp) {
			
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
		pixCtr = 0;	

		// Calculate the overlapping segment averages
		for (int j = tOffyMin ; j < tOffyMax; j++) {
			for (int i = tOffxMin; i < tOffxMax; i++) {
				idx = j * mw + i;
				idxShift = m * mw + n;
				m1Avg += *(im1p + idx );
				m2Avg += *(im2p + idx + idxShift);
				pixels[pixCtr++] = (std::make_pair((double) *(im1p + idx),(double) *(im2p + idx + idxShift)));
			}
		}

		// Divide by the number of elements in each overlapping region
		m1Avg /= numPix;
		m2Avg /= numPix;

		/* Calculate the correlation coefficient for this window offset */
		for_each(firstPixel, firstPixel + numPix, [&](auto& pixpair) {
			bitProd += (pixpair.first - m1Avg) * (pixpair.second - m2Avg);
			denom1 += pow(pixpair.first - m1Avg, 2);
			denom2 += pow(pixpair.second - m2Avg, 2);
		});

		// Put everything in and do not divide by zero
		ccfp =  denom1 > 0 && denom2 > 0 ? bitProd / sqrt(denom1 * denom2) : -1.0;
	});
}
#endif
