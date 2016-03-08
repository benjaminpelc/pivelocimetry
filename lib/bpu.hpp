#ifndef BPU_UTILITY_FUNCTIONS_H
#define BPU_UTILITY_FUNCTIONS_H

#include <algorithm>
#include <cmath>
#include <iostream>

namespace bpu {

/* Extract value type from a pointer/iterator */
template <typename T> using Value_type = typename T::value_type;

/* Return a vector of elements from a container that all meat the
 * predicate pred */
template <typename It, typename Pred>
std::vector<Value_type<It>> collect(It beg, It end, Pred pred) {
  std::vector<Value_type<It>> res;
  for_each(beg, end, [&](auto &x) {
    if (pred(x))
      res.push_back(x);
  });
  return res;
};

/* Simple for_each implementation for whole container */
template <typename Container, typename Pred>
void for_each(Container &&c, Pred pred) {
  std::for_each(std::begin(c), std::end(c), pred);
}

/* Calculate the median value of a container with specified
 * return type. Original container is not modified */
template <typename To, typename Container> To median(Container c);

/* Same as median but container is modified by partially
 * sorting contents */
template <typename To, typename Container>
To median_modify_container(Container &&c);

/* Arithmetic mean of a container with specified return type */
template <typename To, typename Container> To mean(Container &&c);

/* Mean of pairs. First is the mean of firsts, second is mean
 * of seconds */
template <typename TFirst, typename TSecond, typename Container>
std::pair<TFirst, TSecond> mean_pairs(Container &&c);

/* Static cast but rounding to nearest integer value
 * for integral types */
template <typename To, typename From> To cast_round_if_integral(const From f);

/* Cout helpers for containers */
template <typename Container>
void print_each(const Container &c, const std::string delimeter = ", ");

template <typename It>
void print_each(const It beg, const It end, const std::string delimeter = ", ");

template <typename Container> void print_front(const Container &c);

template <typename Container> void print_back(const Container &c);

/* Subtract a value from a container and take the absolute
 * values */
template <typename T, typename Container>
void subtract_and_abs(Container &c, const T v) {
  std::transform(c.begin(), c.end(), c.begin(),
                 [&v](auto &cval) { return std::abs(cval - v); });
}

/* Add a pair of std::pairs returning a new pair of the same type */
template <typename First, typename Second>
std::pair<First, Second> add_pairs(std::pair<First, Second> &lhs,
                                   std::pair<First, Second> &rhs) {
  return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

/* Calculate the mean pair of a container of pairs */
template <typename TFirst, typename TSecond, typename Container>
std::pair<TFirst, TSecond> mean_pairs(Container &&c) {
  size_t cSize = c.size();
  auto result = std::make_pair(TFirst(), TSecond());

  auto add_pair = [](std::pair<TFirst, TSecond> a,
                     std::pair<TFirst, TSecond> b) {
    return std::make_pair(a.first + b.first, a.second + b.second);
  };

  result = std::accumulate(c.begin(), c.end(), result, add_pair);
  result.first /= cSize;
  result.second /= cSize;

  return result;
}

template <typename To, typename Container> To mean(Container &&c) {
  return cast_round_if_integral<To>(std::accumulate(c.begin(), c.end(), To()) /
                                    c.size());
}

/* If casting to an integral value, round to the nearest integer value rather
 * than discarding the sub-integer component (i.e. floor(x)) */
template <typename To, typename From> To cast_round_if_integral(const From f) {
  if (std::is_integral<To>::value) {
    return static_cast<To>(f + 0.5);
  } else {
    return static_cast<To>(f);
  }
}

template <typename To, typename Container> To median(Container c) {
  return median_modify_container<To>(std::move(c));
}

template <typename To, typename Container>
To median_modify_container(Container &&c) {
  /* Empty array returns zero */
  if (c.empty())
    return static_cast<To>(0);

  /* Single element returns the element */
  size_t cSize = c.size();
  if (cSize == 1)
    return cast_round_if_integral<To>(c[0]);

  /* Find the middle index */
  size_t mark = cSize >> 1;
  std::nth_element(c.begin(), c.begin() + mark, c.end());

  if (cSize & 1) {
    return cast_round_if_integral<To>(c[mark]);
  } else {
    auto median = 0.5 * (c[mark] + c[mark - 1]);
    return cast_round_if_integral<To>(median);
  }
}

template <typename Container>
void print_each(const Container &c, const std::string delimeter) {
  print_each(c.begin(), c.end(), delimeter);
}

template <typename It>
void print_each(const It beg, const It end, const std::string delimeter) {
  std::for_each(beg, end - 1,
                [delimeter](auto &val) { std::cout << val << delimeter; });
  std::cout << *(end - 1) << std::endl;
}

template <typename Container> void print_front(const Container &c) {
  std::cout << c.front() << std::endl;
}

template <typename Container> void print_back(const Container &c) {
  std::cout << c.back() << std::endl;
}
template <typename It>
std::vector<Value_type<It>> collect_unique(It first, It last) {
  std::vector<Value_type<It>> res(last - first);
  auto res_front = res.begin();
  std::copy(first, last, res_front);
  std::sort(res_front, res.end());
  auto last_unique = std::unique(res_front, res.end());
  res.erase(last_unique, res.end());
  return res;
};

template <typename It, typename Pred>
auto collect_unique(It first, It last, Pred p)
    -> std::vector<decltype(p(*first))> {
  std::vector<decltype(p(*first))> res(last - first);
  auto res_itr = res.begin();
  for_each(first, last, [&](auto v) { *(res_itr++) = p(v); });

  auto res_front = res.begin();
  auto res_end = res.end();

  std::sort(res_front, res_end);
  auto last_unique = std::unique(res_front, res_end);
  res.erase(last_unique, res_end);

  return res;
};

template <typename Container, typename Pred>
auto collect_unique(Container &&c, Pred p)
    -> std::vector<decltype(p(c.front()))> {
  return collect_unique(c.begin(), c.end(), p);
};
}

#endif
