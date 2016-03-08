// utils.hpp
// Utility helper functions that do not belong in a class of their own.
//
// Author: Benjamin Pelc <pelc.benjamin@gmail.com>
// Date created:

#ifndef BPPIV_UTILS_H
#define BPPIV_UTILS_H

#include <cstdlib>

namespace PivEng {
size_t subsrcipts_to_index(const size_t i, const size_t j,
                           const size_t num_cols);
}

#endif
