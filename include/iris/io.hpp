#pragma once
#include <iostream> // std::basic_ostream
#include <iris/ranges.hpp>
#include <iris/utility.hpp>

// iris grobal namespace
// range operator<<
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

// tuple-like operator<<
namespace iris {
  namespace iostream {
    template <class CharT, class Traits, class T, std::size_t... Indicies>
    auto& tuple_print(std::basic_ostream<CharT, Traits>& os,
                      const T& t,
                      std::index_sequence<Indicies...>) {
      const char* dlm = "";
      using swallow   = std::initializer_list<int>;
      (void)swallow{
        (void(std::cout << std::exchange(dlm, " ") << std::get<Indicies>(t)),
         0)...};
      return os;
    }
  } // namespace iostream
} // namespace iris
template <
  class CharT,
  class Traits,
  class T,
  iris::enable_if_t<iris::is_tuple_like_v<T> && !iris::is_range_v<T>> = nullptr>
auto& operator<<(std::basic_ostream<CharT, Traits>& os, const T& t) {
  return iris::iostream::tuple_print(
    os, t, std::make_index_sequence<std::tuple_size_v<T>>{});
}

template <class T, class CharT, class Traits>
void operator|(const T& t, std::basic_ostream<CharT, Traits>& os) {
  os << t << std::endl;
}
// end of iris grobal namespace
