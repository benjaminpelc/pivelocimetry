// utils.hpp
// Utility helper functions that do not belong in a class of their own.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_UTILS_H
#define BPPIV_UTILS_H

#include <cstdlib>

namespace PivEng {

// subsrcipts_to_index
// For a pair of array subscripts for a two-dimesnional array return the linear
// index.
//  -- i : first array subscript
//  -- j : second array subscript
//  num_cols : number of columns in the array
size_t subsrcipts_to_index(const size_t i, const size_t j,
                           const size_t num_cols);
}

#endif
