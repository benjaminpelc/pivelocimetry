// IntMap.hpp
// Header for IntMap class. A two-dimensional matrix with unsigned 16-bit
// integer elements. Instances of this class are used to contain image pixel
// intensity values.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef INT_MAP_H
#define INT_MAP_H

#include <memory>

#include "../lib/Mat2.hpp"
#include "IntMappable.hpp"

class IntMap : public Mat2<uint16_t> {
public:
  // Type definitions
  typedef std::unique_ptr<IntMap> Uptr;
  typedef std::pair<IntMap *, IntMap *> Pair;

  // IntMap
  // Create an IntMap of fixed size with all array elements equal to zero.
  //  -- rows : number of rows in array
  //  -- cols : number of columns in array
  IntMap(unsigned int rows, unsigned int cols);

  // IntMap
  // Create an IntMap from an instance of an object satisfying the IntMappable
  // interface.
  //  -- raw : IntMappable instance containing pixel intensities.
  IntMap(IntMappable *raw);

  // IntMap
  // Create an IntMap from an instance of an object satisfying the IntMappable
  // interface.
  //  -- raw : IntMappable instance containing pixel intensities.
  IntMap(const std::unique_ptr<IntMappable> &raw);

  ~IntMap();

private:
};

#endif
