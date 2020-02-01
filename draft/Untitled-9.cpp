#include <bits/stdc++.h>
#include <iris/utility/is_tuple_like.hpp>
class X;
template <>
struct std::tuple_size<X> : std::integral_constant<std::size_t, 1> {};
template <>
struct std::tuple_element<0, X> {
  using type = int;
};
class X {
  int i = 0;

public:
  template <std::size_t I>
  std::tuple_element_t<I, X> get() = delete;
  template <>
  std::tuple_element_t<0, X> get<0>() { return i; }
};
#include <iostream>
int main() {
  std::cout << std::boolalpha << iris::is_tuple_like_v<X>;
}
