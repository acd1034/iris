#include <bits/stdc++.h>
namespace ns1 {
  template <typename C>
  constexpr auto data(C& c) -> decltype(c.data()) {
    return c.data();
  }
  template <typename C>
  constexpr auto data(const C& c) -> decltype(c.data()) {
    return c.data();
  }
  template <typename T, std::size_t N>
  constexpr T* data(T (&array)[N]) noexcept {
    return array.data();
  }
  template <typename E>
  constexpr const E* data(std::initializer_list<E> il) noexcept {
    return std::begin(il);
  }
} // namespace ns1
namespace ns2 {
  template <typename T>
  constexpr decltype(auto) data(T&& x) {
    using ns1::data;
    return data(std::forward<T>(x));
  }
} // namespace ns2
#include <iris/testing.hpp>
long fibonacci(unsigned n) {
  if (n < 2) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}
int main() {
  iris::stop_watch w;
  w.start();
  std::cout << "f(42) = " << fibonacci(42) << '\n';
  w.stop();
  std::cout << w.seconds() << "sec" << '\n';
}
