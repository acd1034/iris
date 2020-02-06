#pragma once
#include <iris/type_traits/common_reference.hpp>
#include <iris/type_traits/is_detected.hpp>

namespace iris {
  namespace concepts {
    // only used in detected_prefix_increment, detected_postfix_increment
    template <typename T>
    using class_type_t = typename T::type;

    // ISO C++17 does not allow incrementing expression of type bool [-Wincrement-bool]
    template <typename T, typename = void>
    struct detected_prefix_increment {};
    template <typename T>
    struct detected_prefix_increment<T, std::void_t<decltype(++std::declval<T>())>> {
      using type = decltype(++std::declval<T>());
    };
    template <>
    struct detected_prefix_increment<bool, void> {};
    template <typename T>
    using detected_prefix_increment_t = detected_t<concepts::class_type_t, detected_prefix_increment<T>>;

    template <typename T, typename = void>
    struct detected_postfix_increment {};
    template <typename T>
    struct detected_postfix_increment<T, std::void_t<decltype(++std::declval<T>())>> {
      using type = decltype(std::declval<T>()++);
    };
    template <>
    struct detected_postfix_increment<bool, void> {};
    template <typename T>
    using detected_postfix_increment_t = detected_t<concepts::class_type_t, detected_postfix_increment<T>>;

    template <typename T, typename U>
    using detected_common_type_t = detected_t<std::common_type_t, T, U>;
    template <typename T, typename U>
    using detected_common_reference_t = detected_t<common_reference_t, T, U>;
  } // namespace concepts
} // namespace iris
