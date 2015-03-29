#include "PivPoint.hpp"

namespace PivEng {

PIVPoint::PIVPoint(int xCoord, int yCoord, PivOptions& options) :
	m_ccf(std::make_shared<CCF>(options.winHeight() + 1, options.winWidth() + 1)),
	m_peaksVector(options.numPeaks()),
	m_dispsVec(options.numPeaks()),
	m_i(xCoord),
	m_j(yCoord)
{}

CCF* PIVPoint::get_ccf()
{
	return m_ccf.get();
}

dv PIVPoint::getDv()
{
	// auto d = std::find_if(m_dispsVec.begin(), m_dispsVec.end(), [](auto& d){ return d.valid; });


	return dv();
	// return dv((double) m_i, (double) m_j, d.u, d.v);
}

Peak::PeaksVec& PIVPoint::peaks()
{
	return m_peaksVector;
}

Disp::DispVec& PIVPoint::dispsVec()
{
	return m_dispsVec;
}


Disp& PIVPoint::primaryDisp()
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

void PIVPoint::printPeaks() 
{
	auto i(0);
	std::cout << "Peak#\ti\tj\tValue\tValid" << std::endl;
	for(auto& p : m_peaksVector)
		std::cout << (i++) << "\t" << p.i - m_ccf->offsetX() << "\t" << p.j - m_ccf->offsetY()
			<< "\t" 
			<< std::setprecision(4) << std::fixed
			<<  p.val << "\t" << p.valid << std::endl;

}

void PIVPoint::printDisps() 
{
	auto i(0);
	std::cout << "Disp\tu\tv\tValid" << std::endl;
	for(auto& d : m_dispsVec)
		std::cout << (i++) << "\t" << std::setprecision(4) << std::fixed << d.u << "\t" << d.v
			<< "\t" << d.valid << std::endl;

}

void PIVPoint::printToOfstream(std::ofstream& file)
{
	if (m_dispsVec[0].valid) {
	file << m_i << "\t" << m_j << "\t"
		 << m_dispsVec[0].u << "\t"
		 << m_dispsVec[0].v << "\t"
		 << std::endl;
	}
}
		

void PIVPoint::set_xCoord(int x)
{
	m_i = x;
}

void PIVPoint::set_yCoord(int y)
{
	m_j = y;
}

void PIVPoint::set_coords(std::pair<int, int>& coords)
{
	m_i = coords.first;
	m_j = coords.second;
}


int PIVPoint::x()
{
	return m_i;
}

int PIVPoint::y()
{
	return m_j;
}

PIVPoint::~PIVPoint() {};
}
