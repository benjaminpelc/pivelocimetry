#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>
#include <iostream>

#include "int_map.h"
#include "pivoptions.h"

class Grid
{
	public:
		Grid();
		Grid(const std::shared_ptr<PivOptions>& config, const std::shared_ptr<IntMap>& image);
		~Grid();

	private:
		std::vector<int> _points_x,
						 _points_y;
};

Grid::Grid() {};

Grid::Grid(const std::shared_ptr<PivOptions>& config, const std::shared_ptr<IntMap>& image)
{
	std::cout << "In grid" << std::endl;
}

Grid::~Grid() {};

#endif
