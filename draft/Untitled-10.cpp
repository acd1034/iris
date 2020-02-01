#include <bits/stdc++.h>
#include <iostream>
#include <iris/io.hpp>
#include <iris/utility.hpp>
int main() {
  using namespace iris::tuple_io;
  std::cout << iris::is_tuple_like_v<int[3]> << std::endl;
  int a[]{1, 2, 3};
  std::cout << iris::utility::get<2>(a) << std::endl;
  using Type = int[];
  std::cout << iris::utility::get<2>(Type{1, 2, 3}) << std::endl;
  std::cout << a << std::endl;
  std::cout << Type{1, 2, 3} << std::endl;
}
