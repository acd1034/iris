#include <bits/stdc++.h>
#include <iris/concepts.hpp>
#include <iris/io.hpp>
inline namespace a {
  template <class T, std::enable_if_t<!iris::is_equality_comparable_v<T>, std::nullptr_t> = nullptr>
  bool operator==(const T&, const T&) {
    std::cout << "global" << std::endl;
    return true;
  }
} // namespace a
inline namespace b {
  template <class T, std::enable_if_t<!iris::is_equality_comparable_v<T>, std::nullptr_t> = nullptr>
  bool operator==(const T&, const T&) {
    std::cout << "global2" << std::endl;
    return false;
  }
} // namespace b

#include <iostream>
int main() {
  1 == 2;
  struct X {};
  // X{} == X{}; // error
  using namespace iris::io::ranges;
  using namespace iris::io::tuple;
  using namespace iris::io::delegate;
  std::cout << std::array{1, 2, 3} << std::endl;
}
