#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array>
TEMPLATE_TEST_CASE_SIG("iterator concept", "[iterator][concept]",
                       ((typename T, bool B), T, B),
                       (int, true)) {}
TEMPLATE_TEST_CASE_SIG("TemplateTestSig: arrays can be created from NTTP arguments", "[vector][template][nttp]",
                       ((typename T, int V), T, V), (int, 5), (float, 4), (std::string, 15), ((std::tuple<int, float>), 6)) {
  std::array<T, V> v;
  REQUIRE(v.size() > 1);
}
TEMPLATE_TEST_CASE_SIG("TemplateTestSig: arrays can be created from NTTP arguments", "[vector][template][nttp]",
                       ((typename T, bool B), T, B), (int, true), (float, true), (std::string, false), ((std::tuple<int, float>), false)) {
  static_assert(std::is_arithmetic_v<T> == B);
}
