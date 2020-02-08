#include <iris/testing.hpp>
#include <iostream>
long fibonacci(unsigned n) {
  if (n < 2) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}
int main() {
  iris::stop_watch w;
  w.start();
  std::cout << "f(40) = " << fibonacci(40) << '\n';
  w.stop();
  std::cout << w.seconds() << "sec\n\n";

  iris::urng g(0, 10);
  for (std::size_t i = 0; i < 3; ++i) std::cout << g() << std::endl;
  g.set_range(0, -10);
  for (std::size_t i = 0; i < 3; ++i) std::cout << g() << std::endl;
}
