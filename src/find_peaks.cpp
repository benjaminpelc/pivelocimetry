#include "find_peaks.hpp"

namespace PivEng {

inline bool is_local_peak(const double *p, const unsigned int ccf_cols) {
  /* Returns true if the point (i,j) has greater
   * value than the four surrounding points */
  /* auto * p = &m_mat[i]; */
  auto p_0 = *p;
  return p_0 > *(p - ccf_cols) && p_0 > *(p + ccf_cols) && p_0 > *(p + 1) &&
         p_0 > *(p - 1);
}

inline bool in_valid_range(const double value, const double min,
                           const double max) {
  return value > min && value < max;
}

void find_ccf_peaks(std::vector<Peak> &peaks_container, const Mat2<double> &ccf,
                    const int max_disp) {
  /* FindPeaks
   * Find peaks in the correlation function. Pass a vector of peak objects to
   *store
   * the results. The number of peaks searched for is dictated by the length of
   * the peak vector passed as an argument.
   *
   * ToDo
   * 1) Add independent maximum x and y displacements */

  const unsigned ccf_rows = ccf.rows();
  const unsigned ccf_cols = ccf.cols();

  const unsigned j_min = ccf_rows / 2 - max_disp + 1;
  const unsigned i_min = ccf_cols / 2 - max_disp + 1;
  const unsigned j_max = ccf_rows - j_min;
  const unsigned i_max = ccf_cols - i_min;

  // double current_max = 0.0, /* Something silly big negative */
  double previous_max =
      9999999999.9; /* something silly big for first iteration */
  double *currentElemPtr = nullptr;

  /* coords of peak value, set to initial coord */
  unsigned j{0}, i{0};

  /* Be cynical, do not believe any peak to be automatically valid */
  auto *const ccf_begin = ccf.begin();

  auto temp_peak = Peak();

  /* iterate through each of the number of peaks specified to search for */
  for (auto &peak : peaks_container) {
    /* Loop through each point in the CCF matrix.
     * Using raw loop as index values as well as element values are required*/
    for (j = j_min; j <= j_max; j++) {
      for (i = i_min; i <= i_max; i++) {
        currentElemPtr = ccf_begin + ccf_cols * j + i;
        if (in_valid_range(*currentElemPtr, temp_peak.val, previous_max) &&
            is_local_peak(currentElemPtr, ccf_cols)) {
          temp_peak.setPeak(i, j, *currentElemPtr, true);
        }
      }
    }
    /* Once valid peaks have stopped turning up we really should not bother
     * to continue, so we will break out of the peak vector loop */
    /** to continue, so we will break out of the peak vector loop */
    if (!temp_peak.valid) {
      break;
    } else {
      peak = temp_peak;
      previous_max = temp_peak.val;
      temp_peak.val = 0.0;
      temp_peak.valid = false; /* reset validity to false for next round */
    }
  }
}
}
