#include "PivPoint.hpp"

namespace PivEng {

PivPoint::PivPoint(int xCoord, int yCoord, PivOptions& options) :
	m_ccf(std::make_shared<CCF>(options.winHeight() + 1, options.winWidth() + 1)),
	m_peaksVector(options.numPeaks()),
	m_dispsVec(options.numPeaks()),
	m_i(xCoord),
	m_j(yCoord)
{}

CCF* PivPoint::get_ccf()
{
	return m_ccf.get();
}

dv* PivPoint::getDv()
{
	/* Search through the calculated displacements for the first valid one.
	 * If a valid displacement is found, return a pointer to a new displacement 
	 * vector object. If no valid displacements are found return a null pointer */
	auto d = std::find_if(m_dispsVec.begin(), m_dispsVec.end(), [](auto& d){ return d.valid; });

	if (d != m_dispsVec.end()) {
		return new dv((double) m_i, (double) m_j, d->u, d->v);
	} else {
		return nullptr;
	}
}

Peak::PeaksVec& PivPoint::peaks()
{
	return m_peaksVector;
}

Disp::DispVec& PivPoint::dispsVec()
{
	return m_dispsVec;
}


Disp& PivPoint::primaryDisp()
{
	// auto d = std::find_if(m_dispsVec.begin(), m_dispsVec.end(), [](auto& d){ return d.valid; });
    //
	// if ( d != m_dispsVec.end() ) {
	// 	std::cout << "Valid found" << std::endl;
	// 	return *d;
	// } else {
	// 	std::cout << "No valid" << std::endl;
	// 	return *d;
	// }
	return m_dispsVec[0];
}

void PivPoint::printPeaks() 
{
	auto i(0);
	std::cout << "Peak#\ti\tj\tValue\tValid" << std::endl;
	for(auto& p : m_peaksVector)
		std::cout << (i++) << "\t" << p.i - m_ccf->offsetX() << "\t" << p.j - m_ccf->offsetY()
			<< "\t" 
			<< std::setprecision(4) << std::fixed
			<<  p.val << "\t" << p.valid << std::endl;

}

void PivPoint::printDisps() 
{
	auto i(0);
	std::cout << "Disp\tu\tv\tValid" << std::endl;
	for(auto& d : m_dispsVec)
		std::cout << (i++) << "\t" << std::setprecision(4) << std::fixed << d.u << "\t" << d.v
			<< "\t" << d.valid << std::endl;

}

void PivPoint::printToOfstream(std::ofstream& file)
{
	if (m_dispsVec[0].valid) {
	file << m_i << "\t" << m_j << "\t"
		 << m_dispsVec[0].u << "\t"
		 << m_dispsVec[0].v << "\t"
		 << std::endl;
	}
}
		

void PivPoint::set_xCoord(int x)
{
	m_i = x;
}

void PivPoint::set_yCoord(int y)
{
	m_j = y;
}

void PivPoint::set_coords(std::pair<int, int>& coords)
{
	m_i = coords.first;
	m_j = coords.second;
}


int PivPoint::x()
{
	return m_i;
}

int PivPoint::y()
{
	return m_j;
}

PivPoint::~PivPoint() {};
}
