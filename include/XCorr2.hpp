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

void x_corr_n_2(Mat2<double> &ccf, const int imageCols,
                const uint16_t *im1pixel, const uint16_t *im2pixel,
                const int col, const int row);
}

#endif
