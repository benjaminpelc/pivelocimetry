#include "Grid.hpp"

namespace PivEng {

	Grid::Grid( PivOptions& config, IntMap& image ) :
		m_ptsX(),
		m_ptsY(),
		m_coords()
	{
		/* Get the image width and height */
		int imW = image.cols(),
			imH = image.rows(),
			winW = config.winWidth(),
			winH = config.winHeight(),
			ovlpX = config.olvpHoriz(),
			ovlpY = config.olvpVert();

		/* Number of vectors in the x and y directions.*/
		auto noPointsInDirn = [](int imDim, int winDim, int olp) -> int {
			return floor ( (imDim - winDim) / (winDim - olp) + 1);
		};

		m_noX = noPointsInDirn(imW, winW, ovlpX);
		m_noY = noPointsInDirn(imH, winH, ovlpY); 

		/* Initialize vectors of x and y grid points */
		m_ptsX.resize(m_noX);
		m_ptsY.resize(m_noY);

		/* Set length of vector to store coordinate points */
		m_coords.resize(m_noX * m_noY);

		int i = 0, j = 0;

		/* Have repetition here. Perhaps refactor out */
		std::for_each(m_ptsX.begin(), m_ptsX.end(), [&](int& x) {
					x = (winW - ovlpX) * (i++) -1 + winW / 2; 
				});
		
		std::for_each(m_ptsY.begin(), m_ptsY.end(), [&](int& y) {
					y = (winH - ovlpY) * (j++) -1 + winH / 2; 
				});

		int ctr = 0;
		std::for_each(m_coords.begin(), m_coords.end(), [&](auto &c) {
				c = std::make_pair(m_ptsX[ctr % m_noX], m_ptsY[floor (ctr / m_noX)]);
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

	int Grid::numPoints()
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
