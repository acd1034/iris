#pragma once
#include <iris/utility/get.hpp>

// patial specialization of std::tuple_size, std::tuple_element for built-in array
template <typename T, std::size_t N>
struct std::tuple_size<T[N]> : std::integral_constant<std::size_t, N> {};
template <std::size_t I, typename T, std::size_t N>
struct std::tuple_element<I, T[N]> {
  using type = std::enable_if_t<(I < N), T>;
};
