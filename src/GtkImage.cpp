// GtkImage.cpp
// Implementation of GtkImage class. Handle loading of images and retrieval of
// pixel intensity values and various image properties.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "GtkImage.hpp"

GtkBufImage::GtkBufImage(std::string fn) :
	_pixBuff{Gdk::Pixbuf::create_from_file(fn)},
	pixels{_pixBuff->get_pixels()},
	rowstrid{_pixBuff->get_rowstride()},
	n_channels{_pixBuff->get_n_channels()}

{
}

GtkBufImage::~GtkBufImage() {}

void GtkBufImage::read(std::string fn) { _pixBuff = Gdk::Pixbuf::create_from_file(fn); }

unsigned int GtkBufImage::pixelInt(unsigned int row, unsigned int col) {
  guchar *p = nullptr;

  p =  pixels + row * rowstrid + col * n_channels;

  return static_cast<uint16_t>(p[0]);
}

unsigned int GtkBufImage::height() { return (unsigned int)_pixBuff->get_height(); }

unsigned int GtkBufImage::width() { return (unsigned int)_pixBuff->get_width(); }
