#pragma once
#include <iostream>
#include <optional>
#include <iris/concepts.hpp>

// See:
// https://github.com/CaseyCarter/cmcstl2/blob/master/include/stl2/detail/semiregular_box.hpp
// https://en.cppreference.com/w/cpp/ranges/semiregular_wrapper
namespace iris {
  template <class T,
            class = std::enable_if_t<std::is_move_constructible_v<
                                       T> && std::is_copy_constructible_v<T>>>
  struct semiregular_box : std::optional<T> {
  private:
    using Base = std::optional<T>;
    constexpr Base& base() & { return *this; }
    constexpr const Base& base() const& { return *this; }
    constexpr Base&& base() && { return static_cast<Base&&>(*this); }
    constexpr const Base&& base() const&& {
      return static_cast<const Base&&>(*this);
    }

  public:
    template <class, class>
    friend struct semiregular_box;
    template <class U                                         = T,
              enable_if_t<std::is_default_constructible_v<U>> = nullptr>
    constexpr semiregular_box() noexcept(std::is_nothrow_constructible_v<T>)
      : Base{std::in_place} {
      std::cout << "dconst" << std::endl;
    }
    template <class U                                          = T,
              enable_if_t<!std::is_default_constructible_v<U>> = nullptr>
    constexpr semiregular_box() noexcept : Base{} {
      std::cout << "ndconst" << std::endl;
    }

    semiregular_box(semiregular_box&&)      = default;
    semiregular_box(const semiregular_box&) = default;
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    semiregular_box(semiregular_box<U>&& rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
      : Base{std::move(rhs).base()} {
      std::cout << "mconst_from_box<U>" << std::endl;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    semiregular_box(const semiregular_box<U>& rhs) noexcept(
      std::is_nothrow_copy_constructible_v<T>)
      : Base{rhs.base()} {
      std::cout << "cconst_from_box<U>" << std::endl;
    }
    template <
      class U,
      enable_if_t<
        std::is_convertible_v<U, T> && std::is_rvalue_reference_v<U&&>> =
        nullptr>
    constexpr explicit semiregular_box(U&& rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
      : Base{std::in_place, std::move(rhs)} {
      std::cout << "mconst_from_U" << std::endl;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr explicit semiregular_box(const U& rhs) noexcept(
      std::is_nothrow_copy_constructible_v<T>)
      : Base{std::in_place, rhs} {
      std::cout << "cconst_from_U" << std::endl;
    }

    template <class... Args,
              enable_if_t<is_constructible_from_v<T, Args...>> = nullptr>
    constexpr semiregular_box(std::in_place_t, Args&&... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>)
      : Base{std::in_place, std::forward<Args>(args)...} {}
    template <class U,
              class... Args,
              enable_if_t<
                is_constructible_from_v<T, std::initializer_list<U>, Args...>> =
                nullptr>
    constexpr semiregular_box(
      std::in_place_t,
      std::initializer_list<U> l,
      Args&&... args) noexcept(std::
                                 is_nothrow_constructible_v<
                                   T,
                                   std::initializer_list<U>,
                                   Args...>)
      : Base{std::in_place, l, std::forward<Args>(args)...} {}

    semiregular_box& operator=(semiregular_box&& rhs) noexcept(
      std::is_nothrow_move_assignable_v<
        T> || std::is_nothrow_move_constructible_v<T>) {
      if constexpr (std::is_move_assignable_v<T>) {
        std::cout << "massign_from_box1" << std::endl;
        base() = std::move(rhs).base();
      } else {
        std::cout << "massign_from_box2" << std::endl;
        if (rhs)
          emplace(*std::move(rhs));
        else
          reset();
      }
      return *this;
    }
    semiregular_box& operator=(const semiregular_box& rhs) noexcept(
      std::is_nothrow_copy_assignable_v<
        T> || std::is_nothrow_copy_constructible_v<T>) {
      if constexpr (std::is_copy_assignable_v<T>) {
        std::cout << "cassign_from_box1" << std::endl;
        base() = rhs.base();
      } else {
        std::cout << "cassign_from_box2" << std::endl;
        if (rhs)
          emplace(*rhs);
        else
          reset();
      }
      return *this;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(semiregular_box<U>&& rhs) noexcept(
      std::is_nothrow_move_assignable_v<
        T> || std::is_nothrow_move_constructible_v<T>) {
      if constexpr (std::is_move_assignable_v<T>) {
        std::cout << "massign_from_box<U>1" << std::endl;
        base() = std::move(rhs).base();
      } else {
        std::cout << "massign_from_box<U>2" << std::endl;
        if (rhs)
          emplace(std::move(*rhs));
        else
          reset();
      }
      return *this;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box&
    operator=(const semiregular_box<U>& rhs) noexcept(
      std::is_nothrow_copy_assignable_v<
        T> || std::is_nothrow_copy_constructible_v<T>) {
      if constexpr (std::is_copy_assignable_v<T>) {
        std::cout << "cassign_from_box<U>1" << std::endl;
        base() = rhs.base();
      } else {
        std::cout << "cassign_from_box<U>2" << std::endl;
        if (rhs)
          emplace(*rhs);
        else
          reset();
      }
      return *this;
    }
    template <
      class U,
      enable_if_t<
        std::is_convertible_v<U, T> && std::is_rvalue_reference_v<U&&>> =
        nullptr>
    constexpr semiregular_box& operator=(U&& rhs) noexcept(
      std::is_nothrow_move_assignable_v<
        T> || std::is_nothrow_move_constructible_v<T>) {
      if constexpr (std::is_move_assignable_v<T>) {
        std::cout << "massign_from_U1" << std::endl;
        base() = std::move(rhs);
      } else {
        std::cout << "massign_from_U2" << std::endl;
        emplace(std::move(rhs));
      }
      return *this;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(const U& rhs) noexcept(
      std::is_nothrow_copy_assignable_v<
        T> || std::is_nothrow_copy_constructible_v<T>) {
      if constexpr (std::is_copy_assignable_v<T>) {
        std::cout << "cassign_from_U1" << std::endl;
        base() = rhs;
      } else {
        std::cout << "cassign_from_U2" << std::endl;
        emplace(rhs);
      }
      return *this;
    }

    using Base::emplace, Base::swap, Base::reset, Base::operator*,
      Base::operator->, Base::operator bool, Base::has_value, Base::value,
      Base::value_or;
    using value_type = typename Base::value_type;
  };
  template <class T>
  semiregular_box(T)->semiregular_box<T>;
} // namespace iris
