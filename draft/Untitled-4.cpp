#include <bits/stdc++.h>
#include <iris/experimental/delegate.hpp>

int main() {
  using std::cout;
  using namespace std::literals::string_literals;
  cout << std::boolalpha;
  iris::is_tuple_like_v<int> | cout;
  iris::is_tuple_like_v<int const> | cout;
  iris::is_tuple_like_v<int volatile> | cout;
  iris::is_tuple_like_v<int*> | cout;
  iris::is_tuple_like_v<int&> | cout;
  iris::is_tuple_like_v<std::pair<int, int>> | cout;
  iris::is_tuple_like_v<std::pair<int, int> const> | cout;
  iris::is_tuple_like_v<std::pair<int, int> volatile> | cout;
  iris::is_tuple_like_v<std::pair<int, int>*> | cout;
  iris::is_tuple_like_v<std::pair<int, int>&> | cout;
  iris::is_tuple_like_v<std::tuple<int, int>> | cout;
  iris::is_tuple_like_v<std::array<int, 1>> | cout;
  // using T = std::pair<int, int>&;
  // iris::is_detected_v<std::tuple_size, T> | cout; // true
  // iris::is_detected_v<iris::utility::has_tuple_element, T> | cout; // false
  // iris::is_detected_v<iris::utility::has_get, T> | cout; // false
  // std::is_same_v<std::tuple_element_t<0, T>, int> | cout; // compile error!
  iris::is_range_v<std::string> | cout;
  iris::is_range_v<std::array<int, 1>> | cout;
  cout << std::pair{1, "2s"s} << "v ";
  cout << std::tuple{
    1,
    'a',
    "hello"s,
  } << "v ";
  cout << std::array{1, 2, 3} << "v ";
}
