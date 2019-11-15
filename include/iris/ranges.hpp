#pragma once
#include <iris/iterator.hpp>

namespace iris {
  namespace ranges {
    template <typename R>
    using class_begin_t = decltype(std::declval<R>().begin());
    template <typename R>
    using class_end_t = decltype(std::declval<R>().end());
  } // namespace ranges

#define IRIS_DEFINE_UNARY_CONCEPT(Name, Type, ...)                                                 \
  template <typename Type>                                                                         \
  using Name = std::conjunction<__VA_ARGS__>;                                                      \
  template <typename Type>                                                                         \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type>::value;
#define IRIS_DEFINE_BNARY_CONCEPT(Name, Type1, Type2, ...)                                         \
  template <typename Type1, typename Type2>                                                        \
  using Name = std::conjunction<__VA_ARGS__>;                                                      \
  template <typename Type1, typename Type2>                                                        \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2>::value;
  IRIS_DEFINE_UNARY_CONCEPT(is_range_class, R, is_detected<ranges::class_begin_t, R&>,
                            is_detected<ranges::class_end_t, R&>)
}; // namespace iris