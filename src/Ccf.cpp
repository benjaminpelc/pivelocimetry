#include "Ccf.hpp"

namespace PivEng {

/* Constructor:
 * Must be passed with row and column number specifiers.
 * Calls default Matrix2<double> constructor.
 * Initialize all values to -1.0  */
CCF::CCF(unsigned int rows, unsigned int cols) : 
	Mat2<double>(rows, cols, -1.0) {}

/* Destructor:
 * Nothing exciting here, all memory is deallocated inside Matrix2 
 * parent class */
CCF::~CCF() {}

int CCF::offsetX() const { return (m_cols - 1) / 2; }

int CCF::offsetY() const { return (m_rows - 1) / 2; }

void CCF::findPeaks(Peak::PeaksVec& pv, int maxDisp) const
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
	maxDisp = floor(m_rows / 2) - maxDisp + 1;

	double maxVal = 0.0, /* Something silly big negative */
	       preMax = BIG_DOUBLE; /* something silly big for first iteration */
	double* currentElemPtr = nullptr;

	/* coords of peack value, set to initial coord */
	int j(0), i(0),
		jC = maxDisp,
		iC = maxDisp,
		jMax = m_rows - maxDisp,
		iMax = m_cols - maxDisp;
	
	/* Be cynical, do not believe any peak to be automatically valid */
	bool valid = false;
	auto * cp = &m_mat[0];
	auto inValidRange = [&]() -> bool { return *currentElemPtr > maxVal && *currentElemPtr < preMax; };

	/* iterate through each of the number of peaks specified to search for */
	for (auto& peak : pv) {
		/* Loop through each point in the CCF matrix.
		 * Using raw loop as index values as well as element values are required*/
		for (j = maxDisp; j < jMax; j++) {
			for (i = maxDisp; i < iMax; i++) {
				currentElemPtr = cp + m_cols * j + i;
				
				/* Check to see if point is larger than current max but smaller than 
				 * the previous peak. Check surrounding values to make sure it is in 
				 * fact a peak value */
				if ( inValidRange() && isLocalPeak(currentElemPtr) ) {
					/* All things being good, update the current peak value, coords
					 * and validity. These will be used if no other peak is found */
					maxVal = *currentElemPtr;
					jC = j;
					iC = i;
					valid = true;
				}
			}
		}
		/* Once valid peaks have stopped turning up we really should not bother
		 * to continue, so we will break out of the peak vector loop */
		/** to continue, so we will break out of the peak vector loop */
		if (!valid) break;

		/* punch in the values for this peak */
		peak.setPeak(iC, jC, maxVal, valid);

		/* Set preMax to the current peak max, funture peaks will have to be
		 * smaller than this. Also set maxVal back to something silly neg */
		preMax = maxVal;
		maxVal = 0.0;
		
		valid = false; /* reset validity to false for next round */
	
		/* std::cout << "(i, j, val, legit) = (" << peak.get_iCoord() << ",\t" << peak.get_jCoord() << ",\t" << peak.val() << ",\t" << peak.valid() << ")" << std::endl; */
	}
}

/* bool CCF::isLocalPeak(int j, int i) */
bool CCF::isLocalPeak(double* p) const
{
	/* Returns true if the point (i,j) has greater 
	 * value than the four surrounding points */
	/* auto * p = &m_mat[i]; */
    return *(p) > *(p - m_cols) &&
            *(p) > *(p + m_cols) &&
	        *(p) > *(p + 1) &&
	        *(p) > *(p - 1);
}

}
