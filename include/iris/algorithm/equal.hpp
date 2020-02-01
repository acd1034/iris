#pragma once
#include <iris/ranges.hpp>

namespace iris {
  // equal
  template <class T,
            class U,
            enable_if_t<is_equality_comparable_with_v<T, U> && !std::is_array_v<T>> = nullptr>
  bool equal(const T& lhs, const U& rhs) {
    return lhs == rhs;
  }
  template <class It1, class It2, class It3, class It4>
  bool equal(It1 first1, It2 last1, It3 first2, It4 last2);
  template <class T,
            class U,
            enable_if_t<(!is_equality_comparable_with_v<T, U> || std::is_array_v<T>) //
                        &&is_range_v<T> && is_range_v<U>> = nullptr>
  bool equal(const T& lhs, const U& rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U, enable_if_t<is_range_v<T>> = nullptr>
  bool equal(const T& lhs, std::initializer_list<U> rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U, enable_if_t<is_range_v<U>> = nullptr>
  bool equal(std::initializer_list<T> lhs, const U& rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U>
  bool equal(std::initializer_list<T> lhs,
             std::initializer_list<U> rhs) {
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U,
            enable_if_t<is_range_v<T>> = nullptr>
  bool equal(const T& lhs,
             std::initializer_list<std::initializer_list<U>> rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U,
            enable_if_t<is_range_v<U>> = nullptr>
  bool equal(std::initializer_list<std::initializer_list<T>> lhs,
             const U& rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U>
  bool equal(std::initializer_list<std::initializer_list<T>> lhs,
             std::initializer_list<std::initializer_list<U>> rhs) {
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class It1, class It2, class It3, class It4>
  bool equal(It1 first1, It2 last1, It3 first2, It4 last2) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
      if (!::iris::equal(*first1, *first2)) return false;
    return first1 == last1 && first2 == last2;
  }
} // namespace iris
