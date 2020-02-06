#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iris/ranges.hpp>
#include "test_include.hpp"
static_assert(iris::is_regular_v<mini::strange_t>);

TEMPLATE_TEST_CASE_SIG("range concepts", "[range][concepts]",
                       ((typename T, bool B1, bool B2, bool B3, bool B4, bool B5), T, B1, B2, B3, B4, B5),
                       // (int, false, false, false, false, false),
                       // (mini::strange_t, false, false, false, false, false),
                       // (mini::range<int*>, true, true, true, true, true),
                       // (mini::range<mini::strange_t*>, true, true, true, true, true),
                       (mini::range<mini::iter>, true, false, false, false, false),
                       (mini::range<std::istream_iterator<int>>, true, true, true, false, false),
                       (std::forward_list<int>, true, true, true, false, false),
                       (std::list<int>, true, true, true, true, false),
                       (mini::range<std::move_iterator<std::list<int>::iterator>>, true, true, true, true, false),
                       (mini::range<std::reverse_iterator<std::list<int>::iterator>>, true, true, true, true, false),
                       (std::vector<int>, true, true, true, true, true),
                       (std::vector<mini::strange_t>, true, true, true, true, true)) {
  static_assert(iris::is_range_v<T> == B1);
  static_assert(iris::is_input_range_v<T> == B2);
  static_assert(iris::is_forward_range_v<T> == B3);
  static_assert(iris::is_bidirectional_range_v<T> == B4);
  static_assert(iris::is_random_access_range_v<T> == B5);
}
