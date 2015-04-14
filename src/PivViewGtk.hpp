#ifndef BPPIV_PIV_VIEW_GTK_H
#define BPPIV_PIV_VIEW_GTK_H

#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <algorithm>
#include "PivPoint.hpp"
#include "../lib/bpu.hpp"

class PivViewGtk {
  using VecPivVector = std::vector<PivEng::PivVector>;

public:
  PivViewGtk(PivEng::PivPoint::PivPointVec &vs);
  ~PivViewGtk();

private:
  PivEng::PivPoint::PivPointVec &m_pivPointVec;
  VecPivVector piv_vectors;
};

#endif
