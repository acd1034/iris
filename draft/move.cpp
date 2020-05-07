#include <iostream>
struct X {
  X() { std::cout << "dc" << std::endl; }
  X(X const&) { std::cout << "cc" << std::endl; }
  X(X&&) { std::cout << "mc" << std::endl; }
  X operator+() const& { return *this; }
  X&& operator+() && { return std::move(*this); }
};
X f(X const& x) { return x; }
X&& f(X&& x) { return std::move(x); }
X&& g(X&& x) { return f(std::move(x)); }
int main() {
  // X x;
  // std::ignore = +x;
  // std::cout << std::endl;
  // std::ignore = +X{};

  // f(X{});
  g(X{});
}
