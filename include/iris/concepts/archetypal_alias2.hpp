#pragma once
// #include <type_traits>

namespace iris {
  namespace concepts {
    template <typename T>
    using class_type_t = typename T::type;
  } // namespace concepts
} // namespace iris
