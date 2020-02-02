#pragma once
#include <ostream>                        // std::basic_ostream
#include <iris/ranges.hpp>                // is_range
#include <iris/utility/is_tuple_like.hpp> // is_tuple_like

namespace iris {
  inline namespace io {
    inline namespace ranges_io {
      // range operator<<
      template <
        class CharT,
        class Traits,
        class R,
        enable_if_t<
          is_range_v<R> && !is_range_v<range_value_t<R>>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
        const char* dlm = "";
        for (const auto& x : r) os << std::exchange(dlm, " ") << x;
        return os;
      }
      template <
        class CharT,
        class Traits,
        class R,
        enable_if_t<
          is_range_v<R> && is_range_v<range_value_t<R>>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
        const char* dlm = "";
        for (const auto& x : r) os << std::exchange(dlm, "\n") << x;
        return os;
      }
    } // namespace ranges_io

    inline namespace tuple_io {
      using ::iris::ranges_io::operator<<;
      // tuple-like operator<<
      namespace _tuple_print {
        template <class CharT, class Traits, class T, std::size_t... Indicies>
        auto& tuple_print(std::basic_ostream<CharT, Traits>& os,
                          const T& t,
                          std::index_sequence<Indicies...>) {
          const char* dlm = "";
          using swallow   = std::initializer_list<int>;
          (void)swallow{
            (void(os << std::exchange(dlm, " ") << get<Indicies>(t)), 0)...};
          return os;
        }
      } // namespace _tuple_print
      template <
        class CharT,
        class Traits,
        class T,
        enable_if_t<is_tuple_like_v<T> && !is_range_v<T>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const T& t) {
        return _tuple_print::tuple_print(os, t, std::make_index_sequence<std::tuple_size_v<T>>{});
      }
    } // namespace tuple_io

    inline namespace pipe {
      template <class T, class CharT, class Traits>
      void operator|(const T& t, std::basic_ostream<CharT, Traits>& os) {
        os << t << std::endl;
      }
    } // namespace pipe
  }   // namespace io
} // namespace iris
