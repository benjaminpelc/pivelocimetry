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
		int _noVectorsX, _noVectorsY;
		std::vector<int> _pointsX,
						 _pointsY;
		std::vector<CoordPair> _coordsVector;	
};

Grid::Grid(
			const PivOptions::Uptr& config,
			const std::unique_ptr<IntMap>& image 
		) :
	_pointsX(),
	_pointsY(),
	_coordsVector()
{
	/* Get the image width and height */
	int imW = image->cols(),
		imH = image->rows(),
		winW = config->get_windowWidth(),
		winH = config->get_windowHeight(),
		ovlpX = config->get_overlapHoriz(),
		ovlpY = config->get_overlapVert();

	/* Number of vectors in the x and y directions.
	 * 
	 * ToDo:
	 * 1) Have repetition here, extract out as a lambda. */
	_noVectorsX = (int) floor( (imW - winW) / (winW - ovlpX) + 1); 
	_noVectorsY = (int) floor( (imH - winH) / (winH - ovlpY) + 1); 

	/* Initialize vectors of x and y grid points */
	_pointsX.resize(_noVectorsX);
	_pointsY.resize(_noVectorsY);

	/* Set length of vector to store coordinate points */
	_coordsVector.resize(_noVectorsX * _noVectorsY);

	for (int i = 0; i < _noVectorsX; i++)
	{
		_pointsX[i] = (winW - ovlpX) * i - 1 + winW / 2;
	}

	for (int j = 0; j < _noVectorsY; j++)
	{
		_pointsY[j] = (winH - ovlpY) * j - 1 + winH / 2;
	}

	auto cv = _coordsVector.begin();
	for (auto y : _pointsY) {
		for (auto x : _pointsX) {
			cv->first = x;
			cv->second = y;
			cv++;
		}
	}
}

Grid::~Grid() {};

int Grid::get_xCoord(int i)
{
	return _pointsX[i];
}

int Grid::get_yCoord(int i)
{
	return _pointsY[i];
}

int Grid::get_noPointsX()
{
	return _pointsX.size();
}

int Grid::get_noPointsY()
{
	return _pointsY.size();
}

int Grid::get_totalGridPoints()
{
	return _pointsX.size() * _pointsY.size();
}

std::vector<int>& Grid::get_xCoordVector()
{
	return _pointsX;
}

std::vector<int>& Grid::get_yCoordVector()
{
	return _pointsY;
}

std::vector<Grid::CoordPair>& Grid::get_coordPairsVector()
{
	return _coordsVector;
}
#endif
