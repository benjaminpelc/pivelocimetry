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
		static void gauss(std::shared_ptr<CCF>& ccf, Peak::PeaksVec& peaks, Displacement::DispVec& displacements);
	private:
		
};

void SubPixlel::gauss(std::shared_ptr<CCF>& ccf, Peak::PeaksVec& peaks, Displacement::DispVec& displacements)
{
	// std::cout << "In Gauss, eww!" << std::endl;

	int i, j;
	double dx, dy;

	/* Calculate displacements for each peak */
	auto p = peaks.begin();
	auto d = displacements.begin();
	while ( p->get_isValid() && p != peaks.end() && d != displacements.end() ){
		// std::cout << "In Gauss, peak locs: " << p->get_iCoord() << std::endl;
		i = p->get_iCoord();
		j = p->get_jCoord();
		
		dx = i + ( log(ccf->get_elementAt(j, i-1)) - log(ccf->get_elementAt(j, i + 1))    ) /
			( 2*log(ccf->get_elementAt(j, i-1)) - 4*log(ccf->get_elementAt(j,i)) + 2*log(ccf->get_elementAt(j,i+1)))
			- floor(ccf->get_numCols()/2);

		dy = j + ( log(ccf->get_elementAt(j-1, i)) - log(ccf->get_elementAt(j+1, i))    ) /
			( 2*log(ccf->get_elementAt(j-1, i)) - 4*log(ccf->get_elementAt(j,i)) + 2*log(ccf->get_elementAt(j+1,i)))
			- floor(ccf->get_numRows()/2);

		/* A number is only not equal to itself iff it is a NaN */
		if ( !(dx != dx || dy != dy) )
		{
			// std::cout << "dx: " << dx << ", dy: "<< dy << std::endl;
			/* put the necessary bits in */
			d->set_isValid(true);
			d->set_displacementX(dx);
			d->set_displacementY(dy);
		} else {
			break;
		}
		p++;
		d++;
	}
}

#endif
