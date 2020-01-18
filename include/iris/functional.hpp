#pragma once
namespace iris {
  struct identity {
    template <class T>
    constexpr T&& operator()(T&& t) const noexcept(
      noexcept(std::forward<T>(t))) {
      return std::forward<T>(t);
    }
  };
} // namespace iris
