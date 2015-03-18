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
		// Basic XCorr2 function. No normalising etc
		template<typename T>
		static void xCorr2(Matrix2<double>& mat, Matrix2<T>& m1, Matrix2<T>& m2);
		
		template<typename T>
		static void xCorr2m(Matrix2<double>& mat, Matrix2<T>& m1, Matrix2<T>& m2);

		// template<typename T>
		// static void xCorr2n(Matrix2<double>& mat, Matrix2<T>& m1, Matrix2<T>& m2, int x0, int y0, int wx, int wy);
		// static void xCorr2n(CCF::Sptr& ccf, std::unique_ptr<IntMap>& m1, std::unique_ptr<IntMap>& m2, int x0, int y0, int wx, int wy);
		// static void xCorr2n(CCF::Sptr& ccf, std::unique_ptr<IntMap>& m1, std::unique_ptr<IntMap>& m2, std::pair<int, int>& coordPair, int wx, int wy);
		// static void xCorr2n(CCF::Sptr& ccf, std::unique_ptr<IntMap>& m1, std::unique_ptr<IntMap>& m2,
		// 		std::pair<int, int>& coordPair, std::pair<int, int>& window);
		static void xCorr2n(CCF::Sptr& ccf, IntMap::Pair& imPair,
				std::pair<int, int>& coordPair, std::pair<int, int>& window);
	private:
};

template<typename T>
void XCorr2::xCorr2(
		Matrix2<double>& ccf,
		Matrix2<T>& m1,
		Matrix2<T>& m2
		)
{
	// Row and column counts of CCF
	int ccfRows = ccf.rows(),
		ccfCols = ccf.cols(),
		imRows  = m1.rows(),
		imCols  = m1.cols(),
		mIndex, nIndex,
		mOffset = imRows + (int) floor((ccfRows/2.0 - imRows)),
		nOffset = imCols + (int) floor((ccfCols/2.0 - imCols)),
		mMin, mMax, nMin, nMax,
		iMin, iMax, jMin, jMax;

	// Product bit counter 
	T bitProd;
	
	// m and n are the row and column of the ccf (respectively)
	mMin = mOffset > 0 ? -mOffset : 0;
	nMin = nOffset > 0 ? -nOffset : 0;
	mMax = mOffset < ccfRows ? ccfRows - mOffset : ccfRows;
	nMax = nOffset < ccfCols ? ccfCols - nOffset : ccfCols;

	for (int m = mMin ; m < mMax; m++) {
		mIndex = m + mOffset; 

		for (int n = nMin; n < nMax; n++) {
		nIndex = n + nOffset;;
		
			bitProd = 0; // Reset counter

			// Limits of the overlapping regions
			iMin = m < 0 ? -m : 0;
			iMax = m + imRows > imRows ? imRows - m : imRows;
			jMin = n < 0 ? -n : 0;
			jMax = n + imCols > imCols ? imCols - n : imCols;

			for (int i = iMin; i < iMax; i++) {
				for (int j = jMin; j < jMax; j++) {
					bitProd += m1.getElem(i, j) * m2.getElem(i + m, j + n);
				}
			}
			ccf.setElem(mIndex, nIndex, (double) bitProd);
		}
	}
}


template<typename T>
void XCorr2::xCorr2m(
		Matrix2<double>& ccf,
		Matrix2<T>& m1,
		Matrix2<T>& m2
		)
{
	// Row and column counts of CCF
	int ccfRows = ccf.rows(),
		ccfCols = ccf.cols(),
		imRows  = m1.rows(),
		imCols  = m1.cols(),
		mIndex, nIndex,
		mOffset = imRows + (int) floor((ccfRows/2.0 - imRows)),
		nOffset = imCols + (int) floor((ccfCols/2.0 - imCols)),
		mMin, mMax, nMin, nMax,
		iMin, iMax, jMin, jMax;

	// Product bit counter 
	double  bitProd,
			m1Avg, m2Avg,
			denom1, denom2;
	
	// m and n are the row and column of the ccf (respectively)
	mMin = mOffset > 0 ? -mOffset : 0;
	nMin = nOffset > 0 ? -nOffset : 0;
	mMax = mOffset < ccfRows ? ccfRows - mOffset : ccfRows;
	nMax = nOffset < ccfCols ? ccfCols - nOffset : ccfCols;

	for (int m = mMin ; m < mMax; m++) {
		mIndex = m + mOffset; 
		for (int n = nMin; n < nMax; n++) {
		nIndex = n + nOffset;;
		
			// Limits of the overlapping regions
			iMin = m < 0 ? -m : 0;
			iMax = m + imRows > imRows ? imRows - m : imRows;
			jMin = n < 0 ? -n : 0;
			jMax = n + imCols > imCols ? imCols - n : imCols;

			// Reset all counters
			m1Avg = m2Avg = bitProd = denom1 = denom2 = 0.0;

			// Calculate the overlapping segment averages
			for (int i = iMin; i < iMax; i++) {
				for (int j = jMin; j < jMax; j++) {
					m1Avg += (double) m1.getElem(i, j);
					m2Avg += (double) m2.getElem(i + m, j + n);
				}
			}

			// Divide by the number of elements in each overlapping region
			m1Avg /= (double) ((iMax - iMin) * (jMax - jMin));
			m2Avg /= (double) ((iMax - iMin) * (jMax - jMin));

			// For each element in the overlapping regions sum the piecewise products of the elements minus the region average. Also calculate the two denominators
			for (int i = iMin; i < iMax; i++) {
				for (int j = jMin; j < jMax; j++) {
					bitProd += ((double) m1.getElem(i, j) - m1Avg) * ((double) m2.getElem(i + m, j + n) - m2Avg);
					denom1 += ((double) m1.getElem(i, j) - m1Avg) * ((double) m1.getElem(i, j) - m1Avg);
					denom2 += ((double) m2.getElem(i + m, j + n) - m2Avg) * ((double) m2.getElem(i + m, j + n) - m2Avg);
				}
			}
			// Put everything in and do not divide by zero
			ccf.setElem(mIndex, nIndex, denom1 > 0 && denom2 > 0 ? bitProd / sqrt(denom1 * denom2) : -1.0);
		}
	}
}

// template<typename T>
void XCorr2::xCorr2n(CCF::Sptr& ccf, IntMap::Pair& imPair, std::pair<int, int>& coordPair, std::pair<int, int>& window)
{
	int x0 = coordPair.first,
		y0 = coordPair.second;

	int wx = window.first,
		wy = window.second;

	IntMap::Uptr& m1 = imPair.first;
	IntMap::Uptr& m2 = imPair.second;

	// Row and column counts of CCF
	int ccfRows = ccf->rows(),
		ccfCols = ccf->cols(),
		imRows  = wy,
		imCols  = wx,
		mIndex, nIndex,
		mOffset = imRows + (int) floor((ccfRows/2.0 - imRows)),
		nOffset = imCols + (int) floor((ccfCols/2.0 - imCols)),
		mMin, mMax, nMin, nMax,
		iMin, iMax, jMin, jMax,
		xOff = x0 - (int) (wx / 2.0) + 1,
		yOff = y0 - (int) (wy / 2.0) + 1;

	// Product bit counter 
	double  bitProd,
			m1Avg, m2Avg,
			denom1, denom2;
	
	// m and n are the row and column of the ccf (respectively)
	mMin = mOffset > 0 ? -mOffset : 0;
	nMin = nOffset > 0 ? -nOffset : 0;
	mMax = mOffset < ccfRows ? ccfRows - mOffset : ccfRows;
	nMax = nOffset < ccfCols ? ccfCols - nOffset : ccfCols;

	for (int m = mMin ; m < mMax; m++) {
		mIndex = m + mOffset; 
		for (int n = nMin; n < nMax; n++) {
		nIndex = n + nOffset;;
		
			// Limits of the overlapping regions
			jMin = m < 0 ? -m : 0;
			jMax = m + imRows > imRows ? imRows - m : imRows;
			iMin = n < 0 ? -n : 0;
			iMax = n + imCols > imCols ? imCols - n : imCols;

			// Reset all counters
			m1Avg = m2Avg = bitProd = denom1 = denom2 = 0.0;

			// Calculate the overlapping segment averages
			for (int j = jMin; j < jMax; j++) {
				for (int i = iMin; i < iMax; i++) {
					m1Avg += (double) m1->getElem(j + yOff, i + xOff);
					m2Avg += (double) m2->getElem(j + yOff + m, i + xOff+ n);
				}
			}

			// Divide by the number of elements in each overlapping region
			m1Avg /= (double) ((iMax - iMin) * (jMax - jMin));
			m2Avg /= (double) ((iMax - iMin) * (jMax - jMin));

			// For each element in the overlapping regions sum the piecewise products of the elements minus the region average. Also calculate the two denominators
			for (int j = jMin; j < jMax; j++) {
				for (int i = iMin; i < iMax; i++) {
					
					bitProd += ((double) m1->getElem(j + yOff, i + xOff) - m1Avg) * ((double) m2->getElem( j + yOff + m, i + xOff + n) - m2Avg);
					denom1 += ((double) m1->getElem(j + yOff, i + xOff) - m1Avg) * ((double) m1->getElem(j + yOff, i + xOff) - m1Avg);
					denom2 += ((double) m2->getElem(j + yOff +  m, i + xOff + n) - m2Avg) * ((double) m2->getElem(j + yOff + m, i + xOff + n) - m2Avg);
				}
			}
			// Put everything in and do not divide by zero
			ccf->setElem(mIndex, nIndex, denom1 > 0 && denom2 > 0 ? bitProd / sqrt(denom1 * denom2) : -1.0);
		}
	}
}
#endif
