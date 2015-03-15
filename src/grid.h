#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "int_map.h"
#include "pivoptions.h"

class Grid
{
	public:
		Grid(const std::shared_ptr<PivOptions>& config, const std::shared_ptr<IntMap>& image);
		~Grid();

	private:
		int _noVectorsX, _noVectorsY;
		std::vector<int> _pointsX,
						 _pointsY;
};

Grid::Grid(
			const std::shared_ptr<PivOptions>& config,
			const std::shared_ptr<IntMap>& image 
		)
{
	/* Get the image width and height */
	int imW = image->get_numCols(),
		imH = image->get_numRows(),
		winW = config->get_windowWidth(),
		winH = config->get_windowHeight(),
		ovlpX = config->get_overlapHoriz(),
		ovlpY = config->get_overlapVert();

	/* Number of vectors in the x and y directions */
	_noVectorsX = (int) floor(
				(imW - winW) / (winW - ovlpX) + 1
			); 
	_noVectorsY = (int) floor(
				(imH - winH) / (winH - ovlpY) + 1
			); 

	std::cout << _noVectorsX << std::endl;
	std::cout << _noVectorsY << std::endl;

	/* Initialize vectors of x and y grid points */
	std::vector<int> _pointsX(_noVectorsX),
					 _pointsY(_noVectorsY);

	for (int i = 0; i < _noVectorsX; i++)
	{
		_pointsX[i] = (winW - ovlpX) * i - 1 + winW / 2;
	}

	for (int i = 0; i < _noVectorsY; i++)
	{
		_pointsY[i] = (winH - ovlpY) * i - 1 + winH / 2;
	}

	std::cout << _pointsX[0] << std::endl;
	std::cout << _pointsX[1] << std::endl;
}

Grid::~Grid() {};

#endif
