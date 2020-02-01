#pragma once
#include <tuple>
#include <iris/type_traits.hpp>

namespace iris {
  namespace utility {
    namespace _get {
      template <std::size_t I, typename T, enable_if_t<std::is_lvalue_reference_v<T&>> = nullptr>
      constexpr auto get(T& t) -> decltype(t.template get<I>()) {
        return t.template get<I>();
      }
      template <std::size_t I, typename T, enable_if_t<std::is_lvalue_reference_v<T&>> = nullptr>
      constexpr auto get(const T& t) -> decltype(t.template get<I>()) {
        return t.template get<I>();
      }
      template <std::size_t I, typename T, enable_if_t<std::is_rvalue_reference_v<T&&>> = nullptr>
      constexpr auto get(T&& t) -> decltype(static_cast<T&&>(t).template get<I>()) {
        return static_cast<T&&>(t).template get<I>();
      }
      template <std::size_t I, typename T, enable_if_t<std::is_rvalue_reference_v<T&&>> = nullptr>
      constexpr auto get(const T&& t) -> decltype(static_cast<const T&&>(t).template get<I>()) {
        return static_cast<const T&&>(t).template get<I>();
      }
      template <std::size_t I, typename T, std::size_t N, enable_if_t<(I < N)> = nullptr>
      constexpr T& get(T (&arr)[N]) {
        return arr[I];
      }
      template <std::size_t I, typename T, std::size_t N, enable_if_t<(I < N)> = nullptr>
      constexpr const T& get(const T (&arr)[N]) {
        return arr[I];
      }
      template <std::size_t I, typename T, std::size_t N, enable_if_t<(I < N)> = nullptr>
      constexpr T&& get(T(&&arr)[N]) {
        return static_cast<T&&>(arr[I]);
      }
      template <std::size_t I, typename T, std::size_t N, enable_if_t<(I < N)> = nullptr>
      constexpr const T&& get(const T(&&arr)[N]) {
        return static_cast<const T&&>(arr[I]);
      }
    } // namespace _get
  }   // namespace utility
} // namespace iris
