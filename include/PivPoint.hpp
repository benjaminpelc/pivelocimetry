// PivPoint.hpp
// Implementation of PivPoint class. Basically a container containing all
// information about a PIV vector point, such as coodinates, a list of
// cross-correlation function displacement peaks and the corresponding
// displacement vectors.
//
// Currently, each point has:
// 1) A CCF
// 2) A vector of peak objects
// 3) A vector of displacement objects
// 4) A pair of pixel coordinates
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef PIV_POINT_H
#define PIV_POINT_H

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "PivOptions.hpp"
#include "../lib/Mat2.hpp"
#include "IntMap.hpp"
#include "Peak.hpp"
#include "Disp.hpp"
#include "Grid.hpp"
#include "PivVector.hpp"

namespace PivEng {

class PivPoint {
public:
  using PivPointVec = std::vector<PivPoint>;

  PivPoint(int xCoord, int yCoord, PivOptions &options);
  ~PivPoint();

  // CCF* get_ccf();
  Peak::PeaksVec &peaks();
  Disp::DispVec &dispsVec();

  void set_xCoord(int x);
  void set_yCoord(int y);
  void set_coords(Grid::CoordPair &coords);

  int x();
  int y();

  std::unique_ptr<PivVector> get_piv_vector();

  Disp &primaryDisp();
  void printToOfstream(std::ofstream &file);
  void printPeaks();
  void printDisps();

  int i, j;

private:
  Peak::PeaksVec m_peaksVector;
  Disp::DispVec m_dispsVec;
};
}

#endif
