#ifndef SUBPIXEL_FITTERS_H
#define SUBPIXEL_FITTERS_H

#include "Ccf.hpp"
#include "Peak.hpp"
#include "Disp.hpp"

#include <vector>
#include <memory>

namespace PivEng {

class SubPixel
{
	public:
		static void gauss(CCF& ccf, Peak::PeaksVec& peaks, Disp::DispVec& displacements);
		// static double gauss3(const double a, const double b, const double c);
		static double gauss3(const double* a, const double* b, const double* c);
	private:
		
};


}

#endif
