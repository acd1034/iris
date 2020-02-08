#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <type_traits>

TEMPLATE_TEST_CASE("iterator concept", "[iterator][concept]", int) {
  static_assert(std::is_arithmetic_v<TestType>);
}
TEMPLATE_TEST_CASE_SIG("iterator concept", "[iterator][concept]",
                       ((typename T, bool B), T, B),
                       (int, true)) {
  static_assert(std::is_arithmetic_v<T> == B);
}
