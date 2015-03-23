/* Struct Peak 
 *
 * Container class for a correlation function peak,
 * Contains two integer correlation function coordinates and 
 * the  correlation function value at those coordinates. 
 * Contains a validity flag which can be switched on/off as 
 * appropriate */

#ifndef BPPIB_PIV_ENGINE_PEAK_H
#define BPPIB_PIV_ENGINE_PEAK_H

#include <vector>

namespace PivEng {

	struct Peak
	{
		typedef std::vector<Peak> PeaksVec;

		Peak() : i(-1), j(-1), val(-1.0), valid(false) {};
		Peak(int ic, int jc, double v, bool torf) : i(ic), j(jc), val(v), valid(torf) {};
		~Peak() {};

		void setPeak(int ic, int jc, double v, bool torf) { i = ic; j = jc; val = v; valid = torf; };

		int i, j; 
		double val;
		bool valid; 
	};
}
#endif
