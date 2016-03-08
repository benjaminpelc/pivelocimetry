// Grid.hpp
// Header file for Grid class. Generate a grid of (x, y) coordinate points at
// which vectors will be calculated. 
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

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

class Grid {
public:
  typedef std::unique_ptr<Grid> Uptr;
  typedef std::pair<int, int> CoordPair;

  Grid(PivOptions &config, IntMap &image);
  ~Grid();
  int x(int i) const;
  int y(int i) const;
  int numX() const;
  int numY() const;
  int size() const;

  CoordPair &operator[](const int i) { return m_coords[i]; };

  std::vector<int> &xVector();
  std::vector<int> &yVector();
  std::vector<CoordPair> &coordsVec();

private:
  int m_noX, m_noY;
  std::vector<int> m_ptsX, m_ptsY;
  std::vector<CoordPair> m_coords;
};
}
#endif
