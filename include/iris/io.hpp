#pragma once
#include <ostream>                        // std::basic_ostream, std::endl
#include <iris/ranges.hpp>                // is_range
#include <iris/utility/is_tuple_like.hpp> // is_tuple_like

namespace iris {
  namespace _io {
    template <typename T>
    struct is_std_basic_ostream : std::false_type {};
    template <typename CharT, typename Traits>
    struct is_std_basic_ostream<std::basic_ostream<CharT, Traits>> : std::true_type {};
    template <typename T>
    inline constexpr bool is_std_basic_ostream_v = is_std_basic_ostream<T>::value;

    template <typename CharT, typename Traits, typename T, std::size_t... Indicies>
    auto& tuple_io_impl(std::basic_ostream<CharT, Traits>& os, const T& t,
                        std::index_sequence<Indicies...>) {
      const char* dlm = "";
      using swallow   = std::initializer_list<int>;
      (void)swallow{
        (void(os << std::exchange(dlm, " ") << get<Indicies>(t)), 0)...};
      return os;
    }
  } // namespace _io
  template <typename Os, typename T>
  using is_stream_insertable = std::conjunction<
    _io::is_std_basic_ostream<std::remove_reference_t<Os>>,
    is_detected_exact<std::remove_reference_t<Os>&,
                      concepts::bit_left_shift_t,
                      std::remove_reference_t<Os>&,
                      const std::remove_reference_t<T>&>>;
  template <typename Os, typename T>
  inline constexpr bool is_stream_insertable_v = is_stream_insertable<Os, T>::value;

  inline namespace io {
    inline namespace ranges_io {
      template <typename CharT, typename Traits, typename R,
                enable_if_t<is_range_v<R> && !is_range_v<range_value_t<R>>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
        const char* dlm = "";
        for (const auto& x : r) os << std::exchange(dlm, " ") << x;
        return os;
      }
      template <typename CharT, typename Traits, typename R,
                enable_if_t<is_range_v<R> && is_range_v<range_value_t<R>>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const R& r) {
        const char* dlm = "";
        for (const auto& x : r) os << std::exchange(dlm, "\n") << x;
        return os;
      }
    } // namespace ranges_io

    inline namespace tuple_io {
      using ::iris::ranges_io::operator<<;
      template <typename CharT, typename Traits, typename T,
                enable_if_t<is_tuple_like_v<T> && !is_range_v<T>> = nullptr>
      auto& operator<<(std::basic_ostream<CharT, Traits>& os, const T& t) {
        return _io::tuple_io_impl(os, t, std::make_index_sequence<std::tuple_size_v<T>>{});
      }
    } // namespace tuple_io

    inline namespace pipe {
      template <typename T, typename CharT, typename Traits>
      void operator|(const T& t, std::basic_ostream<CharT, Traits>& os) {
        os << t << std::endl;
      }
    } // namespace pipe
  }   // namespace io
} // namespace iris
