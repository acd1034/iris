#include <iris/iostream.hpp>

namespace ns {
  struct not_having {};
  struct having {
    void operator++() {}
    int operator++(int) { return 0; }
  };
} // namespace ns

int main() {
  using std::cout;
  cout << std::boolalpha;
  //  d &&  s
  //  d && ds
  // nd &&  s
  // nd && ds
  // clang-format off
  iris::is_detected_satisfy_v<std::is_void, iris::prefix_increment_t, ns::having> | cout;
  iris::is_detected_satisfy_v<std::is_void, iris::postfix_increment_t, ns::having> | cout;
  iris::is_detected_satisfy_v<std::is_void, iris::prefix_increment_t, ns::not_having> | cout;
  iris::is_detected_satisfy_v<std::is_void, iris::postfix_increment_t, ns::not_having> | cout;
  cout << std::endl;
  iris::is_detected_dissatisfy_v<std::is_void, iris::prefix_increment_t, ns::having> | cout;
  iris::is_detected_dissatisfy_v<std::is_void, iris::postfix_increment_t, ns::having> | cout;
  iris::is_detected_dissatisfy_v<std::is_void, iris::prefix_increment_t, ns::not_having> | cout;
  iris::is_detected_dissatisfy_v<std::is_void, iris::postfix_increment_t, ns::not_having> | cout;
}
