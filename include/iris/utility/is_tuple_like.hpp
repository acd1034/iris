#pragma once
#include <iris/concepts/def_define_concept.hpp>
#include <iris/type_traits/is_detected.hpp>
#include <iris/utility/get.hpp>

namespace iris {
  // tuple-like
  namespace utility {
    template <std::size_t I, typename T>
    using adl_or_iris_get_t = decltype(get<I>(std::declval<T>()));

    template <typename, typename>
    struct has_get_impl : std::false_type {};
    template <typename T, std::size_t... Indices>
    struct has_get_impl<T, std::index_sequence<Indices...>>
      : std::bool_constant<((is_detected_v<adl_or_iris_get_t, Indices, T>)&&...)> {};
    template <typename T>
    using has_get =
      has_get_impl<T,
                   std::index_sequence<detected_t<std::tuple_size, T>::value>>;
    template <typename T>
    inline constexpr bool has_get_v = has_get<T>::value;

    template <typename, typename>
    struct has_tuple_element_impl : std::false_type {};
    template <typename T, std::size_t... Indices>
    struct has_tuple_element_impl<T, std::index_sequence<Indices...>>
      : std::bool_constant<((is_detected_v<std::tuple_element, Indices, T>)&&...)> {};
    // template <typename T, std::size_t... Indices>
    // struct has_tuple_element_impl<T, std::index_sequence<Indices...>>
    //   : std::conjunction<is_detected<std::tuple_element, Indices, T>...> {};
    template <typename T>
    using has_tuple_element = has_tuple_element_impl<
      T,
      std::index_sequence<detected_t<std::tuple_size, T>::value>>;
    template <typename T>
    inline constexpr bool has_tuple_element_v = has_tuple_element<T>::value;
  } // namespace utility
  // clang-format off
  IRIS_DEFINE_UNARY_CONCEPT(is_tuple_like, T,
                            is_detected<std::tuple_size, T>,
                            is_detected<utility::has_get, T>,
                            is_detected<utility::has_tuple_element, T>)
  // clang-format on
} // namespace iris
