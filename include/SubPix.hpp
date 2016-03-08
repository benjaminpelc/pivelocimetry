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

void gauss(const Mat2<double> &ccf, const Peak::PeaksVec &peaks,
           Disp::DispVec &displacements);
double gauss3(const double *a, const double *b, const double *c);
}

#endif
