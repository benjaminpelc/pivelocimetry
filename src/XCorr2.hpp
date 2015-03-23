#ifndef XCORR2_H
#define XCORR2_H

/*
 * XCorr2.h
 * 2D cross-correlation functions
 *
 */

#include "Ccf.hpp"
#include "IntMap.hpp"

#include <cmath>
#include <algorithm>

namespace PivEng {

	class XCorr2
	{
		public:
			typedef std::pair<int, int> IntPair;
			typedef std::pair<double, double> DoublePair;

			static void xCorr2n(CCF& ccf, IntMap::Pair& imPair, IntPair& coordPair);
		private:
	};

}

#endif
