#include <iostream>
#include <iris/experimental/delegate.hpp>

template <class T>
[[deprecated]] void type(T&&) {}
int main() {
  using std::cout;
  using namespace iris;
  {
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
    std::cout << std::endl;
  }
  {
    // move
    // emplace
    struct as {
      as()          = default;
      as(const as&) = default;
      as(as&&)      = default;
      as& operator  =(const as&) {
        std::cout << "  as&" << std::endl;
        return *this;
      }
      as& operator=(as&&) {
        std::cout << "  as&&" << std::endl;
        return *this;
      }
    } a;
    struct nas {
      nas() = default;
      nas(const nas&) {
        std::cout << "  nas&" << std::endl;
      }
      nas(nas&&) {
        std::cout << "  nas&&" << std::endl;
      }
      nas& operator=(const nas&) = delete;
      nas& operator=(nas&&) = delete;
    } n;
    semiregular_box s1{a};
    s1 = a;
    s1 = as{};
    std::cout << std::endl;
    semiregular_box s2{n};
    s2 = n;
    s2 = nas{};
  }
}
