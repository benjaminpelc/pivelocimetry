// find_peaks.hpp
// Header file for correlation function peak finding functions.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_FIND_CCF_PEAKS_H
#define BPPIV_FIND_CCF_PEAKS_H

#include <algorithm>

#include "../lib/Mat2.hpp"
#include "Peak.hpp"

namespace PivEng {

// is_local_peak
// For a two dimentional array of doubles, determine whether each element is a
// local maxima (i.e. is this point greater than the four surrounding points?)
//  -- p : pointer to the first element of the array
//  -- m_cols : number of array columns
inline bool is_local_peak(const double *p, const unsigned int m_cols);

// in_valid_range
// Does a value lie within a specified range? Non-inclusive of limits, greater
// than and less than and not greater than or equal to or less than or equal to.
//
// N.B. : This should probably be moved to a utility class/namespace.
inline bool in_valid_range(const double value, const double min,
                           const double max);

// find_ccf_peaks
// Find peaks in a cross-correlation function
//  -- peaks_container : A vector containing Peak objects to store peak data
//                       for the given cross-correlation function.
//  -- ccf : cross-correlation function from which to find peaks.
//  -- max_disp : The maximum pixel displacement from the centre of the
//                cross-correlation function to search for peaks in.
void find_ccf_peaks(std::vector<Peak> &peaks_container, const Mat2<double> &ccf,
                    const int max_disp);
}

#endif
