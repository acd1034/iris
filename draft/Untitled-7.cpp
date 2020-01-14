#include <bits/stdc++.h>
#include <iris/iostream.hpp>
#include <iris/semiregular_box.hpp>

template <class T>
[[deprecated]] void type(T&&) {} int main() {
  using std::cout;
  using namespace iris;
  struct dconstructible {
  } d;
  struct ndconstructible {
    ndconstructible() = delete;
    ndconstructible(int){};
  } nd{1};
  struct assignable {
  } a;
  struct nassignable {
    nassignable& operator=(nassignable const&) = delete;
  } na;
  {
    semiregular_box<dconstructible> b;
    semiregular_box b2{d};
    b2 = b;
    std::cout << std::endl;
  }
  {
    semiregular_box<ndconstructible> b;
    semiregular_box b2{nd};
    b2 = b;
    std::cout << std::endl;
  }
  {
    semiregular_box b{a};
    b = a;
    std::cout << std::endl;
  }
  {
    semiregular_box b{na};
    b = na;
    std::cout << std::endl;
  }
  {
    semiregular_box<long> b{semiregular_box<int>{1}};
    b = semiregular_box<int>{1};
  }
}
