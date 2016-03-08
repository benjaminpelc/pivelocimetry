// IntMappable.hpp
// Interface for objects that can be used to generate an IntMap
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef INT_MAPPABLE_H
#define INT_MAPPABLE_H

class IntMappable {
public:
  virtual unsigned int pixelInt(unsigned int row, unsigned int col) = 0;
  virtual unsigned int height() = 0;
  virtual unsigned int width() = 0;
  virtual ~IntMappable() = 0;

private:
};

inline IntMappable::~IntMappable(){};

#endif
