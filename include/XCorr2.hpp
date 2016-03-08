// PivVector.hpp
// Header for x_corr_n_2. Calculate the cross-correlation function for a
// of images.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef XCORR2_H
#define XCORR2_H

#include "../lib/Mat2.hpp"
#include "IntMap.hpp"

#include <cmath>
#include <algorithm>

namespace PivEng {

using PairD = std::pair<double, double>;

// x_corr_n_2
// Calculate the normalised cross-correlation function for a pair of
// two-dimesnional integer maps.
//  -- ccf : 2D double matrix to store the resulting cross-correlation function.
//  -- imageCols : width in pixels of the source images.
//  -- im1pixel, im2pixel : pointers to the first elements of each of the source
//                          images.
//  -- col, row : row and column coordinates of the centre of the interrogation
//                window sub-region. 
void x_corr_n_2(Mat2<double> &ccf, const int imageCols,
                const uint16_t *im1pixel, const uint16_t *im2pixel,
                const int col, const int row);
}

#endif
