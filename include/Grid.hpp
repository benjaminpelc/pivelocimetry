// Grid.hpp
// Header file for Grid class. Generate a grid of (x, y) coordinate points at
// which vectors will be calculated.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef GRID_H
#define GRID_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "IntMap.hpp"
#include "PivOptions.hpp"

namespace PivEng {

class Grid {
public:
  // Type definitions
  typedef std::unique_ptr<Grid> Uptr;
  typedef std::pair<int, int> CoordPair;

  // Constructor
  // Create a new instance of Grid based on input images and PivOptions.
  //  -- config : A PivOptions configuration object
  //  -- image : An intensity map containing the source image pixel intensities
  Grid(PivOptions &config, IntMap &image);
  ~Grid();

  // x
  // Return the ith grid coordinate in the x direction.
  int x(int i) const;

  // y
  // Return the ith grid coordinate in the y direction.
  int y(int i) const;

  // numX
  // Return the number of grid points in the x direction.
  int numX() const;

  // numY
  // Return the number of grid points in the y direction.
  int numY() const;

  // size
  // Return the total number of vector grid points (numX * numY).
  int size() const;

  // [] operator
  // Access grid coordinates via array index notation.
  CoordPair &operator[](const int i) { return m_coords[i]; };

  // xVector
  // Return a vector of integer grid points in the x direction.
  std::vector<int> &xVector();

  // yVector
  // Return a vector of integer grid points in the y direction.
  std::vector<int> &yVector();

  // coordsVec
  // Return a vector of (x, y) coordinate pairs for each vector grid point.
  std::vector<CoordPair> &coordsVec();

private:
  // number of grid points in the x and y directions
  int m_noX, m_noY;

  // Vectos containing the individual grid points in the x and y directions.
  std::vector<int> m_ptsX, m_ptsY;

  // Vector containing (x, y) coordinate pairs for each vector grid point.
  std::vector<CoordPair> m_coords;
};
}
#endif
