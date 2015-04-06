#include "Grid.hpp"

namespace PivEng {

Grid::Grid( PivOptions& config, IntMap& image ) :
	m_ptsX(),
	m_ptsY(),
	m_coords()
{
	auto imW = image.cols(),
		 imH = image.rows();
	auto winW = config.winWidth(),
		 winH = config.winHeight();
	auto ovlpX = config.olvpHoriz(),
		 ovlpY = config.olvpVert();

	auto num_points_on_axis = [](int imDim, int winDim, int olp) -> int {
		return (imDim - winDim) / (winDim - olp) + 1;
	};

	m_noX = num_points_on_axis(imW, winW, ovlpX);
	m_noY = num_points_on_axis(imH, winH, ovlpY); 

	m_ptsX.resize(m_noX);
	m_ptsY.resize(m_noY);
	m_coords.resize(m_noX * m_noY);

	/* Have repetition here. Perhaps refactor out */
	size_t i = 0, j = 0;
	std::for_each(m_ptsX.begin(), m_ptsX.end(), [&](int& x) {
				x = (winW - ovlpX) * (i++) -1 + winW / 2; 
			});
	
	std::for_each(m_ptsY.begin(), m_ptsY.end(), [&](int& y) {
				y = (winH - ovlpY) * (j++) -1 + winH / 2; 
			});

	size_t ctr = 0;
	std::for_each(m_coords.begin(), m_coords.end(), [&](auto &c) {
			c = std::make_pair(m_ptsX[ctr % m_noX], m_ptsY[ctr / m_noX]);
			ctr++;
		});
}

Grid::~Grid() {};

int Grid::x(int i)
{
	return m_ptsX[i];
}

int Grid::y(int i)
{
	return m_ptsY[i];
}

int Grid::numX()
{
	return m_ptsX.size();
}

int Grid::numY()
{
	return m_ptsY.size();
}

int Grid::size()
{
	return m_ptsX.size() * m_ptsY.size();
}

std::vector<int>& Grid::xVector()
{
	return m_ptsX;
}

std::vector<int>& Grid::yVector()
{
	return m_ptsY;
}

std::vector<Grid::CoordPair>& Grid::coordsVec()
{
	return m_coords;
}
}
