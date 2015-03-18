#ifndef BPPIV_IMAGE_H
#define BPPIV_IMAGE_H

#include <iostream>
#include "matrix2.h"
#include <gtkmm.h>

class Image
{
	public:
		// Constructor
		Image();
		// Destructor
		~Image();

		// Setters 
		void set_filename(std::string fn);
		void readFromFile();

		// Getters
		std::string get_filename();
		void get_pixelArray();

	private:
		std::string _filename;
		Matrix2<int> _pixelArray;
		Glib::RefPtr<Gdk::Pixbuf> _pixBuff;
};

#endif
