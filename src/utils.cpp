// utils.cpp
// Utility helper functions that do not belong in a class of their own.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#include "utils.hpp"

namespace PivEng {

size_t subsrcipts_to_index(const size_t i, const size_t j,
                           const size_t num_cols) {
  return j * num_cols + i;
}
}
