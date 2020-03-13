// https://brevzin.github.io/c++/2020/01/15/abbrev-lambdas/
#define IRIS_ABBREV_LAMBDA(expr) \
  noexcept(noexcept(expr))->decltype((expr)) { return expr; }
namespace iris {
  template <typename T>
  constexpr auto begin(T& c) IRIS_ABBREV_LAMBDA(c.begin())
}

#include <iostream>
#include <vector>
int main() {
  std::vector<int> v{1};
  std::cout << *iris::begin(v) << std::endl;
  auto f = [](auto& c) IRIS_ABBREV_LAMBDA(c.data());
  std::cout << *f(v) << std::endl;
}
