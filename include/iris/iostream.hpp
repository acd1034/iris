#pragma once
#include <iostream>

#include <iris/ranges.hpp>

// iris grobal namespace
template <
  class CharT,
  class Traits,
  class R,
  iris::enable_if_t<
    iris::is_range_v<R> && !iris::is_range_v<iris::range_value_t<R>>> = nullptr>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  const char* dlm = "";
  for (const auto& x : r) os << std::exchange(dlm, " ") << x;
  return os;
}
template <
  class CharT,
  class Traits,
  class R,
  iris::enable_if_t<
    iris::is_range_v<R> && iris::is_range_v<iris::range_value_t<R>>> = nullptr>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
  const char* dlm = "";
  for (const auto& x : r) os << std::exchange(dlm, "\n") << x;
  return os;
}
template <class T, class CharT, class Traits>
void operator|(const T& t, std::basic_ostream<CharT, Traits>& os) {
  os << t << std::endl;
}
// end of iris grobal namespace
