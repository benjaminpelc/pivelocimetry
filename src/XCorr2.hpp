#ifndef XCORR2_H
#define XCORR2_H

/*
 * XCorr2.h
 * 2D cross-correlation functions
 *
 */

#include "../lib/Mat2.hpp"
#include "IntMap.hpp"

#include <cmath>
#include <algorithm>

namespace PivEng {

	class XCorr2
	{
		public:
			typedef std::pair<int, int> IntPair;
			typedef std::pair<double, double> DoublePair;

			static void xCorr2n(Mat2<double>& ccf,
				const int imageCols,
				const uint16_t* im1pixel,
				const uint16_t* im2pixel,
				const int col,
				const int row);
		private:
	};

}

#endif
