#include <bits/stdc++.h>
#include <iris/adaptors.hpp>
#include <iris/algorithm.hpp>
#include <iris/iostream.hpp>
int main() {
  using std::cout, std::begin, std::list;
  using namespace std::literals::string_literals;
  std::cout << std::boolalpha << "> ";
  list l{0, 1, 2};
  iris::equal(l, l) | cout;
  iris::equal({1, 2, 3}, {1, 2, 3}) | cout;
  iris::equal({{1}, {2}, {3}}, {{1}, {2}, {3}}) | cout;

  list{1, 2, 3, 4, 5} | iris::folded(0, [](auto x, auto y) { return x + y; })
    | cout;
  l | iris::folded(0, [](auto x, auto y) { return x + y; }) | cout;
  list{"hello"s, " "s, "world"s}
    | iris::folded("!"s, [](auto x, auto y) { return x + y; }) | cout;

  iris::iota_iterator j{"hello"s, [](auto i) { return i + "!"s; }};
  for (int i = 0; i < 10; ++i) cout << *j++ << " ";
  '\n' | cout;
  using namespace iris;
  iota_iterator k{1, [](auto i) { return ++i; }};
  const iota_iterator k2{1, [](auto i) { return ++i; }};
  using I = decltype(k);
  is_iterator_v<I> | cout;
  is_copyable_v<I> | cout;
  is_detected_dissatisfy_v<std::is_void, concepts::indirection_t, I&> | cout;
  is_detected_exact_v<I&, concepts::prefix_increment_t, I&> | cout;
  is_detected_v<concepts::postfix_increment_t, I&> | cout;
  is_movable_v<I> | cout;
  is_copy_constructible_v<I> | cout;
  is_assignable_from_v<I&, I const&> | cout;
  range r{iota_iterator{1, [](auto i) { return ++i; }}, unreachable_sentinel};
  range s{counted_iterator{begin(l), end(l), 2}, default_sentinel};
}
