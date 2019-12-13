#include <bits/stdc++.h>
#include <iris/iostream.hpp>

int main() {
  using namespace iris;
  using std::cout;
  cout << std::boolalpha;
  using T = std::ostream_iterator<int>&;
  using U = int;
  std::is_lvalue_reference_v<T> | cout;
  is_common_reference_with_v<std::remove_reference_t<T> const&,
                             std::remove_reference_t<U> const&> | cout;
  is_detected_exact_v<T, concepts::assign_t, T, U> | cout;
}
