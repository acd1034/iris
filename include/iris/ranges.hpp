#pragma once
#include <iris/iterator.hpp>

namespace iris {
  namespace ranges {
    template <typename R>
    using std_begin_t = decltype(std::begin(std::declval<R>()));
    template <typename R>
    using std_end_t = decltype(std::end(std::declval<R>()));
    template <typename R>
    using adl_begin_t = decltype(begin(std::declval<R>()));
    template <typename R>
    using adl_end_t = decltype(end(std::declval<R>()));
  } // namespace ranges
  template <typename R>
  using iterator_t =
    detected_or_t<detected_t<ranges::std_begin_t, R&>, ranges::adl_begin_t, R&>;
  template <typename R>
  using sentinel_t =
    detected_or_t<detected_t<ranges::std_end_t, R&>, ranges::adl_end_t, R&>;
  template <typename R>
  using range_value_t = iter_value_t<iterator_t<R>>;
  template <typename R>
  using range_reference_t = iter_reference_t<iterator_t<R>>;
  // template <typename R>
  // using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
  // template <typename R>
  // using range_difference_t = iter_difference_t<iterator_t<R>>;
#define IRIS_DEFINE_UNARY_CONCEPT(Name, Type, ...)                             \
  template <typename Type>                                                     \
  using Name = std::conjunction<__VA_ARGS__>;                                  \
  template <typename Type>                                                     \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type>::value;
#define IRIS_DEFINE_BNARY_CONCEPT(Name, Type1, Type2, ...)                     \
  template <typename Type1, typename Type2>                                    \
  using Name = std::conjunction<__VA_ARGS__>;                                  \
  template <typename Type1, typename Type2>                                    \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2>::value;
  IRIS_DEFINE_UNARY_CONCEPT(is_range_class,
                            R,
                            is_detected<ranges::class_begin_t, R&>,
                            is_detected<ranges::class_end_t, R&>)
}; // namespace iris
