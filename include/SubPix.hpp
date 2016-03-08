// find_peaks.hpp
// Header file for stand-alone functions for calculating the sub-pixel location
// of a gaussian curve passing through three equally spaced points.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef SUBPIXEL_FITTERS_H
#define SUBPIXEL_FITTERS_H

#include "../lib/Mat2.hpp"

#include "Peak.hpp"
#include "Disp.hpp"

#include <vector>
#include <memory>

namespace PivEng {

// gauss
// Calculate sub-pixel displacement components for each of the peaks in peaks
// for the correlation function ccf.
//  -- ccf : 2D cross-correlation function to calculate peak sub-pixel
//           displacements from.
//  -- peaks : Vector containing the locations of cross-correlation peaks.
//  -- displacements : Vector to store calculated displacements with sub-pixel
//                     components.
void gauss(const Mat2<double> &ccf, const Peak::PeaksVec &peaks,
           Disp::DispVec &displacements);

// gauss3
// Calculate the sub-pixel peak location of the gausian curve passing through
// points a, b and c. If the denominator is undefined or equal to zero, return
// a NAN.
double gauss3(const double *a, const double *b, const double *c);
}

#endif
