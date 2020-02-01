#include <array>
#include <iostream>
#include <iris/utility/is_tuple_like.hpp>

int main() {
  using std::cout;
  cout << std::boolalpha;
  cout << iris::is_tuple_like_v<int> << std::endl;
  cout << iris::is_tuple_like_v<int const> << std::endl;
  cout << iris::is_tuple_like_v<int volatile> << std::endl;
  cout << iris::is_tuple_like_v<int*> << std::endl;
  cout << iris::is_tuple_like_v<int&> << std::endl;
  std::cout << std::endl;
  cout << iris::is_tuple_like_v<std::pair<int, int>> << std::endl;
  cout << iris::is_tuple_like_v<std::pair<int, int> const> << std::endl;
  cout << iris::is_tuple_like_v<std::pair<int, int> volatile> << std::endl;
  cout << iris::is_tuple_like_v<std::pair<int, int>*> << std::endl;
  cout << iris::is_tuple_like_v<std::pair<int, int>&> << std::endl;
  cout << iris::is_tuple_like_v<std::tuple<int, int>> << std::endl;
  cout << iris::is_tuple_like_v<std::array<int, 1>> << std::endl;
  // std::cout << std::endl;
  // using Type = std::array<int, 1>;
  // cout << iris::is_detected_v<std::tuple_size, Type> << std::endl;
  // cout << iris::is_detected_v<iris::utility::has_tuple_element, Type> << std::endl;
  // cout << iris::is_detected_v<iris::utility::has_get, Type> << std::endl;
}
