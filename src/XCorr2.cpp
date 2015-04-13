#include "XCorr2.hpp"

namespace PivEng {

void x_corr_n_2(Mat2<double>& ccf,
		const int imageCols,
		const uint16_t* im1_first_pixel,
		const uint16_t* im2_first_pixel,
		const int col,
		const int row)
{
	auto ccfRows = ccf.rows(),
		ccfCols = ccf.cols(),
		winRows = ccfRows - 1,
		winCols = ccfCols - 1,
		mOffset = winRows + ccfRows/2 - winRows,
		nOffset = winCols + ccfCols/2 - winCols,

		/* Upper left corner WRT interrogation window centre */
		xOff = col - winCols / 2 + 1,
		yOff = row - winRows / 2 + 1;

	/* Pixel averages and correlation bits */
	auto  bitProd = 0.0, win1Avg = 0.0, win2Avg = 0.0, denom1 = 0.0, denom2 = 0.0;

	/* m and n are the row and column of the ccf (respectively) */
	int mMin = mOffset > 0 ? -mOffset : 0;
	int nMin = nOffset > 0 ? -nOffset : 0;

	/* Correlation function coordinates and iterator.  */
	int ctr = 0, m, n;

	/* Overlapping regions */
	int tOffyMin, tOffyMax, tOffxMin, tOffxMax, numPix;

	/* Store all the overlapping pixels as we will be using them twice */
	std::vector<PairD> pixels(ccf.size());
	int idx, pixCtr, win1sum, win2sum;
	// int idxShift;
	/* Some image pixel coords */
	int i(0), j(0);
	auto p1subAvg = 0.0,
		 p2subAvg = 0.0;

	int p1, p2;
	int image_2_offset;
	auto current_pixels = std::make_pair(0.0, 0.0);

	for (auto& ccfp : ccf) {
		/* Correlation function coefficient index to correlation function plane coords */
		m = ctr     / ccfCols + mMin;
		n = (ctr++) % ccfCols + nMin;


		/* Overlapping window limits plus window offset in image plane */
		tOffyMin = (m < 0 ? -m : 0) + yOff;
		tOffyMax = (m + winRows > winRows ? winRows - m : winRows) + yOff;
		tOffxMin = (n < 0 ? -n : 0) + xOff;
		tOffxMax = (n + winCols > winCols ? winCols - n : winCols) + xOff;

		/* Number of pixels in overlapping region  */
		numPix = (tOffyMax - tOffyMin) * (tOffxMax - tOffxMin);
		pixCtr = win1sum = win2sum = 0;

		image_2_offset = m * imageCols + n;
		/* Calculate the overlapping segment averages */
		for (j = tOffyMin ; j < tOffyMax; j++) {
			for (i = tOffxMin; i < tOffxMax; i++) {
				idx = j * imageCols + i;

				p1 = *(im1_first_pixel + idx);
				p2 = *(im2_first_pixel + idx + image_2_offset);

				win1sum += p1;
				win2sum += p2;

				pixels[pixCtr++] = {static_cast<double>(p1), static_cast<double>(p2)};
			}
		}

		win1Avg = static_cast<double>(win1sum) / numPix;
		win2Avg = static_cast<double>(win2sum) / numPix;

		bitProd = denom1 = denom2 = 0.0;
		for (idx = 0; idx < numPix; idx++) {
			current_pixels = pixels[idx];

			p1subAvg = current_pixels.first - win1Avg;
			p2subAvg = current_pixels.second - win2Avg;
			
			bitProd += p1subAvg * p2subAvg;
			denom1 += p1subAvg * p1subAvg;
			denom2 += p2subAvg * p2subAvg;
		}

		/* Put everything in and do not divide by zero. If denominator is <= 0, use CCF
		 * value of -1.0. */
		ccfp =  (denom1 > 0) && (denom2 > 0) ? bitProd / sqrt(denom1 * denom2) : -1.0;
	}
}
}
