#ifndef CCF_H
#define CCF_H

#include "matrix2.h"
#include "peak.h"

class CCF : public Matrix2<double>
{
	public:
		CCF(unsigned int rows, unsigned int cols);
		~CCF();

		void findPeaks(Peak::PeaksVec& pv, int maxDisp);

	private:	
					
};

CCF::CCF(unsigned int rows, unsigned int cols) : Matrix2<double>(rows, cols, -1.0) {}

CCF::~CCF() {}

/* FindPeaks
 * Find peaks in the correlation function. Pass a vector of peak objects to store
 * the results. The number of peaks searched for is dictated by the length of
 * the peak vector passed as an argument 
 *
 * ToDo
 * 1) Add independent maximum x and y displacements
 * 2) Add isValid bool, set to true if a peak is detected, leave as false if 
 * 	  no peak is found */
void CCF::findPeaks(Peak::PeaksVec& pv, int maxDisp)
{
	maxDisp = floor(_m / 2) - maxDisp;
	double maxVal = -9999999.9; /* Something silly big negative */
	double cVal = _mat[maxDisp][maxDisp]; /* Current CCF value, set to initial value */
	double preMax = 999999999.9; /* something silly big for first iteration */
	int jC = maxDisp, iC = maxDisp; /* coords of peack value, set to initial coord */
	bool valid = false;

	/* iterate through each of the number of peaks specified to search for */
	for (auto& peak : pv) {
		/* Loop through each point in the CCF matrix */
		for (int j = maxDisp; j < _m - maxDisp; j++) {
			for (int i = maxDisp; i < _n - maxDisp; i++) {
				cVal = _mat[j][i];
				/* Check surrounding values to make sure it is in fact a peak value */
				if (cVal > maxVal && cVal < preMax &&
						cVal > _mat[j][i-1] && cVal > _mat[j][i+1] && cVal > _mat[j-1][i] && cVal > _mat[j+1][i] )
				{
					maxVal = cVal;
					jC = j;
					iC = i;
					valid = true;
				}
			}
		}

		/* punch in the values for this peak */
		peak.set_val(maxVal);
		peak.set_iCoord(iC);
		peak.set_jCoord(jC);
		peak.set_isValid(valid);
		preMax = maxVal;
		maxVal = -99999999.9;
		
		/* Once valid peaks have stopped turning up we really should not bother
		 * to continue, so we will break out of the peak vector loop */
		if (!valid) break;
		valid = false; /* reset validity to false for next round */
	
		// std::cout << "(i, j, val, legit) = (" << peak.get_iCoord() << ",\t" << peak.get_jCoord() << ",\t" << peak.get_val() << ",\t" << peak.get_isValid() << ")" << std::endl;
	}

	// pv[0].set_val(maxVal);
	// pv[0].set_jCoord(jC); pv[0].set_iCoord(iC);
}

#endif
