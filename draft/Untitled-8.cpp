
#include <bits/stdc++.h>
#include <iris/experimental/delegate.hpp>

int main() {
  using std::cout, std::list;
  cout << std::boolalpha;
  using iris::equal;
  list l{1, 2, 3};
  equal(l, list{1, 2, 3}) | cout;
  equal(l, {1, 2, 3}) | cout;

  equal(list{1, 2, 3}, list{1, 2, 3}) | cout;
  equal(list{1, 2, 3}, {1, 2, 3}) | cout;
  equal({1, 2, 3}, list{1, 2, 3}) | cout;
  equal({1, 2, 3}, {1, 2, 3}) | cout;
  equal(list{list{1}, list{2}, list{3}}, list{list{1}, list{2}, list{3}}) | cout;
  equal(list{list{1}, list{2}, list{3}}, {{1}, {2}, {3}}) | cout;
  equal({{1}, {2}, {3}}, list{list{1}, list{2}, list{3}}) | cout;
  equal({{1}, {2}, {3}}, {{1}, {2}, {3}}) | cout;

  using Array = int[];
  iris::equal(Array{1, 2, 3}, Array{1, 2, 3}) | cout;
  iris::equal(list{1, 2, 3}, Array{1, 2, 3}) | cout;
  iris::equal(Array{1, 2, 3}, list{1, 2, 3}) | cout;
  iris::equal({1, 2, 3}, Array{1, 2, 3}) | cout;
  iris::equal(Array{1, 2, 3}, {1, 2, 3}) | cout;
  using Array2 = int[][2];
  Array2 a{{1, 2}, {3, 4}};
  iris::equal(a, Array2{{1, 2}, {3, 4}}) | cout;
  iris::equal(a, {{1, 2}, {3, 4}}) | cout;
  iris::equal(a, {{1, 2}, {3, 4, 5}}) | cout;
}
