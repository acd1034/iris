#include <bits/stdc++.h>
#include <iris/iostream.hpp>
struct Base {};
struct Derived : Base {};
namespace ns {
  // customization point
  class X {
    int y = 0;

  public:
    explicit X(int y) : y(y) {}
    void print() { std::cout << y << ' '; }
    /* 違う!
    void swap(X& x) {} */
  };
  // これが正しい
  void swap(X&, X&) {}
} // namespace ns

int main() {
  using std::cout;
  cout << std::boolalpha;
  ns::X x{1}, y{2};
  // std::swap(x, y);
  using std::swap;
  swap(x, y);
  x.print();
  y.print();
  // using T = std::ostream_iterator<int>&;
  // using U = int;
  // std::is_lvalue_reference_v<T> | cout;
  // is_common_reference_with_v<std::remove_reference_t<T> const&,
  //                            std::remove_reference_t<U> const&> | cout;
  // is_detected_exact_v<T, concepts::assign_t, T, U> | cout;
}
