#include "Ccf.hpp"

namespace PivEng {


	/* Constructor:
 	 * Must be passed with row and column number specifiers.
 	 * Calls default Matrix2<double> constructor.
 	 * Initialize all values to -1.0  */
	CCF::CCF(unsigned int rows, unsigned int cols) : 
		Mat2<double>(rows, cols, -1.0),
		m_offsetX(floor ((cols - 1) / 2)),
		m_offsetY(floor ((rows - 1) / 2))
	{
	}

	/* Destructor:
 	 * Nothing exciting here, all memory is deallocated inside Matrix2 
 	 * parent class */
	CCF::~CCF() {}

	int CCF::offsetX()
	{
		return m_offsetX;
	}

	int CCF::offsetY()
	{
		return m_offsetY;
	}

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
		maxDisp = floor(m_rows / 2) - maxDisp + 1;

		double maxVal = 0.0, /* Something silly big negative */
		   	   // currentElem   = m_mat[maxDisp][maxDisp], /* Current CCF value, set to initial value */
		   	   currentElem   = *(m_begin + m_cols * maxDisp + maxDisp), /* Current CCF value, set to initial value */
	       	   preMax = BIG_DOUBLE; /* something silly big for first iteration */

		/* coords of peack value, set to initial coord */
		int jC = maxDisp,
			iC = maxDisp,
			jMax = m_rows - maxDisp,
			iMax = m_cols - maxDisp,
			idx;
		
		/* Be cynical, do not believe any peak to be automatically valid */
		bool valid = false;
		auto inValidRange = [&]() -> bool { return currentElem > maxVal && currentElem < preMax; };

		/* iterate through each of the number of peaks specified to search for */
		for (auto& peak : pv) {
			/* Loop through each point in the CCF matrix.
		 	 * Using raw loop as index values as well as element values are required*/
			for (int j = maxDisp; j < jMax; j++) {
				for (int i = maxDisp; i < iMax; i++) {
					idx = m_cols * j + i;
					currentElem = m_mat[idx];
					/* Check to see if point is larger than current max but smaller than 
				 	 * the previous peak. Check surrounding values to make sure it is in 
				 	 * fact a peak value */
					// if ( inRange(currentElem, maxVal, preMax) && isLocalPeak(idx) ) {
					if ( inValidRange() && isLocalPeak(idx) ) {
						/* All things being good, update the current peak value, coords
					 	 * and validity. These will be used if no other peak is found */
						maxVal = currentElem;
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
		
			// std::cout << "(i, j, val, legit) = (" << peak.get_iCoord() << ",\t" << peak.get_jCoord() << ",\t" << peak.val() << ",\t" << peak.valid() << ")" << std::endl;
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
     	 * return m_mat[m_cols * j + i] > m_mat[m_cols * j + i-1] &&
     	 *        m_mat[m_cols * j + i] > m_mat[m_cols * j + i+1] &&
	 	 *        m_mat[m_cols * j + i] > m_mat[m_cols * (j-1) + i] &&
	 	 *        m_mat[m_cols * j + i] > m_mat[m_cols * (j+1) + i];
     	 */

    	/* Dangerous as is, can access elements out of range */
    	// return m_mat[i] > m_mat[i - m_cols] &&
        //     	m_mat[i] > m_mat[i + m_cols] &&
	    //     	m_mat[i] > m_mat[i + 1] &&
	    //     	m_mat[i] > m_mat[i - 1];

	    auto * p = &m_mat[i];
    	return *(p) > *(p - m_cols) &&
            	*(p) > *(p + m_cols) &&
	        	*(p) > *(p + 1) &&
	        	*(p) > *(p - 1);
	}

}
