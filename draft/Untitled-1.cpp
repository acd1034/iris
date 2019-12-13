#include <bits/stdc++.h>
#include <iris/iostream.hpp>

namespace ns {
  struct not_having {};
  struct mini_range {};
  int begin(mini_range) { return 0; }
  int end(mini_range) { return 1; }
  struct mini_iter {
    using difference_type = int;
    using value_type      = int;
    int i                 = 0;
    int operator*() const { return i; }
    int const* operator->() const { return std::addressof(i); }
    mini_iter& operator++() { return *this; }
    mini_iter operator++(int) {
      auto result = *this;
      return result;
    }
  };
  bool operator==(mini_iter const&, mini_iter const&);
  bool operator!=(mini_iter const&, mini_iter const&);

  template <typename T>
  [[deprecated]] void typer(T) {}
} // namespace ns

int main() {
  using std::cout;
  cout << std::boolalpha;
  iris::is_range_v<std::vector<int>> | cout;
  iris::is_range_v<ns::mini_range> | cout;
  iris::is_range_v<ns::not_having> | cout;
}
