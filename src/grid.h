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
		int get_xCoord(int i);
		int get_yCoord(int i);
		int get_noPointsX();
		int get_noPointsY();
		int get_totalGridPoints();

		std::vector<int>& get_xCoordVector();
		std::vector<int>& get_yCoordVector();
		std::vector<CoordPair>& get_coordPairsVector();

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
		winW = config->get_windowWidth(),
		winH = config->get_windowHeight(),
		ovlpX = config->get_overlapHoriz(),
		ovlpY = config->get_overlapVert();

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

int Grid::get_xCoord(int i)
{
	return _ptsX[i];
}

int Grid::get_yCoord(int i)
{
	return _ptsY[i];
}

int Grid::get_noPointsX()
{
	return _ptsX.size();
}

int Grid::get_noPointsY()
{
	return _ptsY.size();
}

int Grid::get_totalGridPoints()
{
	return _ptsX.size() * _ptsY.size();
}

std::vector<int>& Grid::get_xCoordVector()
{
	return _ptsX;
}

std::vector<int>& Grid::get_yCoordVector()
{
	return _ptsY;
}

std::vector<Grid::CoordPair>& Grid::get_coordPairsVector()
{
	return _coords;
}
#endif
