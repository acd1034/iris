#include <bits/stdc++.h>
#include <iris/experimental/delegate.hpp>
int main() {
  using std::cout, std::begin, std::end, std::list;
  using namespace iris::experimental;
  std::cout << std::boolalpha << "> ";
  list l{0, 1, 2};
  iota(0, [](auto i) { return 2 * i + 1; }) | counted(12) | cout;
  l | counted(5) | cout;
  // FIXME:
  // iota(0) | counted(5) | cout;
  // iota(0) | counted(5) | folded(0, [](int i, int j) { return i + j; }) | cout;
}
