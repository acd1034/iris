#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
#include <catch.hpp>
#include <iris/iterator.hpp>
#include <iris/utility.hpp>

namespace ns {
  struct mini_iter {
    using difference_type = int;
    using value_type      = int;
    int i                 = 0;
    int operator*() const { return i; }
    int const* operator->() const { return std::addressof(i); }
    mini_iter& operator++() { return *this; }
    mini_iter operator++(int) {
      auto result = *this;
      return result;
    }
  };
  bool operator==(mini_iter const&, mini_iter const&);
  bool operator!=(mini_iter const&, mini_iter const&);
} // namespace ns

TEST_CASE("iterator concept", "[iterator]") {
  // clang-format off
  static_assert( iris::is_output_iterator_v<std::ostream_iterator<int>, int>);
  static_assert( iris::is_output_iterator_v<std::back_insert_iterator<std::forward_list<int>>, int>);
  static_assert( iris::is_output_iterator_v<std::forward_list<int>::iterator, int>);
  static_assert(!iris::is_output_iterator_v<std::move_iterator<std::list<int>::iterator>, int>);

  static_assert(!iris::is_input_iterator_v<int*>);
  static_assert( iris::is_input_iterator_v<std::istream_iterator<int>>);
  static_assert( iris::is_forward_iterator_v<std::istream_iterator<int>>);
  static_assert( iris::is_forward_iterator_v<std::forward_list<int>::iterator>);
  static_assert( iris::is_forward_iterator_v<ns::mini_iter>);
  static_assert(!iris::is_bidirectional_iterator_v<std::forward_list<int>::iterator>);
  static_assert(!iris::is_bidirectional_iterator_v<ns::mini_iter>);
  static_assert( iris::is_bidirectional_iterator_v<std::list<int>::iterator>);
  static_assert( iris::is_bidirectional_iterator_v<std::move_iterator<std::list<int>::iterator>>);
  static_assert( iris::is_bidirectional_iterator_v<std::reverse_iterator<std::list<int>::iterator>>);
  static_assert(!iris::is_random_access_iterator_v<std::list<int>::iterator>);
  static_assert(!iris::is_random_access_iterator_v<std::move_iterator<std::list<int>::iterator>>);
  static_assert(!iris::is_random_access_iterator_v<std::reverse_iterator<std::list<int>::iterator>>);
  static_assert( iris::is_random_access_iterator_v<std::vector<int>::iterator>);
  // clang-format on
}

TEST_CASE("iterator operation", "[iterator]") {
  // clang-format off
  {
    using Array = std::forward_list<int>;
    Array a{0,1,2,3,4};
    auto i = std::begin(a);
    using It = decltype(i);
    static_assert(std::is_same_v<iris::iterator_traits<It>::iterator_category, std::forward_iterator_tag>);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 0);
    REQUIRE(iris::iterator_traits<It>::distance(i, std::end(a)) == 5);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::advance(i)) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::next(i)) == 2);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::at(i, 2) == 3);
    REQUIRE(a == Array{0,1,2,3,4});
    int n = -1;
    iris::iterator_traits<It>::assign(i, n);
    REQUIRE(iris::iterator_traits<It>::deref(i) == -1);
    REQUIRE(a == Array{0,-1,2,3,4});
  }
  {
    using Array = std::forward_list<int>;
    Array a{0,1,2,3,4};
    using It = decltype(std::begin(a));
    static_assert(std::is_same_v<iris::iterator_traits<It>::iterator_category, std::forward_iterator_tag>);
    REQUIRE(iris::iterator_traits<It>::deref(std::begin(a)) == 0);
    REQUIRE(iris::iterator_traits<It>::distance(std::begin(a), std::end(a)) == 5);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::advance(std::begin(a))) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(std::begin(a)) == 0);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::next(std::begin(a))) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(std::begin(a)) == 0);
    iris::iterator_traits<It>::at(std::begin(a),2) = -1;
    REQUIRE(a == Array{0,1,-1,3,4});
    iris::iterator_traits<It>::assign(std::begin(a), -1);
    REQUIRE(iris::iterator_traits<It>::deref(std::begin(a)) == -1);
    REQUIRE(a == Array{-1,1,-1,3,4});
  }
  {
    using Array = std::list<int>;
    Array a{0,1,2,3,4};
    auto i = std::begin(a);
    using It = decltype(i);
    static_assert(std::is_same_v<iris::iterator_traits<It>::iterator_category, std::bidirectional_iterator_tag>);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 0);
    REQUIRE(iris::iterator_traits<It>::distance(i, std::end(a)) == 5);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::advance(i)) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::next(i)) == 2);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::at(i, 2) == 3);
    REQUIRE(a == Array{0,1,2,3,4});
    iris::iterator_traits<It>::assign(i, -1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == -1);
    REQUIRE(a == Array{0,-1,2,3,4});
  }
  {
    using Array = std::list<int>;
    Array a{0,1,2,3,4};
    auto i = std::end(a);
    using It = decltype(i);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::retreat(i)) == 4);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 4);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::prev(i)) == 3);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 4);
    REQUIRE(iris::iterator_traits<It>::at(i, -2) == 2);
    REQUIRE(a == Array{0,1,2,3,4});
    iris::iterator_traits<It>::assign(i, -1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == -1);
    REQUIRE(a == Array{0,1,2,3,-1});
  }
  {
    using Array = int[];
    Array a{0,1,2,3,4};
    auto i = std::begin(a);
    using It = decltype(i);
    static_assert(std::is_same_v<iris::iterator_traits<It>::iterator_category, std::random_access_iterator_tag>);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 0);
    REQUIRE(iris::iterator_traits<It>::distance(i, std::end(a)) == 5);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::advance(i)) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::deref(iris::iterator_traits<It>::next(i)) == 2);
    REQUIRE(iris::iterator_traits<It>::deref(i) == 1);
    REQUIRE(iris::iterator_traits<It>::at(i, 2) == 3);
    REQUIRE(iris::equal(a, Array{0,1,2,3,4}));
    iris::iterator_traits<It>::assign(i, -1);
    REQUIRE(iris::iterator_traits<It>::deref(i) == -1);
    REQUIRE(iris::equal(a, Array{0,-1,2,3,4}));
  }
  // clang-format on
}
