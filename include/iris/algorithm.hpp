#pragma once
#include <algorithm>
#include <iris/ranges.hpp>

namespace iris {
  // equal
  // TODO: conceptを用いた実装
  // clang-format off
  template <typename R1, typename R2>
  bool equal(R1 const& lhs, R2 const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(R const& lhs, std::initializer_list<T> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(std::initializer_list<T> const& lhs, R const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename T, typename U>
  bool equal(std::initializer_list<T> const& lhs, std::initializer_list<U> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }
  template <typename R, typename T>
  bool equal(R const& lhs, std::initializer_list<std::initializer_list<T>> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  template <typename R, typename T>
  bool equal(std::initializer_list<std::initializer_list<T>> const& lhs, R const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  template <typename T, typename U>
  bool equal(std::initializer_list<std::initializer_list<T>> const& lhs, std::initializer_list<std::initializer_list<U>> const& rhs) {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
        [](auto const& lhs, auto const& rhs){ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); });
  }
  // clang-format on
} // namespace iris
