#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iris/algorithm.hpp>
#include <iris/experimental/iterator_traits.hpp>
#include "test_include.hpp"
static_assert(iris::is_regular_v<mini::strange_t>);

TEMPLATE_TEST_CASE_SIG("iterator concepts", "[iterator][concepts]",
                       ((typename T, bool B1, bool B2, bool B3, bool B4, bool B5), T, B1, B2, B3, B4, B5),
                       // (int, false, false, false, false, false),
                       // (mini::strange_t, false, false, false, false, false),
                       // (int*, true, true, true, true, true),
                       // (mini::strange_t*, true, true, true, true, true),
                       (mini::iter, true, false, false, false, false),
                       (std::istream_iterator<int>, true, true, true, false, false),
                       (std::forward_list<int>::iterator, true, true, true, false, false),
                       (std::list<int>::iterator, true, true, true, true, false),
                       (std::move_iterator<std::list<int>::iterator>, true, true, true, true, false),
                       (std::reverse_iterator<std::list<int>::iterator>, true, true, true, true, false),
                       (std::vector<int>::iterator, true, true, true, true, true),
                       (std::vector<mini::strange_t>::iterator, true, true, true, true, true)) {
  static_assert(iris::is_iterator_v<T> == B1);
  static_assert(iris::is_input_iterator_v<T> == B2);
  static_assert(iris::is_forward_iterator_v<T> == B3);
  static_assert(iris::is_bidirectional_iterator_v<T> == B4);
  static_assert(iris::is_random_access_iterator_v<T> == B5);
}
TEMPLATE_TEST_CASE_SIG("iterator concepts sentinel", "[iterator][concepts][sentinel]",
                       ((typename T, typename U, bool B), T, U, B),
                       (mini::iter, mini::iter, false),
                       (mini::iter, mini::sentinel, true),
                       (std::forward_list<int>::iterator, std::forward_list<int>::iterator, true)) {
  static_assert(iris::is_sentinel_for_v<T, U> == B);
}
TEMPLATE_TEST_CASE_SIG("iterator concepts output", "[iterator][concepts][output]",
                       ((typename T, typename U, bool B), T, U, B),
                       (std::ostream_iterator<int>, int, true),
                       (std::forward_list<int>::iterator, int, true),
                       (std::back_insert_iterator<std::forward_list<int>>, int, true),
                       (std::move_iterator<std::forward_list<int>::iterator>, int, false)) {
  static_assert(iris::is_output_iterator_v<T, U> == B);
}
