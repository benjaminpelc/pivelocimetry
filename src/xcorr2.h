#ifndef XCORR2_H
#define XCORR2_H

/*
 * XCorr2.h
 * 2D cross-correlation functions
 *
 */

#include "ccf.h"
#include "int_map.h"

#include <cmath>
#include <memory>
#include <vector>

namespace PivEng {

	class XCorr2
	{
		public:
			typedef std::pair<int, int> IntPair;
			typedef std::pair<double, double> DoublePair;

			static void xCorr2n(CCF& ccf, IntMap::Pair& imPair, IntPair& coordPair);
		private:
	};

	void XCorr2::xCorr2n(CCF& ccf, IntMap::Pair& imPair, IntPair& coordPair)
	{
		/* Image intensity matrices */
		IntMap::Uptr& image1 = imPair.first;
		IntMap::Uptr& image2 = imPair.second;

		int imageCols = image1->cols();
		int imageRows = image1->rows();

		int ccfRows = ccf.rows(),
			ccfCols = ccf.cols(),
			winRows = ccfRows - 1,
			winCols = ccfCols - 1,
			mOffset = winRows + (int) floor(ccfRows/2.0 - winRows),
			nOffset = winCols + (int) floor(ccfCols/2.0 - winCols),

			/* Upper left corner WRT interrogation window centre */
			xOff = coordPair.first  - (int) (winCols / 2.0) + 1,
			yOff = coordPair.second - (int) (winRows / 2.0) + 1;

		// Pointers to image first pixels
		auto im1pixel = image1->begin(), im2pixel = image2->begin();

		// Pixel averages and correlation bits
		auto  bitProd = 0.0, win1Avg = 0.0, win2Avg =0.0, denom1=0.0, denom2=0.0; 

		// m and n are the row and column of the ccf (respectively)
		int mMin = mOffset > 0 ? -mOffset : 0;
		int nMin = nOffset > 0 ? -nOffset : 0;
		
		// Correlation function coordinates and iterator. 
		int ctr = 0, m, n;

		// Overlapping regions
		int tOffyMin, tOffyMax, tOffxMin, tOffxMax, numPix;

		// Store all the overlapping pixels as we will be using them twice
		std::vector<DoublePair> pixels(ccf.size());
		auto firstPixel = pixels.begin();
		int idx, idxShift, pixCtr;

		/* Do for each point in the correlation function */
		std::for_each(ccf.begin(), ccf.end(), [&](auto& ccfp) {
				
			/* Correlation function coefficient index to correlation function plane coords */
			m = ctr     / ccfCols + mMin;
			n = (ctr++) % ccfCols + nMin;

			// Reset all counters
			win1Avg = win2Avg = bitProd = denom1 = denom2 = 0.0;

			// Overlapping window limits plus window offset in image plane
			tOffyMin = (m < 0 ? -m : 0) + yOff;
			tOffyMax = (m + winRows > winRows ? winRows - m : winRows) + yOff;
			tOffxMin = (n < 0 ? -n : 0) + xOff;
			tOffxMax = (n + winCols > winCols ? winCols - n : winCols) + xOff;

			// Number of pixels in overlapping region 
			numPix = (tOffyMax - tOffyMin) * (tOffxMax - tOffxMin);
			pixCtr = 0;	

			// Calculate the overlapping segment averages
			for (int j = tOffyMin ; j < tOffyMax; j++) {
				for (int i = tOffxMin; i < tOffxMax; i++) {
					/* Pixel index */
					idx = j * imageCols + i;

					/* Pixel offset for second image */
					idxShift = m * imageCols + n;

					/* Sum the pixel intensities */
					win1Avg += *(im1pixel + idx );
					win2Avg += *(im2pixel + idx + idxShift);

					/* Store the pixels for later so we do not have to 
					 * lookup again */
					pixels[pixCtr++] = (std::make_pair((double) *(im1pixel + idx),(double) *(im2pixel + idx + idxShift)));
				}
			}

			// Divide by the number of elements in each overlapping region
			win1Avg /= numPix;
			win2Avg /= numPix;

			/* Calculate the correlation coefficients for this window offset */
			for_each(firstPixel, firstPixel + numPix, [&](auto& pixPair) {
				bitProd += (pixPair.first - win1Avg) * (pixPair.second - win2Avg);
				denom1 += pow(pixPair.first - win1Avg, 2);
				denom2 += pow(pixPair.second - win2Avg, 2);
			});

			/* Put everything in and do not divide by zero. If denominator is <= 0, use CCF
			 * value of -1.0. */
			ccfp =  (denom1 > 0) && (denom2 > 0) ? bitProd / sqrt(denom1 * denom2) : -1.0;
		});
	}
}

#endif
