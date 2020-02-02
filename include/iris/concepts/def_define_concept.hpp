#pragma once
#include <type_traits>
#include <iris/preprocessor.hpp>

// iris grobal namespace
#ifndef IRIS_DEFINE_UNARY_CONCEPT
#define IRIS_DEFINE_UNARY_CONCEPT(Name, Type, ...) \
  template <typename Type>                         \
  using Name = std::conjunction<__VA_ARGS__>;      \
  template <typename Type>                         \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type>::value;
#endif
#ifndef IRIS_DEFINE_BNARY_CONCEPT
#define IRIS_DEFINE_BNARY_CONCEPT(Name, Type1, Type2, ...) \
  template <typename Type1, typename Type2>                \
  using Name = std::conjunction<__VA_ARGS__>;              \
  template <typename Type1, typename Type2>                \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2>::value;
#endif
#ifndef IRIS_DEFINE_VARIA_CONCEPT
#define IRIS_DEFINE_VARIA_CONCEPT(Name, Type1, Type2, ...) \
  template <typename Type1, typename... Type2>             \
  using Name = std::conjunction<__VA_ARGS__>;              \
  template <typename Type1, typename... Type2>             \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2...>::value;
#endif
// end of iris grobal namespace
