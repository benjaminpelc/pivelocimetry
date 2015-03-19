#ifndef OCV_IMAGE_H
#define OCV_IMAGE_H

#include "int_mappable_abstract.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

class OCVImage : public IntMappable
{
	public:
		OCVImage(std::string fn);
		~OCVImage();
		unsigned int getPixelIntensity(unsigned int row, unsigned int col);
		unsigned int getHeight();
		unsigned int getWidth();
	private:
		void readImage(std::string filename);

		cv::Mat _rawImage;
};

#endif
