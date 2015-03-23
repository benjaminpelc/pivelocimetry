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

#include "IntMap.hpp"
#include "PivOptions.hpp"

namespace PivEng {

	class Grid
	{
		public:
			typedef std::unique_ptr<Grid> Uptr;
			typedef std::pair<int, int> CoordPair;

			Grid(PivOptions& config, IntMap& image);
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
			int m_noX, m_noY;
			std::vector<int> m_ptsX,
						 	 m_ptsY;
			std::vector<CoordPair> m_coords;	
	};

}
#endif
