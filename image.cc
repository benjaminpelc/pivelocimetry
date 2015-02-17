#include "image.h"

Image::Image() {}

Image::~Image() {}

// Setters
void Image::set_filename(std::string fn)
{
	_filename = fn;
}

// Getters
std::string Image::get_filename()
{
	return _filename;
}
