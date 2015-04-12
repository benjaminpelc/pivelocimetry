#include "SubPix.hpp"

namespace PivEng {

void SubPixel::gauss(const Mat2<double>& ccf, const Peak::PeaksVec& peaks, Disp::DispVec& displacements)
{
	// std::cout << "In Gauss, eww!" << std::endl;
	uint_fast16_t i, j;
	double dx, dy;

	/* Offset value make central row and column the zero displacement */
	uint_fast16_t cols = ccf.cols(),
		offsetX = ccf.offsetX(),
		offsetY = ccf.offsetY();

	auto e0  = ccf.begin(),
		 e = e0;

	/* Calculate displacements for each peak */
	auto p = peaks.begin();
	auto d = displacements.begin();

	while ( p != peaks.end() && p->valid ){
		i = p->i;
		j = p->j;

		/* Pointer to correlation peak value */
		e  = e0 + j * cols + i;
		// std::cout << e << "\t" << *e << std::endl;
		/* Calculate x and y subpixel displacements */
		dx = i + gauss3((e - 1), e, (e + 1) ) - offsetX; 
		dy = j + gauss3((e - cols), e, (e + cols)) - offsetY; 

		/* A number is only not equal to itself iff it is a NaN. If the peak is invalid, 
		 * assume subsequent peaks are also invalid. Invalidity is caused by taking the 
		 * logarithm of a negative correlation function element. Is it logical to think
		 * if a peak is invalid then all subsequent peaks will be invalid?  */
		if ( dx != dx || dy != dy ) {
			break;
		} else {
			d->set_displacement(dx, dy, true);
			p++, d++;
		}
	}
}

double SubPixel::gauss3(const double* a, const double* b, const double* c)
{
	return  (log(*a) - log(*c)) / ( 2*log(*a) - 4*log(*b) + 2*log(*c)); 
}
}
