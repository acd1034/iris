#include <bits/stdc++.h>
#include <iris/io.hpp>
#include <iris/utility/is_tuple_like.hpp>
// after is_tuple_like.hpp
#include <iris/utility/array_as_tuple.hpp>

int main() {
  using namespace iris::tuple_io;
  std::cout << std::boolalpha << iris::is_tuple_like_v<int[3]> << std::endl;
  int a[]{1, 2, 3};
  using iris::get;
  std::cout << get<2>(a) << std::endl;
  using Type = int[];
  std::cout << get<2>(Type{1, 2, 3}) << std::endl;
  std::cout << a << std::endl;
  std::cout << Type{1, 2, 3} << std::endl;
}
