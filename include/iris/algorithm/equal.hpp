#pragma once
#include <iris/ranges.hpp>

namespace iris {
  // equal
  namespace algorithm {
    IRIS_DEFINE_BNARY_CONCEPT(
      is_weakly_equality_comparable_with, T, U,
      is_detected_exact<bool, concepts::equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
      is_detected_exact<bool, concepts::equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
      is_detected_exact<bool, concepts::not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
      is_detected_exact<bool, concepts::not_equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>)
    IRIS_DEFINE_UNARY_CONCEPT(
      is_equality_comparable, T,
      is_weakly_equality_comparable_with<T, T>)
    IRIS_DEFINE_BNARY_CONCEPT(
      is_equality_comparable_with, T, U,
      is_equality_comparable<T>,
      is_equality_comparable<U>,
      is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
      is_equality_comparable<concepts::common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
      is_weakly_equality_comparable_with<T, U>)
  } // namespace algorithm
  template <class T,
            class U,
            enable_if_t<algorithm::is_equality_comparable_with_v<T, U>> = nullptr>
  bool equal(const T& lhs, const U& rhs) {
    return lhs == rhs;
  }
  template <class It1, class It2, class It3, class It4>
  bool equal(It1 first1, It2 last1, It3 first2, It4 last2);
  template <class T,
            class U,
            enable_if_t<!algorithm::is_equality_comparable_with_v<T, U> //
                        && is_range_v<T> && is_range_v<U>> = nullptr>
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
            enable_if_t<is_range_v<T> && is_range_v<range_value_t<T>>> = nullptr>
  bool equal(const T& lhs,
             std::initializer_list<std::initializer_list<U>> rhs) {
    using std::begin, std::end;
    return ::iris::equal(begin(lhs), end(lhs), begin(rhs), end(rhs));
  }
  template <class T, class U,
            enable_if_t<is_range_v<U> && is_range_v<range_value_t<U>>> = nullptr>
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
