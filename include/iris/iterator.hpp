#pragma once
#include <iris/concepts.hpp>

namespace iris {
  // https://en.cppreference.com/w/cpp/iterator
  namespace iterator {
    template <typename I>
    using class_value_t = typename I::value_type;
    template <typename I>
    using class_difference_t = typename I::difference_type;
  } // namespace iterator
  template <typename I>
  using iter_value_t = std::remove_cv_t<detected_t<iterator::class_value_t, I>>;
  // alias templateは特殊化できない
  // template <typename T>
  // using iter_value_t<T*> = std::remove_cv_t<T>;
  // template <typename T, std::size_t N>
  // using iter_value_t<T(&)[N]> = std::remove_cv_t<T>;
  template <typename I>
  using iter_reference_t = detected_t<concepts::indirection_t, I const&>;
  // 要検討
  // template <typename I>
  // using iter_rvalue_reference_t = decltype(ranges::iter_move(std::declval<I&>()));
  // template <typename I>
  // using iter_difference_t = detected_t<iterator::class_difference_t, I>;

  // clang-format off
  IRIS_DEFINE_UNARY_CONCEPT(is_iterator, I,
                            // 標準はdefault_constructibleを課す(何故?)
                            is_copyable<I>,
                            // *i
                            is_detected_dissatisfy<std::is_void, concepts::indirection_t, I&>,
                            // ++i, i++
                            is_detected_exact<I&, concepts::detected_prefix_increment_t, I&>,
                            is_detected<concepts::detected_postfix_increment_t, I&>)
  IRIS_DEFINE_BNARY_CONCEPT(is_sentinel_for, S, I,
                            is_iterator<I>,
                            // ==, !=
                            is_weakly_equality_comparable_with<S, I>)
  IRIS_DEFINE_UNARY_CONCEPT(is_input_iterator, I,
                            is_iterator<I>,
                            // i.operator->(). 標準はどこにも課さない
                            // is_detected_dissatisfy<std::is_void, concepts::member_selection_t, I&>,
                            is_detected_satisfy<is_signed_integral, iterator::class_difference_t, I>,
                            is_detected_dissatisfy<std::is_void, iterator::class_value_t, I>,
                            is_common_reference_with<detected_t<concepts::indirection_t, I&>&&, detected_t<iterator::class_value_t, I>&>)
  IRIS_DEFINE_BNARY_CONCEPT(is_output_iterator, I, T,
                            is_iterator<I>,
                            // *i = t, *i++ = t. is_assignable_fromは満たさない
                            is_detected_exact<detected_t<concepts::indirection_t, I&>, concepts::assign_t, detected_t<concepts::indirection_t, I&>, T const&>,
                            is_detected_exact<detected_t<concepts::indirection_t, detected_t<concepts::detected_postfix_increment_t, I&>>,
                                              concepts::assign_t,
                                              detected_t<concepts::indirection_t, detected_t<concepts::detected_postfix_increment_t, I&>>,
                                              T const&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_forward_iterator, I,
                            is_input_iterator<I>,
                            // i++
                            is_detected_exact<I, concepts::detected_postfix_increment_t, I&>,
                            // ==, !=
                            is_equality_comparable<I>)
  IRIS_DEFINE_UNARY_CONCEPT(is_bidirectional_iterator, I,
                            is_forward_iterator<I>,
                            // --i
                            is_detected_exact<I&, concepts::prefix_decrement_t, I&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_random_access_iterator, I,
                            is_bidirectional_iterator<I>,
                            // <, <=, >, >
                            is_totally_ordered<I>,
                            // i += n, i + n, n + i
                            is_detected_exact<I&, concepts::plus_assign_t, I&, detected_t<iterator::class_difference_t, I> const>,
                            is_detected_exact<I, concepts::plus_t, I, detected_t<iterator::class_difference_t, I> const>,
                            is_detected_exact<I, concepts::plus_t, detected_t<iterator::class_difference_t, I> const, I>,
                            // i -= n, i - n
                            is_detected_exact<I&, concepts::minus_assign_t, I&, detected_t<iterator::class_difference_t, I> const>,
                            is_detected_exact<I, concepts::minus_t, I, detected_t<iterator::class_difference_t, I> const>,
                            // i - j
                            is_detected_exact<detected_t<iterator::class_difference_t, I>, concepts::minus_t, I, I>,
                            // i[n]
                            is_detected_exact<concepts::indirection_t<I const&>, concepts::array_subscript_t, I const&, detected_t<iterator::class_difference_t, I> const>)
  // clang-format on
} // namespace iris
