#include <cmath>
#include <algorithm>

namespace bpu {

template<typename To, typename Container>
To median(Container&& c);

template<typename To, typename Container>
To median_modify_container(Container&& c);

template<typename To, typename Container>
To median(Container&& c)
{
	auto cCopy = c;
	return median_modify_container<To>(cCopy);
}

template<typename To, typename Container>
To median_modify_container(Container&& c)
{
	/* Empty array returns zero */
	if (c.empty())
		return static_cast<To>(0);

	/* Single element returns the element */
	size_t sz = c.size();
	if (sz == 1)
		return c[0];

	/* Find the middle index */
	size_t mark = floor(sz / 2);
	std::nth_element(c.begin(), c.begin() + mark, c.end());

	/* Value at floor size/2 */
	auto cMark = c[mark];

	if (sz % 2 != 0) {
		if (std::is_integral<To>::value) {
			return static_cast<To>(cMark + 0.5);
		} else {
			return static_cast<To>(cMark);
		}
	} else {
		auto cMarkPrev = c[mark - 1];
		if (std::is_integral<To>::value) {
			return static_cast<To>(0.5 * (cMarkPrev + cMark) + 0.5);
		} else {
			return static_cast<To>(0.5 * (cMarkPrev + cMark));
		}
	}
}
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
