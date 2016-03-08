// DoPiv.cpp
// Header file for DoPIV class. The main PIV vector calculation
// Loop.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_DO_PIV_H
#define BPPIV_DO_PIV_H

#include <fstream>
#include <algorithm>
#include <iomanip>
#include <thread>

#include "PivOptions.hpp"
#include "IntMap.hpp"
#include "Grid.hpp"
#include "XCorr2.hpp"
#include "PivPoint.hpp"
#include "SubPix.hpp"
#include "find_peaks.hpp"
#include "../lib/Mat2.hpp"

#include "../lib/alias.hpp"

namespace PivEng {

class DoPiv {
public:
  typedef std::vector<PivPoint> PivPointVec;

  // DoPiv
  // Calculate all PIV vectors
  //  -- options : PIV analysis settings including window size, overlap, etc.
  //  -- imPair : A pair of IntMap image pixel intensity matrices.
  //  -- g : Vector grid object containing vector spatial coordinates
  DoPiv(PivOptions &options, const IntMap::Pair &imPair, Grid &g);

  // print
  // Print the calculated vectors to STDOUT in the format:
  //   x1    y1    u1    v1    valid1
  //   x2    y2    u2    v2    valid2
  //   ...
  void print();

  // write
  // Write out the PIV vectors in the format:
  //   x1    y1    u1    v1
  //   x2    y2    u2    v2
  // Use tab delimiter. Modify this to use specified delimeter.
  //  -- filename : Where to write the vectors to.
  void write(const std::string filename);

  // PivPointVec
  // Return a reference to the vector of PIV points. 
  PivPointVec &pointsVector();

  ~DoPiv();

private:
  // m_num_points
  // The total number of displacement vectors. This is the same length as the
  // vector grid object.
  int m_num_points;

  // m_ccfs
  // Vector of correlation functions. One two dimentional matrix with double
  // elements for each vector grid point.
  std::vector<Mat2<double>> m_ccfs;

  // m_points
  // Vector containing PivPoints. Each point contains all information about the
  // vector at that point.
  PivPointVec m_points;
};
}
#endif
