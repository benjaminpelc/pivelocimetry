#include "ocv_image.h"

OCVImage::OCVImage(std::string fn)
{
	readImage(fn);
}

OCVImage::~OCVImage()
{
	// _rawImage.~Mat();
}

void OCVImage::readImage(std::string fn)
{
	_rawImage = cv::imread(fn, 0);
}

unsigned int OCVImage::getPixelIntensity(unsigned int row, unsigned int col)
{
	return ((cv::Scalar) _rawImage.at<uchar>(row, col)).val[0];
}

unsigned int OCVImage::getHeight()
{
	return (unsigned int) _rawImage.rows;
}

unsigned int OCVImage::getWidth()
{
	return (unsigned int) _rawImage.cols;
}
