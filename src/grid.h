/* Class Grid
 *
 * Grid of integer image plane coordinates.
 * Coordinates mark the centre of a PIV interrogation window.
 */

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <map>
#include <utility>
#include <algorithm>

#include "int_map.h"
#include "pivoptions.h"

class Grid
{
	public:
		typedef std::unique_ptr<Grid> Uptr;
		typedef std::pair<int, int> CoordPair;

		Grid(const PivOptions::Uptr& config, const std::unique_ptr<IntMap>& image);
		~Grid();
		int x(int i);
		int y(int i);
		int numX();
		int numY();
		int numPoints();

		std::vector<int>& xVector();
		std::vector<int>& yVector();
		std::vector<CoordPair>& coordsVec();

	private:
		int _noX, _noY;
		std::vector<int> _ptsX,
						 _ptsY;
		std::vector<CoordPair> _coords;	
};

Grid::Grid(
			const PivOptions::Uptr& config,
			const std::unique_ptr<IntMap>& image 
		) :
	_ptsX(),
	_ptsY(),
	_coords()
{
	/* Get the image width and height */
	int imW = image->cols(),
		imH = image->rows(),
		winW = config->winWidth(),
		winH = config->winHeight(),
		ovlpX = config->olvpHoriz(),
		ovlpY = config->olvpVert();

	/* Number of vectors in the x and y directions.*/
	auto noPointsInDirn = [](int imDim, int winDim, int olp) -> int {
		return floor ( (imDim - winDim) / (winDim - olp) + 1);
	};

	_noX = noPointsInDirn(imW, winW, ovlpX);
	_noY = noPointsInDirn(imH, winH, ovlpY); 

	/* Initialize vectors of x and y grid points */
	_ptsX.resize(_noX);
	_ptsY.resize(_noY);

	/* Set length of vector to store coordinate points */
	_coords.resize(_noX * _noY);

	int i = 0, j = 0;

	/* Have repetition here. Perhaps refactor out */
	std::for_each(_ptsX.begin(), _ptsX.end(), [&](int& x) {
				x = (winW - ovlpX) * (i++) -1 + winW / 2; 
			});
	
	std::for_each(_ptsY.begin(), _ptsY.end(), [&](int& y) {
				y = (winH - ovlpY) * (j++) -1 + winH / 2; 
			});

	int ctr = 0;
	std::for_each(_coords.begin(), _coords.end(), [&](auto &c) {
			c = std::make_pair(_ptsX[ctr % _noX], _ptsY[floor (ctr / _noX)]);
			ctr++;
	});
}

Grid::~Grid() {};

int Grid::x(int i)
{
	return _ptsX[i];
}

int Grid::y(int i)
{
	return _ptsY[i];
}

int Grid::numX()
{
	return _ptsX.size();
}

int Grid::numY()
{
	return _ptsY.size();
}

int Grid::numPoints()
{
	return _ptsX.size() * _ptsY.size();
}

std::vector<int>& Grid::xVector()
{
	return _ptsX;
}

std::vector<int>& Grid::yVector()
{
	return _ptsY;
}

std::vector<Grid::CoordPair>& Grid::coordsVec()
{
	return _coords;
}
#endif
