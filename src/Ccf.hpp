/* Class CCF 
 * Correlation function matrix for storing two dimensional cross-
 * correlation values. 
 * Inherits from Matrix2<double>
 * Includes method for locating peaks */

#ifndef CCF_H
#define CCF_H

#include "../lib/Mat2.hpp"
#include "Peak.hpp"
#include <cmath>

namespace PivEng {

	class CCF : public Mat2<double>
	{
		public:
			using Sptr =  std::shared_ptr<CCF>;

			CCF(unsigned int rows, unsigned int cols);
			~CCF();

			void findPeaks(Peak::PeaksVec& pv, int maxDisp) const;
			bool isLocalPeak(double *  j) const;

		private:	
	};

}

#endif
