// GtkImage.hpp
// Header for GtkImage class. Handle loading of images and retrieval of
// pixel intensity values and various image properties.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef GTK_IMAGE_H
#define GTK_IMAGE_H

#include "IntMappable.hpp"
#include <iostream>
#include <gtkmm.h>

class GtkBufImage : public IntMappable {
public:
  GtkBufImage(std::string fn);
  ~GtkBufImage();
  unsigned int pixelInt(unsigned int row, unsigned int col);
  unsigned int height();
  unsigned int width();

private:
	Glib::RefPtr<Gdk::Pixbuf> _pixBuff;
	guchar *pixels;
	int rowstrid;
	int n_channels;
  void read(std::string filename);

};

#endif
