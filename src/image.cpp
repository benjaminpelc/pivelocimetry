#include "image.h"

Image::Image() {
	_pixelArray = Matrix2<int>(16, 16, 0);
}

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

void Image::readImageFromFile()
{
	std::cout << _pixelArray;
	_pixBuff = Gdk::Pixbuf::create_from_file(get_filename());
	int width = _pixBuff->get_width(),
		height = _pixBuff->get_height(),
		rowstride = _pixBuff->get_rowstride(),
		n_channels = _pixBuff->get_n_channels();

	guchar *pixels = _pixBuff->get_pixels(),
		   *p; //= pixels + 7 * rowstride + 7 * n_channels;
	
	// _pixelArray = new Matrix2<int>(height, width, 0);
	std::cout << _pixelArray.rows() << " x " << _pixelArray.cols() << std::endl;

	for(int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			p = pixels + i * rowstride + j * n_channels;
				_pixelArray.setElem(i, j, (int) p[0]);
		}
	}
	std::cout << _pixelArray << std::cout;
}

void Image::get_pixelArray() {
	std::cout << _pixelArray.rows() << std::endl;
}
