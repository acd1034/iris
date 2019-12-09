#pragma once
#include <iris/preprocessor.hpp>
#include <iris/type_traits.hpp>

namespace iris {
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
  using element_selection_t = decltype(std::declval<T>().operator->());
  template <typename T>
  using suffix_increment_t = decltype(std::declval<T>()++);
  template <typename T>
  using suffix_decrement_t = decltype(std::declval<T>()--);
  template <typename T, typename U>
  using array_subscript_t = decltype(std::declval<T>()[std::declval<U>()]);
  template <typename T, typename... Args>
  using function_call_t = decltype(std::declval<T>()(std::declval<Args>()...));
  template <typename T, typename U>
  using comma_t = decltype(std::declval<T>(), std::declval<U>());

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
  // clang-format off
IRIS_DEFINE_BNARY_CONCEPT(is_derived_from, T, U,
                          std::is_base_of<U, T>,
                          std::is_convertible<std::remove_cv_t<T>*, std::remove_cv_t<U>*>)
// IRIS_DEFINE_BNARY_CONCEPT(is_common_reference_with, T, U,
//                           std::is_same<std::common_reference_t<T, U>, std::common_reference_t<U, T>>,
//                           std::is_convertible<T, std::common_reference_t<T, U>>,
//                           std::is_convertible<U, std::common_reference_t<T, U>>)
IRIS_DEFINE_BNARY_CONCEPT(is_common_with, T, U,
                          std::is_same<std::common_type_t<T, U>, std::common_type_t<U, T>>,
                          std::is_convertible<T, std::common_type_t<T, U>>,
                          std::is_convertible<U, std::common_type_t<T, U>>/*,
                          is_common_reference_with<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>,
                          is_common_reference_with<std::add_lvalue_reference_t<std::common_type_t<T, U>, std::common_reference_t<std::add_lvalue_reference_t<T const>, std::add_lvalue_reference_t<U const>>>*/)
IRIS_DEFINE_UNARY_CONCEPT(is_boolean, T,
                          std::is_convertible<T, bool>,
                          is_detected_convertible<bool, logical_not_t, T>,
                          is_detected<logical_and_t, std::remove_reference_t<T> const&, bool>,
                          is_detected<logical_and_t, bool, std::remove_reference_t<T> const&>,
                          is_detected<logical_and_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected<logical_or_t, std::remove_reference_t<T> const&, bool>,
                          is_detected<logical_or_t, bool, std::remove_reference_t<T> const&>,
                          is_detected<logical_or_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected_convertible<bool, equal_to_t, std::remove_reference_t<T> const&, bool>,
                          is_detected_convertible<bool, equal_to_t, bool, std::remove_reference_t<T> const&>,
                          is_detected_convertible<bool, equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected_convertible<bool, not_equal_to_t, std::remove_reference_t<T> const&, bool>,
                          is_detected_convertible<bool, not_equal_to_t, bool, std::remove_reference_t<T> const&>,
                          is_detected_convertible<bool, not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>)
IRIS_DEFINE_BNARY_CONCEPT(is_weakly_comparable_with, T, U,
                          is_detected_satisfy<is_boolean, equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          is_detected_satisfy<is_boolean, equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, not_equal_to_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          is_detected_satisfy<is_boolean, not_equal_to_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>)
IRIS_DEFINE_UNARY_CONCEPT(is_equality_comparable, T,
                          is_weakly_comparable_with<T, T>)
IRIS_DEFINE_BNARY_CONCEPT(is_equality_comparable_with, T, U,
                          is_equality_comparable<T>,
                          is_equality_comparable<U>,
                          // is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          // is_equality_comparable<std::common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
                          is_weakly_comparable_with<T, U>)
IRIS_DEFINE_UNARY_CONCEPT(is_totally_ordered, T,
                          is_equality_comparable<T>,
                          is_detected_satisfy<is_boolean, less_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, less_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, greater_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, greater_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<T> const&>)
IRIS_DEFINE_BNARY_CONCEPT(is_totally_ordered_with, T, U,
                          is_totally_ordered<T>,
                          is_totally_ordered<U>,
                          // is_common_reference_with<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          // is_totally_ordered<std::common_reference_t<std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>>,
                          is_equality_comparable_with<T, U>,
                          is_detected_satisfy<is_boolean, less_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, less_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          is_detected_satisfy<is_boolean, less_equal_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, less_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          is_detected_satisfy<is_boolean, greater_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, greater_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>,
                          is_detected_satisfy<is_boolean, greater_equal_t, std::remove_reference_t<U> const&, std::remove_reference_t<T> const&>,
                          is_detected_satisfy<is_boolean, greater_equal_t, std::remove_reference_t<T> const&, std::remove_reference_t<U> const&>)
IRIS_DEFINE_UNARY_CONCEPT(is_movable, T,
                          std::is_assignable<T&, T>,
                          std::is_move_constructible<T>,
                          std::is_object<T>,
                          std::is_swappable<T>)
IRIS_DEFINE_UNARY_CONCEPT(is_copyable, T,
                          is_movable<T>,
                          std::is_assignable<T&, T const&>,
                          std::is_copy_constructible<T>)
IRIS_DEFINE_UNARY_CONCEPT(is_semiregular, T,
                          is_copyable<T>,
                          std::is_default_constructible<T>)
IRIS_DEFINE_UNARY_CONCEPT(is_regular, T,
                          is_semiregular<T>,
                          is_equality_comparable<T>)
// clang-format on
#undef IRIS_DEFINE_UNARY_CONCEPT
#undef IRIS_DEFINE_BNARY_CONCEPT

} // namespace iris
