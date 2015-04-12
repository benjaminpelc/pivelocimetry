#include "utils.hpp"

namespace PivEng {

size_t subsrcipts_to_index(const size_t i, const size_t j, const size_t num_cols)
{
	return j * num_cols + i;
}

}

