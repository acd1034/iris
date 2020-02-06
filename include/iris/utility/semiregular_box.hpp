#pragma once
// #include <iostream>
#include <optional>
#include <iris/concepts.hpp>
#include <iris/type_traits/type_operation.hpp>

// https://github.com/CaseyCarter/cmcstl2/blob/master/include/stl2/detail/semiregular_box.hpp
// https://en.cppreference.com/w/cpp/ranges/semiregular_wrapper
namespace iris {
  template <typename T,
            typename = std::enable_if_t<
              std::is_move_constructible_v<T> && std::is_copy_constructible_v<T>>>
  struct semiregular_box;

  namespace utility {
    template <typename>
    struct is_semiregular_box : std::false_type {};
    template <typename T>
    struct is_semiregular_box<semiregular_box<T>> : std::true_type {};
    template <typename T>
    inline constexpr bool is_semiregular_box_v = is_semiregular_box<T>::value;
  } // namespace utility

  template <typename T, typename>
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
    template <typename, typename>
    friend struct semiregular_box;
    template <typename U                                         = T,
              enable_if_t<std::is_default_constructible_v<U>> = nullptr>
    constexpr semiregular_box() noexcept(std::is_nothrow_constructible_v<T>)
      : Base{std::in_place} {
      // std::cout << "dconst" << std::endl;
    }
    template <typename U                                          = T,
              enable_if_t<!std::is_default_constructible_v<U>> = nullptr>
    constexpr semiregular_box() noexcept : Base{} {
      // std::cout << "ndconst" << std::endl;
    }

    semiregular_box(semiregular_box&&)      = default;
    semiregular_box(const semiregular_box&) = default;
    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box(semiregular_box<U>&& rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
      : Base{std::move(rhs).base()} {
      // std::cout << "mconst_from_box" << std::endl;
    }
    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box(const semiregular_box<U>& rhs) noexcept(
      std::is_nothrow_copy_constructible_v<T>)
      : Base{rhs.base()} {
      // std::cout << "cconst_from_box" << std::endl;
    }
    template <typename U,
              enable_if_t<
                std::is_convertible_v<U, T> && std::is_rvalue_reference_v<U&&>> = nullptr>
    constexpr explicit semiregular_box(U&& rhs) noexcept(
      std::is_nothrow_move_constructible_v<T>)
      : Base{std::in_place, std::move(rhs)} {
      // std::cout << "mconst_from_U" << std::endl;
    }
    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr explicit semiregular_box(const U& rhs) noexcept(
      std::is_nothrow_copy_constructible_v<T>)
      : Base{std::in_place, rhs} {
      // std::cout << "cconst_from_U" << std::endl;
    }

    template <typename... Args,
              enable_if_t<is_constructible_from_v<T, Args...>> = nullptr>
    constexpr semiregular_box(std::in_place_t, Args&&... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>)
      : Base{std::in_place, std::forward<Args>(args)...} {}
    template <typename U, typename... Args,
              enable_if_t<
                is_constructible_from_v<T, std::initializer_list<U>, Args...>> = nullptr>
    constexpr semiregular_box(
      std::in_place_t, std::initializer_list<U> l,
      Args&&... args) noexcept(std::
                                 is_nothrow_constructible_v<
                                   T, std::initializer_list<U>, Args...>)
      : Base{std::in_place, l, std::forward<Args>(args)...} {}

  private:
    template <typename U, enable_if_t<
                         utility::is_semiregular_box_v<remove_cvref_t<U>>> = nullptr>
    constexpr semiregular_box& assign_semiregular_box(U&& rhs) noexcept(
      (std::is_rvalue_reference_v<U&&> //
       && (std::is_nothrow_move_assignable_v<T> || std::is_nothrow_move_constructible_v<T>))
      || (std::is_lvalue_reference_v<U> //
          && (std::is_nothrow_copy_assignable_v<T> || std::is_nothrow_copy_constructible_v<T>))) {
      if constexpr ((std::is_rvalue_reference_v<U&&> && std::is_move_assignable_v<T>)
                    || (std::is_lvalue_reference_v<U&&> && std::is_copy_assignable_v<T>)) {
        // std::cout << "assign_from_box1" << std::endl;
        Base::operator=(std::forward<U>(rhs).base());
      } else {
        // std::cout << "assign_from_box2" << std::endl;
        if (rhs)
          Base::emplace(*std::forward<U>(rhs));
        else
          Base::reset();
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
    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(semiregular_box<U>&& rhs) noexcept(
      noexcept(assign_semiregular_box(std::move(rhs)))) {
      return assign_semiregular_box(std::move(rhs));
    }
    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(const semiregular_box<U>& rhs) noexcept(
      noexcept(assign_semiregular_box(rhs))) {
      return assign_semiregular_box(rhs);
    }

    template <typename U, enable_if_t<std::is_convertible_v<U, T>> = nullptr>
    constexpr semiregular_box& operator=(U&& rhs) noexcept(
      (std::is_rvalue_reference_v<U&&> && //
       (std::is_nothrow_move_assignable_v<T> || std::is_nothrow_move_constructible_v<T>))
      || (std::is_lvalue_reference_v<U&&> && //
          (std::is_nothrow_copy_assignable_v<T> || std::is_nothrow_copy_constructible_v<T>))) {
      if constexpr ((std::is_rvalue_reference_v<U&&> && std::is_move_assignable_v<T>)
                    || (std::is_lvalue_reference_v<U> && std::is_copy_assignable_v<T>)) {
        // std::cout << "assign_from_U1" << std::endl;
        Base::operator=(std::forward<U>(rhs));
      } else {
        // std::cout << "assign_from_U2" << std::endl;
        Base::emplace(std::forward<U>(rhs));
      }
      return *this;
    }
  };
  template <typename T>
  semiregular_box(T)->semiregular_box<T>;
} // namespace iris
