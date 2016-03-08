// DoPiv.cpp
// Implementation of DoPIV class. The main PIV vector calculation
// Loop.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "DoPiv.hpp"

namespace PivEng {
DoPiv::DoPiv(PivOptions &options, const IntMap::Pair &imPair, Grid &g)
    : m_num_points(g.size()),
      m_ccfs(m_num_points,
             Mat2<double>(options.winHeight() + 1, options.winWidth() + 1)),
      m_points(m_num_points, PivPoint(-1, -1, options)) {
  // Create a vector of PivPoints when the object is instantiated,
  // give constructor to instantiate CCF at correct size,
  // for now set coordinate to (-1, -1) to indicate that the piv has not yet
  // been done
  //
  //  Once vector points have been initiated loop through each point with
  //  an individual pair of interrogation region coordinates and do the PIV
  //  calculations for each point */

  auto im1Beg = imPair.first->begin();
  auto im2Beg = imPair.second->begin();
  auto imCols = imPair.first->cols();

  // Loop through each grid point and set the point coordinates to the
  // corresponding coordinates from grid.
  for (auto idx = 0; idx < m_num_points; idx++)
    m_points[idx].set_coords(g[idx]);

  // Lambda to calculate cross correlation functions for each vector point.
  auto ccfBatch = [&](int beg, int end) {
    Mat2<double> *ccf = nullptr;
    PivPoint *p = nullptr;
    Peak::PeaksVec *pks = nullptr;

    for (auto idx = beg; idx != end; idx++) {
      ccf = &m_ccfs[idx];
      p = &m_points[idx];
      pks = &p->peaks();

      // Do the cross-correlation, find the peaks and calculate the sub-pixel
      // component of displacement.
      x_corr_n_2(*ccf, imCols, im1Beg, im2Beg, p->i, p->j);
      find_ccf_peaks(*pks, *ccf, 13);
      gauss(*ccf, *pks, p->dispsVec());
    }
  };

  // Run on two threads, splitting the points evenly between the two.
  std::thread t1{ccfBatch, 0, m_num_points / 2};
  ccfBatch(m_num_points / 2, m_num_points);
  t1.join();
}

DoPiv::PivPointVec &DoPiv::pointsVector() {
  return m_points;
}

void DoPiv::write(const std::string filename) {
  std::ofstream outfile(filename);
  std::for_each(m_points.begin(), m_points.end(),
                [&outfile](auto &point) { point.printToOfstream(outfile); });

  outfile.close();
}

void DoPiv::print() {
  Disp *pv = nullptr;

  for (auto &p : m_points) {
    pv = &p.primaryDisp();
    std::cout << p.x() << "\t" << p.y() << std::setprecision(3) << std::fixed
              << "\t" << pv->get_u() << "\t" << pv->get_v() << "\t"
              << sqrt(pow(pv->get_u(), 2) + pow(pv->get_v(), 2)) << "\t"
              << pv->is_valid() << std::endl;
  }
  std::cout << "Total vectors calculated: " << m_points.size() << std::endl;
}

DoPiv::~DoPiv() {}
}
