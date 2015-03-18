/* Class CCF 
 * Correlation function matrix for storing two dimensional cross-
 * correlation values. 
 * Inherits from Matrix2<double>
 * Includes method for locating peaks */

#ifndef CCF_H
#define CCF_H

#include "matrix2.h"
#include "../tests/Mat2.h"
#include "peak.h"

// class CCF : public Matrix2<double>
class CCF : public Mat2<double>
{
	public:
		typedef std::shared_ptr<CCF> Sptr;

		CCF(unsigned int rows, unsigned int cols);
		~CCF();

		void findPeaks(Peak::PeaksVec& pv, int maxDisp);
		bool isLocalPeak(int j);

	private:	
		const double BIG_DOUBLE = 9999999999.9;
		bool inRange(double subject, double minimum, double maximum);
};

/* Constructor:
 * Must be passed with row and column number specifiers.
 * Calls default Matrix2<double> constructor.
 * Removed initializing elements to -1.0 for efficiency increase. Be
 * careful though, perhaps add a validity flag. */
// CCF::CCF(unsigned int rows, unsigned int cols) : Matrix2<double>(rows, cols) {}
CCF::CCF(unsigned int rows, unsigned int cols) : Mat2<double>(rows, cols) {}

/* Destructor:
 * Nothing exciting here, all memory is deallocated inside Matrix2 
 * parent class */
CCF::~CCF() {}

void CCF::findPeaks(Peak::PeaksVec& pv, int maxDisp)
{
	/* FindPeaks
 	 * Find peaks in the correlation function. Pass a vector of peak objects to store
 	 * the results. The number of peaks searched for is dictated by the length of
 	 * the peak vector passed as an argument.
 	 *
 	 * ToDo
 	 * 1) Add independent maximum x and y displacements */

	/* Define the boundary of the correlation function search region
	 * 1) pretty sure this needs 1 subtracting
	 * 2) Add check to make sure maxDisp does not exceed CCF boundaries */
	maxDisp = floor(_rows / 2) - maxDisp;

	double maxVal = -BIG_DOUBLE, /* Something silly big negative */
		   // currentElement   = _mat[maxDisp][maxDisp], /* Current CCF value, set to initial value */
		   currentElement   = _mat[_cols * maxDisp + maxDisp], /* Current CCF value, set to initial value */
	       preMax = BIG_DOUBLE; /* something silly big for first iteration */

	/* coords of peack value, set to initial coord */
	int jC = maxDisp,
		iC = maxDisp,
		idx;
	
	/* Be cynical, do not believe any peak to be automatically valid */
	bool valid = false;

	/* iterate through each of the number of peaks specified to search for */
	for (auto& peak : pv) {
		/* Loop through each point in the CCF matrix.
		 * Using raw loop as index values as well as element values are required*/
		for (int j = maxDisp; j < _rows - maxDisp; j++) {
			for (int i = maxDisp; i < _cols - maxDisp; i++) {
				idx = _cols * j + i;
				currentElement = _mat[idx];
				/* Check to see if point is larger than current max but smaller than 
				 * the previous peak. Check surrounding values to make sure it is in 
				 * fact a peak value */
				if ( inRange(currentElement, maxVal, preMax) && isLocalPeak(idx) ) {
					/* All things being good, update the current peak value, coords
					 * and validity. These will be used if no other peak is found */
					maxVal = currentElement;
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

		/* Set preMax to the current peak max, funture peaks will have to be
		 * smaller than this. Also set maxVal back to something silly neg */
		preMax = maxVal;
		maxVal = -BIG_DOUBLE;
		
		/* Once valid peaks have stopped turning up we really should not bother
		 * to continue, so we will break out of the peak vector loop */
		/** to continue, so we will break out of the peak vector loop */
		if (!valid) break;
		valid = false; /* reset validity to false for next round */
	
		// std::cout << "(i, j, val, legit) = (" << peak.get_iCoord() << ",\t" << peak.get_jCoord() << ",\t" << peak.get_val() << ",\t" << peak.get_isValid() << ")" << std::endl;
	}
}

bool CCF::inRange(double subject, double minimum, double maximum)
{
	/* Returns true if the subject is greater than minimum and 
	 * less than maximum 
	 *
	 * todo 
	 * Template this into a general function */
	return subject > minimum && subject < maximum;
}

// bool CCF::isLocalPeak(int j, int i)
bool CCF::isLocalPeak(int i)
{
	/* Returns true if the point (i,j) has greater 
	 * value than the four surrounding points */
    /*
     * return _mat[_cols * j + i] > _mat[_cols * j + i-1] &&
     *        _mat[_cols * j + i] > _mat[_cols * j + i+1] &&
	 *        _mat[_cols * j + i] > _mat[_cols * (j-1) + i] &&
	 *        _mat[_cols * j + i] > _mat[_cols * (j+1) + i];
     */

    /* Dangerous as is, can access elements out of range */
    return _mat[i] > _mat[i - _cols] &&
            _mat[i] > _mat[i + _cols] &&
	        _mat[i] > _mat[i + 1] &&
	        _mat[i] > _mat[i - 1];
}

#endif
