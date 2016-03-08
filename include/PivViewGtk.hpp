// PivViewGtk.hpp
// Header for GTK Vector Viewer GUI class.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_PIV_VIEW_GTK_H
#define BPPIV_PIV_VIEW_GTK_H

#include "../lib/bpu.hpp"
#include "MyAreaD.hpp"
#include "PivPoint.hpp"
#include <algorithm>
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

class PivViewGtk {
  using VecPivVector = std::vector<PivEng::PivVector>;

public:
  PivViewGtk(PivEng::PivPoint::PivPointVec &vs);
  ~PivViewGtk();

private:
  PivEng::PivPoint::PivPointVec &m_pivPointVec;
  VecPivVector piv_vectors;

  double max_velocity_magnitude{0};

  Gtk::Window *pWindow;
  MyAreaD *pMyArea;
  Gtk::Label *pNumVectorsLabel, *pMaxVelLabel;

  int num_vectors;

  // Private Member Functions
  void get_piv_vectors_and_maximum_velocity();
};

#endif
