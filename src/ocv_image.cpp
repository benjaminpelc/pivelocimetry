#include "ocv_image.h"

OCVImage::OCVImage(std::string fn)
{
	read(fn);
}

OCVImage::~OCVImage()
{
	// m_rawImage.~Mat();
}

void OCVImage::read(std::string fn)
{
	m_rawImage = cv::imread(fn, 0);
}

unsigned int OCVImage::pixelInt(unsigned int row, unsigned int col)
{
	return ((cv::Scalar) m_rawImage.at<uchar>(row, col)).val[0];
}

unsigned int OCVImage::height()
{
	return (unsigned int) m_rawImage.rows;
}

unsigned int OCVImage::width()
{
	return (unsigned int) m_rawImage.cols;
}
