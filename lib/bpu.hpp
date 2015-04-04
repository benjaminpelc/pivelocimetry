#include <cmath>
#include <algorithm>

namespace bpu {

template<typename T>
T median(std::vector<T>& vec)
{
	size_t sz = vec.size();
	if (sz % 2 != 0) {
		size_t mark = floor(sz / 2);
		std::nth_element(vec.begin(), vec.begin() + mark, vec.end());
		return vec[mark];
	} else {
		std::sort(vec.begin(), vec.end());
		return 0.5 * (vec[sz / 2 - 1] + vec[sz / 2]);
	}
};

/*
 * template<typename T>
 * T median(std::vector<T>& vec)
 * {
 * 	size_t sz = vec.size();
 * 	if (sz % 2 != 0) {
 * 		size_t mark = floor(sz / 2);
 * 		std::nth_element(vec.begin(), vec.begin() + mark, vec.end());
 * 		return vec[mark];
 * 	} else {
 * 		std::sort(vec.begin(), vec.end());
 * 		return 0.5 * (vec[sz / 2 - 1] + vec[sz / 2]);
 * 	}
 * };
 */
}
