#pragma once
#include <algorithm>
#include <utility>

#include <iris/def_define_concept.hpp>

namespace iris {
  // equal
  // clang-format off
  template <typename R1, typename R2>
  bool equal(R1 const& lhs, R2 const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(R const& lhs, std::initializer_list<T> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(std::initializer_list<T> const& lhs, R const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename T, typename U>
  bool equal(std::initializer_list<T> const& lhs, std::initializer_list<U> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(R const& lhs, std::initializer_list<std::initializer_list<T>> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  template <typename R, typename T>
  bool equal(std::initializer_list<std::initializer_list<T>> const& lhs, R const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  template <typename T, typename U>
  bool equal(std::initializer_list<std::initializer_list<T>> const& lhs, std::initializer_list<std::initializer_list<U>> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  // clang-format on

  // tuple-like
  namespace utility {
    template <std::size_t I, typename T>
    using member_get_t = decltype(std::declval<T>().template get<I>());
    template <std::size_t I, typename T>
    using std_get_t = decltype(std::get<I>(std::declval<T>()));

    template <typename, typename>
    struct has_get_impl : std::false_type {};
    template <typename T, std::size_t... Indices>
    struct has_get_impl<T, std::index_sequence<Indices...>>
      : std::bool_constant<(
          true && ...
          && (is_detected_v<member_get_t,
                            Indices,
                            T> || is_detected_v<std_get_t, Indices, T>))> {};
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
      : std::bool_constant<(
          true && ... && is_detected_v<std::tuple_element, Indices, T>)> {};
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
                            is_detected<utility::has_tuple_element, T>,
                            is_detected<utility::has_get, T>)
  // clang-format on
} // namespace iris
