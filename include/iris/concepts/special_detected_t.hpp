#pragma once
#include <iris/concepts/archetypal_alias2.hpp>
#include <iris/type_traits/is_detected.hpp>

namespace iris {
  namespace concepts {
    template <typename T, typename U>
    using detected_common_type_t = detected_t<std::common_type_t, T, U>;
    template <typename T, typename U>
    using detected_common_reference_t = detected_t<common_reference_t, T, U>;

    template <class T, class = void>
    struct detected_prefix_increment {};
    template <class T>
    struct detected_prefix_increment<T, std::void_t<decltype(++std::declval<T>())>> {
      using type = decltype(++std::declval<T>());
    };
    template <>
    struct detected_prefix_increment<bool, void> {};
    template <class T>
    using detected_prefix_increment_t = detected_t<concepts::class_type_t, detected_prefix_increment<T>>;

    template <class T, class = void>
    struct detected_postfix_increment {};
    template <class T>
    struct detected_postfix_increment<T, std::void_t<decltype(++std::declval<T>())>> {
      using type = decltype(std::declval<T>()++);
    };
    template <>
    struct detected_postfix_increment<bool, void> {};
    template <class T>
    using detected_postfix_increment_t = detected_t<concepts::class_type_t, detected_postfix_increment<T>>;
  } // namespace concepts
} // namespace iris
