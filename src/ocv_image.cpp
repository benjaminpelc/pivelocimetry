#include "ocv_image.h"

OCVImage::OCVImage(std::string fn)
{
	read(fn);
}

OCVImage::~OCVImage()
{
	// _rawImage.~Mat();
}

void OCVImage::read(std::string fn)
{
	_rawImage = cv::imread(fn, 0);
}

unsigned int OCVImage::pixelInt(unsigned int row, unsigned int col)
{
	return ((cv::Scalar) _rawImage.at<uchar>(row, col)).val[0];
}

unsigned int OCVImage::height()
{
	return (unsigned int) _rawImage.rows;
}

unsigned int OCVImage::width()
{
	return (unsigned int) _rawImage.cols;
}
