#pragma once
#include <functional> // std::invoke

#include <iris/common_reference.hpp>
#include <iris/preprocessor.hpp>

namespace iris {
  namespace concepts {
    // See https://en.cppreference.com/w/cpp/concepts
#define IRIS_DEFINE_UNARY_OPERATOR_TYPE(Name, Op)                              \
  template <typename T>                                                        \
  using Name = decltype(Op std::declval<T>());
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(prefix_increment_t, ++)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(prefix_decrement_t, --)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(unary_plus_t, +)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(negate_t, -)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(bit_not_t, ~)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(logical_not_t, !)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(address_of_t, &)
    IRIS_DEFINE_UNARY_OPERATOR_TYPE(indirection_t, *)
#undef IRIS_DEFINE_UNARY_OPERATOR_TYPE

#define IRIS_DEFINE_BNARY_OPERATOR_TYPE(Name, Op)                              \
  template <typename T, typename U>                                            \
  using Name = decltype(std::declval<T>() Op std::declval<U>());
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(equal_to_t, ==)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(not_equal_to_t, !=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(less_t, <)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(less_equal_t, <=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(greater_t, >)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(greater_equal_t, >=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(plus_t, +)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(minus_t, -)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(multiplies_t, *)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(divides_t, /)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(modulus_t, %)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_and_t, &)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_or_t, |)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_xor_t, ^)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_left_shift_t, <<)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_right_shift_t, >>)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(logical_and_t, &&)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(logical_or_t, ||)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(assign_t, =)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(plus_assign_t, +=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(minus_assign_t, -=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(multiplies_assign_t, *=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(divides_assign_t, /=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(modulus_assign_t, %=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_and_assign_t, &=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_or_assign_t, |=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_xor_assign_t, ^=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_left_shift_assign_t, <<=)
    IRIS_DEFINE_BNARY_OPERATOR_TYPE(bit_right_shift_assign_t, >>=)
#undef IRIS_DEFINE_BNARY_OPERATOR_TYPE

    template <typename T>
    using member_selection_t = decltype(std::declval<T>().operator->());
    template <typename T>
    using postfix_increment_t = decltype(std::declval<T>()++);
    template <typename T>
    using postfix_decrement_t = decltype(std::declval<T>()--);
    template <typename T, typename U>
    using array_subscript_t = decltype(std::declval<T>()[std::declval<U>()]);
    template <typename T, typename... Args>
    using function_call_t =
      decltype(std::declval<T>()(std::declval<Args>()...));
    template <typename T, typename U>
    using comma_t = decltype(std::declval<T>(), std::declval<U>());
    template <typename T, typename U>
    using static_cast_t = decltype(static_cast<U>(std::declval<T>()));

    template <typename T, typename U>
    using common_type_t = detected_t<std::common_type_t, T, U>;
    template <typename T, typename U>
    using common_reference_t = detected_t<::iris::common_reference_t, T, U>;
    template <typename T, typename U>
    using std_swap_t =
      decltype(std::swap(std::declval<T>(), std::declval<U>()));
    template <typename T, typename U>
    using adl_swap_t = decltype(swap(std::declval<T>(), std::declval<U>()));
  } // namespace concepts

#define IRIS_DEFINE_UNARY_CONCEPT(Name, Type, ...)                             \
  template <typename Type>                                                     \
  using Name = std::conjunction<__VA_ARGS__>;                                  \
  template <typename Type>                                                     \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type>::value;
#define IRIS_DEFINE_BNARY_CONCEPT(Name, Type1, Type2, ...)                     \
  template <typename Type1, typename Type2>                                    \
  using Name = std::conjunction<__VA_ARGS__>;                                  \
  template <typename Type1, typename Type2>                                    \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2>::value;
#define IRIS_DEFINE_VARIA_CONCEPT(Name, Type1, Type2, ...)                     \
  template <typename Type1, typename... Type2>                                 \
  using Name = std::conjunction<__VA_ARGS__>;                                  \
  template <typename Type1, typename... Type2>                                 \
  inline constexpr bool IRIS_CONCAT(Name, _v) = Name<Type1, Type2...>::value;
  // clang-format off
  // relationships
  IRIS_DEFINE_BNARY_CONCEPT(is_same_as, T, U,
                            std::is_same<T, U>,
                            std::is_same<U, T>)
  IRIS_DEFINE_BNARY_CONCEPT(is_convertible_to, T, U,
                            std::is_convertible<T, U>// ,
                            /* requires(T (&fn)()) { static_cast<U>(fn()); } */)
  IRIS_DEFINE_BNARY_CONCEPT(is_derived_from, T, U,
                            std::is_base_of<U, T>,
                            is_convertible_to<std::remove_cv_t<T>*, std::remove_cv_t<U>*>)
  IRIS_DEFINE_BNARY_CONCEPT(is_common_reference_with, T, U,
                            is_same_as<concepts::common_reference_t<T, U>, concepts::common_reference_t<U, T>>,
                            is_convertible_to<T, concepts::common_reference_t<T, U>>,
                            is_convertible_to<U, concepts::common_reference_t<T, U>>)
  IRIS_DEFINE_BNARY_CONCEPT(is_common_with, T, U,
                            is_same_as<concepts::common_type_t<T, U>, concepts::common_type_t<U, T>>,
                            is_convertible_to<T, concepts::common_type_t<T, U>>,
                            is_convertible_to<U, concepts::common_type_t<T, U>>,
                            is_common_reference_with<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>,
                            is_common_reference_with<
                              std::add_lvalue_reference_t<concepts::common_type_t<T, U>>,
                              concepts::common_reference_t<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>>)
  // types
  IRIS_DEFINE_UNARY_CONCEPT(is_signed_integral, T,
                            std::is_integral<T>,
                            std::is_signed<T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_unsigned_integral, T,
                            std::is_integral<T>,
                            std::negation<std::is_signed<T>>)
  IRIS_DEFINE_UNARY_CONCEPT(is_boolean, T,
                            is_convertible_to<T, bool>,
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
  IRIS_DEFINE_UNARY_CONCEPT(is_destructible, T,
                            std::is_nothrow_destructible<T>)
  IRIS_DEFINE_VARIA_CONCEPT(is_constructible_from, T, Args,
                            is_destructible<T>,
                            std::is_constructible<T, Args...>)
  IRIS_DEFINE_UNARY_CONCEPT(is_default_constructible, T,
                            std::is_nothrow_destructible<T>,
                            std::is_default_constructible<T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_move_constructible, T,
                            std::is_move_constructible<T>,
                            is_convertible_to<T, T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_copy_constructible, T,
                            is_move_constructible<T>,
                            is_constructible_from<T, T&>,
                            is_convertible_to<T&, T>,
                            is_constructible_from<T, T const&>,
                            is_convertible_to<T const&, T>,
                            is_constructible_from<T, T const>,
                            is_convertible_to<T const, T>)
  IRIS_DEFINE_BNARY_CONCEPT(is_assignable_from, T, U,
                            std::is_lvalue_reference<T>,
                            is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_detected_exact<T, concepts::assign_t, T, U>)
  IRIS_DEFINE_UNARY_CONCEPT(is_swappable, T,
                            std::disjunction<is_detected<concepts::std_swap_t, T&, T&>,
                                             is_detected<concepts::adl_swap_t, T&, T&>>)
  IRIS_DEFINE_BNARY_CONCEPT(is_swappable_with, T, U,
                            is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_swappable<T>,
                            is_swappable<U>,
                            std::disjunction<is_detected<concepts::std_swap_t, T&, U&>,
                                             is_detected<concepts::adl_swap_t, T&, U&>>,
                            std::disjunction<is_detected<concepts::std_swap_t, U&, T&>,
                                             is_detected<concepts::adl_swap_t, U&, T&>>)
  // compare
  IRIS_DEFINE_BNARY_CONCEPT(is_weakly_comparable_with, T, U,
                            is_detected_satisfy<is_boolean, concepts::equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_detected_satisfy<is_boolean, concepts::equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                            is_detected_satisfy<is_boolean, concepts::not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_detected_satisfy<is_boolean, concepts::not_equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_equality_comparable, T,
                            is_weakly_comparable_with<T, T>)
  IRIS_DEFINE_BNARY_CONCEPT(is_equality_comparable_with, T, U,
                            is_equality_comparable<T>,
                            is_equality_comparable<U>,
                            is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_equality_comparable<concepts::common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
                            is_weakly_comparable_with<T, U>)
  IRIS_DEFINE_UNARY_CONCEPT(is_totally_ordered, T,
                            is_equality_comparable<T>,
                            is_detected_satisfy<is_boolean, concepts::less_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                            is_detected_satisfy<is_boolean, concepts::less_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                            is_detected_satisfy<is_boolean, concepts::greater_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                            is_detected_satisfy<is_boolean, concepts::greater_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>)
  IRIS_DEFINE_BNARY_CONCEPT(is_totally_ordered_with, T, U,
                            is_totally_ordered<T>,
                            is_totally_ordered<U>,
                            is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                            is_totally_ordered<concepts::common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
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
  IRIS_DEFINE_UNARY_CONCEPT(is_movable, T,
                            std::is_object<T>,
                            is_move_constructible<T>,
                            is_assignable_from<T&, T>,
                            is_swappable<T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_copyable, T,
                            is_movable<T>,
                            is_copy_constructible<T>,
                            is_assignable_from<T&, T const&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_semiregular, T,
                            is_copyable<T>,
                            is_default_constructible<T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_regular, T,
                            is_semiregular<T>,
                            is_equality_comparable<T>)
  // invoke
  IRIS_DEFINE_VARIA_CONCEPT(is_predicate, F, Args,
                            std::is_invocable<F, Args...>,
                            is_boolean<std::invoke_result_t<F, Args...>>)
  template <typename R, typename T, typename U>
  using is_relation = std::conjunction<is_predicate<R, T, T>,
                                       is_predicate<R, U, U>,
                                       is_predicate<R, T, U>,
                                       is_predicate<R, U, T>>;
  template <typename R, typename T, typename U>
  inline constexpr bool is_relation_v = is_relation<R, T, U>::value;
  // clang-format on
#undef IRIS_DEFINE_UNARY_CONCEPT
#undef IRIS_DEFINE_BNARY_CONCEPT
#undef IRIS_DEFINE_VARIA_CONCEPT

} // namespace iris
