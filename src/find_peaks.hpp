#ifndef BPPIV_FIND_CCF_PEAKS_H
#define BPPIV_FIND_CCF_PEAKS_H

#include <algorithm>

#include "Ccf.hpp"
#include "Peak.hpp"

namespace PivEng {

bool is_local_peak(const double* p, const unsigned int m_cols);

bool in_valid_range(const double value, const double min, const double max);

void find_ccf_peaks(
		std::vector<Peak>& peaks_container,
		const CCF& ccf,
		const int max_disp);
}

#endif
