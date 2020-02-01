#pragma once
#include <type_traits>

namespace iris {
  namespace concepts {
#define IRIS_DEFINE_UNARY_OPERATOR_TYPE(Name, Op) \
  template <typename T>                           \
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

#define IRIS_DEFINE_BNARY_OPERATOR_TYPE(Name, Op) \
  template <typename T, typename U>               \
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
  } // namespace concepts
} // namespace iris
