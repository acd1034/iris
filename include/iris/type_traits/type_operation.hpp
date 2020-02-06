#pragma once
#include <type_traits>

namespace iris {
  // https://en.cppreference.com/w/cpp/types/type_identity
  template <typename T>
  struct type_identity {
    using type = T;
  };
  template <typename T>
  using type_identity_t = typename type_identity<T>::type;

  template <typename T>
  struct remove_cvref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
  };

  template <typename T>
  using remove_cvref_t = typename remove_cvref<T>::type;

  template <bool B, typename T = std::nullptr_t>
  using enable_if_t = typename std::enable_if<B, T>::type;
} // namespace iris
