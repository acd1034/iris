// #pragma once
#include <algorithm>
#include <bits/stdc++.h>
#include <iris/iostream.hpp>
#include <iris/ranges.hpp>
namespace iris {
  // equal
  template <class T,
            class U,
            enable_if_t<!is_range_v<T> || !is_range_v<U>> = nullptr>
  bool equal(const T& lhs, const U& rhs) {
    return lhs == rhs;
  }
  /* template <class It1, class It2, class It3, class It4>
  bool equal(It1 first1, It2 last1, It3 first2, It4 last2) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
      if (!equal(*first1, *first2)) return false;
    return first1 == last1 && first2 == last2;
  } */
  template <class T,
            class U,
            enable_if_t<is_range_v<T> && is_range_v<U>> = nullptr>
  bool equal(const T& lhs, const U& rhs) {
    using std::begin, std::end;
    auto first1 = begin(lhs);
    auto last1  = end(lhs);
    auto first2 = begin(rhs);
    auto last2  = end(rhs);
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
      if (!equal(*first1, *first2)) return false;
    return first1 == last1 && first2 == last2;
  }
  template <class T, class U>
  bool equal(const std::initializer_list<T>& lhs,
             const std::initializer_list<U>& rhs) {
    return equal(lhs, rhs);
    // return equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U>
  bool equal(const std::initializer_list<std::initializer_list<T>>& lhs,
             const std::initializer_list<std::initializer_list<U>>& rhs) {
    return equal(lhs, rhs);
    // return equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
} // namespace iris

template <class T>
using il = std::initializer_list<T>;
int main() {
  using std::cout, std::list;
  cout << std::boolalpha;
  // iris::equal(list{1, 2, 3}, list{1, 2, 3}) | cout;
  iris::equal(il<int>{1, 2, 3}, il<int>{1, 2, 3}) | cout;
  // iris::equal({{1}, {2}, {3}}, {{1}, {2}, {3}}) | cout;
}
