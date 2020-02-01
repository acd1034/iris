#pragma once
#include <iris/concepts/archetypal_alias.hpp>
#include <iris/concepts/def_define_concept.hpp>
#include <iris/concepts/special_detected_t.hpp>
#include <iris/type_traits/common_reference.hpp>

namespace iris {
  // https://en.cppreference.com/w/cpp/concepts
  namespace concepts {
    template <typename T, typename U>
    using std_swap_t =
      decltype(std::swap(std::declval<T>(), std::declval<U>()));
    template <typename T, typename U>
    using adl_swap_t = decltype(swap(std::declval<T>(), std::declval<U>()));
  } // namespace concepts

  // relationships
  IRIS_DEFINE_BNARY_CONCEPT(
    is_same_as, T, U,
    std::is_same<T, U>,
    std::is_same<U, T>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_derived_from, T, U,
    std::is_base_of<U, T>,
    std::is_convertible<std::remove_cv_t<T>*, std::remove_cv_t<U>*>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_common_reference_with, T, U,
    is_same_as<concepts::detected_common_reference_t<T, U>, concepts::detected_common_reference_t<U, T>>,
    std::is_convertible<T, concepts::detected_common_reference_t<T, U>>,
    std::is_convertible<U, concepts::detected_common_reference_t<T, U>>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_common_with, T, U,
    is_same_as<concepts::detected_common_type_t<T, U>, concepts::detected_common_type_t<U, T>>,
    std::is_convertible<T, concepts::detected_common_type_t<T, U>>,
    std::is_convertible<U, concepts::detected_common_type_t<T, U>>,
    is_common_reference_with<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>,
    is_common_reference_with<
      std::add_lvalue_reference_t<concepts::detected_common_type_t<T, U>>,
      concepts::detected_common_reference_t<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>>)
  // types
  IRIS_DEFINE_UNARY_CONCEPT(
    is_signed_integral, T,
    std::is_integral<T>,
    std::is_signed<T>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_unsigned_integral, T,
    std::is_integral<T>,
    std::negation<std::is_signed<T>>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_boolean, T,
    std::is_convertible<T, bool>,
    is_detected_convertible<bool, concepts::logical_not_t, T>,
    is_detected<concepts::logical_and_t, std::remove_reference_t<T> const&, bool>,
    is_detected<concepts::logical_and_t, bool, std::remove_reference_t<T> const&>,
    is_detected<concepts::logical_and_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected<concepts::logical_or_t, std::remove_reference_t<T> const&, bool>,
    is_detected<concepts::logical_or_t, bool, std::remove_reference_t<T> const&>,
    is_detected<concepts::logical_or_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected_convertible<bool, concepts::equal_to_t, std::remove_reference_t<T> const&, bool>,
    is_detected_convertible<bool, concepts::equal_to_t, bool, std::remove_reference_t<T> const&>,
    is_detected_convertible<bool, concepts::equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected_convertible<bool, concepts::not_equal_to_t, std::remove_reference_t<T> const&, bool>,
    is_detected_convertible<bool, concepts::not_equal_to_t, bool, std::remove_reference_t<T> const&>,
    is_detected_convertible<bool, concepts::not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>)
  // destruct, construct, assign and swap
  IRIS_DEFINE_UNARY_CONCEPT(
    is_destructible, T,
    std::is_nothrow_destructible<T>)
  IRIS_DEFINE_VARIA_CONCEPT(
    is_constructible_from, T, Args,
    is_destructible<T>,
    std::is_constructible<T, Args...>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_default_constructible, T,
    std::is_nothrow_destructible<T>,
    std::is_default_constructible<T>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_move_constructible, T,
    std::is_move_constructible<T>,
    std::is_convertible<T, T>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_copy_constructible, T,
    is_move_constructible<T>,
    is_constructible_from<T, T&>,
    std::is_convertible<T&, T>,
    is_constructible_from<T, T const&>,
    std::is_convertible<T const&, T>,
    is_constructible_from<T, T const>,
    std::is_convertible<T const, T>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_assignable_from, T, U,
    std::is_lvalue_reference<T>,
    is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_exact<T, concepts::assign_t, T, U>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_swappable, T,
    std::disjunction<is_detected<concepts::std_swap_t, T&, T&>,
                     is_detected<concepts::adl_swap_t, T&, T&>>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_swappable_with, T, U,
    is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_swappable<T>,
    is_swappable<U>,
    std::disjunction<is_detected<concepts::std_swap_t, T&, U&>,
                     is_detected<concepts::adl_swap_t, T&, U&>>,
    std::disjunction<is_detected<concepts::std_swap_t, U&, T&>,
                     is_detected<concepts::adl_swap_t, U&, T&>>)
  // compare
  IRIS_DEFINE_BNARY_CONCEPT(
    is_weakly_equality_comparable_with, T, U,
    is_detected_satisfy<is_boolean, concepts::equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_satisfy<is_boolean, concepts::equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_satisfy<is_boolean, concepts::not_equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_equality_comparable, T,
    is_weakly_equality_comparable_with<T, T>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_equality_comparable_with, T, U,
    is_equality_comparable<T>,
    is_equality_comparable<U>,
    is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_equality_comparable<concepts::detected_common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
    is_weakly_equality_comparable_with<T, U>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_totally_ordered, T,
    is_equality_comparable<T>,
    is_detected_satisfy<is_boolean, concepts::less_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::less_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>)
  IRIS_DEFINE_BNARY_CONCEPT(
    is_totally_ordered_with, T, U,
    is_totally_ordered<T>,
    is_totally_ordered<U>,
    is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_totally_ordered<concepts::detected_common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
    is_equality_comparable_with<T, U>,
    is_detected_satisfy<is_boolean, concepts::less_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::less_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_satisfy<is_boolean, concepts::less_equal_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::less_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_equal_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
    is_detected_satisfy<is_boolean, concepts::greater_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>)
  // operation
  IRIS_DEFINE_UNARY_CONCEPT(
    is_movable, T,
    std::is_object<T>,
    is_move_constructible<T>,
    is_assignable_from<T&, T>,
    is_swappable<T>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_copyable, T,
    is_movable<T>,
    is_copy_constructible<T>,
    is_assignable_from<T&, T const&>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_semiregular, T,
    is_copyable<T>,
    is_default_constructible<T>)
  IRIS_DEFINE_UNARY_CONCEPT(
    is_regular, T,
    is_semiregular<T>,
    is_equality_comparable<T>)
  // invoke
  IRIS_DEFINE_VARIA_CONCEPT(
    is_predicate, F, Args,
    std::is_invocable<F, Args...>,
    is_boolean<std::invoke_result_t<F, Args...>>)
  // clang-format off
  template <typename R, typename T, typename U>
  using is_relation = std::conjunction<
    is_predicate<R, T, T>,
    is_predicate<R, U, U>,
    is_predicate<R, T, U>,
    is_predicate<R, U, T>>;
  template <typename R, typename T, typename U>
  inline constexpr bool is_relation_v = is_relation<R, T, U>::value;
  // clang-format on
} // namespace iris
