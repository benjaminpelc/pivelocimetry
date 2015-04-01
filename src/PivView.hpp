#ifndef BPPIV_PIV_VIEW_H
#define BPPIV_PIV_VIEW_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "PivPoint.hpp"

class PivView
{
	public:
		PivView(PivEng::PivPoint::PivPointVec& vs);
		~PivView();

	private:
		PivEng::PivPoint::PivPointVec& m_pivPointVec;
		
};


#endif
