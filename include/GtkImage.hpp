#ifndef GTK_IMAGE_H
#define GTK_IMAGE_H

#include "IntMappable.hpp"
#include <iostream>
// #include <opencv2/highgui/highgui.hpp>
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
