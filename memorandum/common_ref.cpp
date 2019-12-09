#include <iris/common_reference.hpp>
#include <iris/iostream.hpp>
#include <typeinfo>
struct Base {};
struct Derived : Base {};
int main() {
  using std::cout;
  typedef iris::common_reference_t<char, short, int> A; // int?
  typedef iris::common_reference_t<float, double> B;    // double?
  typedef iris::common_reference_t<Derived, Base> C;    // Base?
  typedef iris::common_reference_t<Derived*, Base*> D;  // Base*?
  // typedef iris::common_reference_t<const int, volatile int> E; // int? -> error(ok?)
  typeid(A).name() | cout;
  typeid(B).name() | cout;
  typeid(C).name() | cout;
  typeid(D).name() | cout;
  // typeid(E).name() | cout;
}
