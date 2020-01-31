
#include <bits/stdc++.h>
#include <iris/experimental/delegate.hpp>

int main() {
  using std::cout, std::list;
  cout << std::boolalpha;
  using iris::equal;
  list l{1, 2, 3};
  equal(l, list{1, 2, 3}) | cout;
  equal(l, {1, 2, 3}) | cout;
  equal(list{1, 2, 3}, list{1, 2, 3, 4}) | cout;

  equal(list{1, 2, 3}, list{1, 2, 3}) | cout;
  equal(list{1, 2, 3}, {1, 2, 3}) | cout;
  equal({1, 2, 3}, list{1, 2, 3}) | cout;
  equal({1, 2, 3}, {1, 2, 3}) | cout;
  equal(list{list{1}, list{2}, list{3}}, list{list{1}, list{2}, list{3}}) | cout;
  equal(list{list{1}, list{2}, list{3}}, {{1}, {2}, {3}}) | cout;
  equal({{1}, {2}, {3}}, list{list{1}, list{2}, list{3}}) | cout;
  equal({{1}, {2}, {3}}, {{1}, {2}, {3}}) | cout;

  int a[]{1, 2, 3};
  equal(a, a);
  using Array = int[];
  Array b{0, 1, 2, 3, 4};
  iris::equal(b, Array{0, 1, 2, 3, 4}) | cout;
  iris::equal(Array{1, 2, 3, 4, 5, 6}, Array{0, 1, 2, 3, 4}) | cout;
}
