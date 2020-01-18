#pragma once
#include <iostream>
#include <optional>
#include <iris/concepts.hpp>

// See:
// https://github.com/CaseyCarter/cmcstl2/blob/master/include/stl2/detail/semiregular_box.hpp
// https://en.cppreference.com/w/cpp/ranges/semiregular_wrapper
namespace iris {
  template <class T,
            class = std::enable_if_t<
              std::is_move_constructible_v<T> && std::is_copy_constructible_v<T>>>
  struct semiregular_box;

  namespace detail {
    template <class>
    struct is_semiregular_box : std::false_type {};
    template <class T>
    struct is_semiregular_box<semiregular_box<T>> : std::true_type {};
    template <class T>
    inline constexpr bool is_semiregular_box_v = is_semiregular_box<T>::value;
  } // namespace detail

  template <class T, class>
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
    constexpr semiregular_box(semiregular_box<U>&& rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
      : Base{std::move(rhs).base()} {
      std::cout << "mconst_from_box" << std::endl;
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box(const semiregular_box<U>& rhs) noexcept(
      std::is_nothrow_copy_constructible_v<T>)
      : Base{rhs.base()} {
      std::cout << "cconst_from_box" << std::endl;
    }
    template <class U,
              enable_if_t<
                std::is_convertible_v<U, T> && std::is_rvalue_reference_v<U&&>> = nullptr>
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
    template <class U, class... Args,
              enable_if_t<
                is_constructible_from_v<T, std::initializer_list<U>, Args...>> = nullptr>
    constexpr semiregular_box(
      std::in_place_t, std::initializer_list<U> l,
      Args&&... args) noexcept(std::
                                 is_nothrow_constructible_v<
                                   T, std::initializer_list<U>, Args...>)
      : Base{std::in_place, l, std::forward<Args>(args)...} {}

  private:
    template <class U, enable_if_t<
                         detail::is_semiregular_box_v<remove_cvref_t<U>>> = nullptr>
    constexpr semiregular_box& assign_semiregular_box(U&& rhs) noexcept(
      (std::is_rvalue_reference_v<U&&> //
       && (std::is_nothrow_move_assignable_v<T> || std::is_nothrow_move_constructible_v<T>))
      || (std::is_lvalue_reference_v<U> //
          && (std::is_nothrow_copy_assignable_v<T> || std::is_nothrow_copy_constructible_v<T>))) {
      if constexpr ((std::is_rvalue_reference_v<U&&> && std::is_move_assignable_v<T>)
                    || (std::is_lvalue_reference_v<U&&> && std::is_copy_assignable_v<T>)) {
        std::cout << "assign_from_box1" << std::endl;
        base() = std::forward<U>(rhs).base();
      } else {
        std::cout << "assign_from_box2" << std::endl;
        if (rhs)
          emplace(*std::forward<U>(rhs));
        else
          reset();
      }
      return *this;
    }

  public:
    constexpr semiregular_box& operator=(semiregular_box&& rhs) noexcept(
      noexcept(assign_semiregular_box(std::move(rhs)))) {
      return assign_semiregular_box(std::move(rhs));
    }
    constexpr semiregular_box& operator=(const semiregular_box& rhs) noexcept(
      noexcept(assign_semiregular_box(rhs))) {
      return assign_semiregular_box(rhs);
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(semiregular_box<U>&& rhs) noexcept(
      noexcept(assign_semiregular_box(std::move(rhs)))) {
      return assign_semiregular_box(std::move(rhs));
    }
    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(const semiregular_box<U>& rhs) noexcept(
      noexcept(assign_semiregular_box(rhs))) {
      return assign_semiregular_box(rhs);
    }

    template <class U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(U&& rhs) noexcept(
      (std::is_rvalue_reference_v<U&&> && //
       (std::is_nothrow_move_assignable_v<T> || std::is_nothrow_move_constructible_v<T>))
      || (std::is_lvalue_reference_v<U&&> && //
          (std::is_nothrow_copy_assignable_v<T> || std::is_nothrow_copy_constructible_v<T>))) {
      if constexpr ((std::is_rvalue_reference_v<U&&> && std::is_move_assignable_v<T>)
                    || (std::is_lvalue_reference_v<U> && std::is_copy_assignable_v<T>)) {
        std::cout << "assign_from_U1" << std::endl;
        base() = std::forward<U>(rhs);
      } else {
        std::cout << "assign_from_U2" << std::endl;
        emplace(std::forward<U>(rhs));
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
