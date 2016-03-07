#ifndef OCV_IMAGE_H
#define OCV_IMAGE_H

#include "IntMappable.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

class OCVImage : public IntMappable {
public:
  OCVImage(std::string fn);
  ~OCVImage();
  unsigned int pixelInt(unsigned int row, unsigned int col);
  unsigned int height();
  unsigned int width();

private:
  void read(std::string filename);

  cv::Mat m_rawImage;
};

#endif
