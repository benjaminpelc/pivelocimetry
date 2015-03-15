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

void CCF::findPeaks(Peak::PeaksVec& pv, int maxDisp)
{
	maxDisp = floor(_m / 2) - maxDisp;
	double maxVal = _mat[maxDisp][maxDisp];
	double cVal = _mat[maxDisp][maxDisp];
	double preMax = 999999999.9; /* something silly big for first iteration */
	int jC = maxDisp, iC = maxDisp;

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
				}
			}
		}
		peak.set_val(maxVal);
		peak.set_iCoord(iC);
		peak.set_jCoord(jC);
		preMax = maxVal;
		maxVal = _mat[maxDisp][maxDisp];
		std::cout << "(i, j, val) = (" << peak.get_iCoord() << ",\t" << peak.get_jCoord() << ",\t" << peak.get_val() << ")" << std::endl;
	}

	// pv[0].set_val(maxVal);
	// pv[0].set_jCoord(jC); pv[0].set_iCoord(iC);
}

#endif
