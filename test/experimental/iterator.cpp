#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iris/algorithm.hpp>
#include <iris/experimental/iterator_traits.hpp>
#include "test_include.hpp"

TEMPLATE_TEST_CASE("iterator traits forward", "[iterator][traits][forward]",
                   int[], std::forward_list<int>, std::list<int>, std::vector<int>) {
  TestType a{0, 1, 2, 3, 4};
  using std::begin, std::end;
  auto i       = begin(a);
  using traits = iris::iterator_traits<decltype(i)>;
  static_assert(std::is_base_of_v<std::forward_iterator_tag, typename traits::iterator_category>);
  CHECK(traits::deref(i) == 0);
  CHECK(traits::distance(i, end(a)) == 5);
  CHECK(traits::deref(traits::advance(i)) == 1);
  CHECK(traits::deref(i) == 1);
  CHECK(traits::deref(traits::next(i)) == 2);
  CHECK(traits::deref(i) == 1);
  CHECK(traits::at(i, 2) == 3);
  CHECK(iris::equal(a, TestType{0, 1, 2, 3, 4}));
  int n = -1;
  traits::assign(i, n);
  CHECK(traits::deref(i) == -1);
  CHECK(iris::equal(a, TestType{0, -1, 2, 3, 4}));
}
TEMPLATE_TEST_CASE("iterator traits rvalue", "[iterator][traits][rvalue]",
                   int[], std::forward_list<int>, std::list<int>, std::vector<int>) {
  TestType a{0, 1, 2, 3, 4};
  using std::begin, std::end;
  using traits = iris::iterator_traits<decltype(begin(a))>;
  static_assert(std::is_base_of_v<std::forward_iterator_tag, typename traits::iterator_category>);
  CHECK(traits::deref(begin(a)) == 0);
  CHECK(traits::distance(begin(a), end(a)) == 5);
  CHECK(traits::deref(traits::advance(begin(a))) == 1);
  CHECK(traits::deref(begin(a)) == 0);
  CHECK(traits::deref(traits::next(begin(a))) == 1);
  CHECK(traits::deref(begin(a)) == 0);
  traits::at(begin(a), 2) = -1;
  CHECK(iris::equal(a, TestType{0, 1, -1, 3, 4}));
  traits::assign(begin(a), -1);
  CHECK(traits::deref(begin(a)) == -1);
  CHECK(iris::equal(a, TestType{-1, 1, -1, 3, 4}));
}
TEMPLATE_TEST_CASE("iterator traits bidirectional", "[iterator][traits][bidirectional]",
                   int[], std::list<int>, std::vector<int>) {
  TestType a{0, 1, 2, 3, 4};
  using std::end;
  auto i       = end(a);
  using traits = iris::iterator_traits<decltype(i)>;
  static_assert(std::is_base_of_v<std::bidirectional_iterator_tag, typename traits::iterator_category>);
  CHECK(traits::deref(traits::retreat(i)) == 4);
  CHECK(traits::deref(i) == 4);
  CHECK(traits::deref(traits::prev(i)) == 3);
  CHECK(traits::deref(i) == 4);
  CHECK(traits::at(i, -2) == 2);
  CHECK(iris::equal(a, TestType{0, 1, 2, 3, 4}));
  traits::assign(i, -1);
  CHECK(traits::deref(i) == -1);
  CHECK(iris::equal(a, TestType{0, 1, 2, 3, -1}));
}
