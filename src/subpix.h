#ifndef SUBPIXEL_FITTERS_H
#define SUBPIXEL_FITTERS_H

#include "ccf.h"
#include "peak.h"
#include "displacement.h"

#include <vector>
#include <memory>

class SubPixlel
{
	public:
		static void gauss(CCF::Sptr& ccf, Peak::PeaksVec& peaks, Displacement::DispVec& displacements);
	private:
		
};

void SubPixlel::gauss(CCF::Sptr& ccf, Peak::PeaksVec& peaks, Displacement::DispVec& displacements)
{
	// std::cout << "In Gauss, eww!" << std::endl;

	int i, j;
	double dx, dy;

	/* Offset value make central row and colum the zero displacent */
	int offsetX = floor(ccf->cols() / 2),
		offsetY = floor(ccf->rows() / 2);

	/* Calculate displacements for each peak */
	auto p = peaks.begin();
	auto d = displacements.begin();
	while ( p->valid() && p != peaks.end() && d != displacements.end() ){
		// std::cout << "In Gauss, peak locs: " << p->get_iCoord() << std::endl;
		i = p->get_iCoord();
		j = p->get_jCoord();

		/* Calculate x and y subpixel displacements, this is messy. Consider refactoring into 
		 * numerator, denominator and offset as:
		 * dx = i + numer / denom - offset */
		dx = i + ( log(ccf->getElem(j, i-1)) - log(ccf->getElem(j, i + 1))    ) /
			(
				 2*log(ccf->getElem(j, i-1)) -
				 4*log(ccf->getElem(j,i)) +
				 2*log(ccf->getElem(j,i+1))
			) - offsetX; 

		dy = j + ( log(ccf->getElem(j-1, i)) - log(ccf->getElem(j+1, i))    ) /
			(
				 2*log(ccf->getElem(j-1, i)) -
				 4*log(ccf->getElem(j,i)) +
				 2*log(ccf->getElem(j+1,i))
			) - offsetY;

		/* A number is only not equal to itself iff it is a NaN. If the peak is invalid, 
		 * assume subsequant peaks are also invalid. Invalidity is caused by taking the 
		 * logarithm of a negative correlation function element. Is it logical to think
		 * if a peak is invalid then all subsequant peaks will be invalid? 
		 *
		 * This is messy, remove the 
		 * double negative */
		if ( (dx == dx && dy == dy) )
		{
			// std::cout << "dx: " << dx << ", dy: "<< dy << std::endl;
			/* put the necessary bits in */
			d->setValid(true);
			d->setX(dx);
			d->setY(dy);
		} else {
			break;
		}

		/* Advance the peak and displacement vector iterators */
		p++, d++;
	}
}

#endif
