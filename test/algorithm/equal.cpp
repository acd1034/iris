#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iris/algorithm/equal.hpp>
#include <iris/testing.hpp>
#include "../include/test_include.hpp"

iris::urng g(-10, 10);
TEMPLATE_TEST_CASE("algorithm equal", "[algorithm][equal]",
                   (std::array<int, 3>), std::forward_list<int>,
                   std::list<int>, std::vector<int>,
                   std::initializer_list<int>, int[]) {
  TestType a{1, 2, 3};
  CHECK(iris::equal(a, a));
  CHECK(iris::equal(a, TestType{1, 2, 3}));
  CHECK(iris::equal(TestType{1, 2, 3}, a));
  CHECK(iris::equal(TestType{1, 2, 3}, TestType{1, 2, 3}));

  CHECK(iris::equal(a, {1, 2, 3}));
  CHECK(iris::equal({1, 2, 3}, a));
  CHECK(iris::equal(TestType{1, 2, 3}, {1, 2, 3}));
  CHECK(iris::equal({1, 2, 3}, TestType{1, 2, 3}));

  using Array = int[];
  CHECK(iris::equal(a, Array{1, 2, 3}));
  CHECK(iris::equal(Array{1, 2, 3}, a));
  CHECK(iris::equal(TestType{1, 2, 3}, Array{1, 2, 3}));
  CHECK(iris::equal(Array{1, 2, 3}, TestType{1, 2, 3}));

  CHECK(!iris::equal(TestType{1, 2, 3}, {1, 2}));
  CHECK(!iris::equal(TestType{1, 2, 3}, {1, 2, -3}));
  CHECK(!iris::equal(TestType{1, 2, 3}, {1, 2, 3, 4}));
  CHECK(!iris::equal(TestType{g(), g(), g()}, {g(), g()}));
  CHECK(!iris::equal(TestType{g(), g(), 3}, {g(), g(), -3}));
  CHECK(!iris::equal(TestType{g(), g(), g()}, {g(), g(), g(), g()}));
}
TEMPLATE_TEST_CASE("algorithm equal", "[algorithm][equal]",
                   // (std::array<std::array<int, 2>, 3>),
                   std::forward_list<std::forward_list<int>>,
                   std::list<std::list<int>>, std::vector<std::vector<int>>,
                   std::initializer_list<std::initializer_list<int>>, int[][2]) {
  TestType a{{1, 2}, {3, 4}, {5, 6}};
  CHECK(iris::equal(a, a));
  CHECK(iris::equal(a, TestType{{1, 2}, {3, 4}, {5, 6}}));
  CHECK(iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, a));
  CHECK(iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, TestType{{1, 2}, {3, 4}, {5, 6}}));

  CHECK(iris::equal(a, {{1, 2}, {3, 4}, {5, 6}}));
  CHECK(iris::equal({{1, 2}, {3, 4}, {5, 6}}, a));
  CHECK(iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5, 6}}));
  CHECK(iris::equal({{1, 2}, {3, 4}, {5, 6}}, TestType{{1, 2}, {3, 4}, {5, 6}}));

  using Array = int[][2];
  CHECK(iris::equal(a, Array{{1, 2}, {3, 4}, {5, 6}}));
  CHECK(iris::equal(Array{{1, 2}, {3, 4}, {5, 6}}, a));
  CHECK(iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, Array{{1, 2}, {3, 4}, {5, 6}}));
  CHECK(iris::equal(Array{{1, 2}, {3, 4}, {5, 6}}, TestType{{1, 2}, {3, 4}, {5, 6}}));

  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5}}));
  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5, -6}}));
  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5, 6, 7}}));
  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}}));
  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {-5, -6}}));
  CHECK(!iris::equal(TestType{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {g(), g()}}, {{g(), g()}, {g(), g()}, {g()}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {g(), 6}}, {{g(), g()}, {g(), g()}, {g(), -6}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {g(), g()}}, {{g(), g()}, {g(), g()}, {g(), g(), g()}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {g(), g()}}, {{g(), g()}, {g(), g()}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {5, 6}}, {{g(), g()}, {g(), g()}, {-5, -6}}));
  CHECK(!iris::equal(TestType{{g(), g()}, {g(), g()}, {g(), g()}}, {{g(), g()}, {g(), g()}, {g(), g()}, {g(), g()}}));
}
