#pragma once
#include <iris/iterator.hpp>

namespace iris {
  // See https://en.cppreference.com/w/cpp/ranges
  namespace ranges {
    template <typename R>
    using std_begin_t = decltype(std::begin(std::declval<R>()));
    template <typename R>
    using std_end_t = decltype(std::end(std::declval<R>()));
    template <typename R>
    using adl_begin_t = decltype(begin(std::declval<R>()));
    template <typename R>
    using adl_end_t = decltype(end(std::declval<R>()));
  } // namespace ranges
  template <typename R>
  using iterator_t =
    detected_or_t<detected_t<ranges::std_begin_t, R&>, ranges::adl_begin_t, R&>;
  template <typename R>
  using sentinel_t =
    detected_or_t<detected_t<ranges::std_end_t, R&>, ranges::adl_end_t, R&>;
  template <typename R>
  using range_value_t = iter_value_t<iterator_t<R>>;
  template <typename R>
  using range_reference_t = iter_reference_t<iterator_t<R>>;
  // template <typename R>
  // using range_rvalue_reference_t = iter_rvalue_reference_t<iterator_t<R>>;
  // template <typename R>
  // using range_difference_t = iter_difference_t<iterator_t<R>>;

  // clang-format off
  IRIS_DEFINE_UNARY_CONCEPT(is_range, R,
                            std::disjunction<is_detected<ranges::std_begin_t, R&>,
                                             is_detected<ranges::adl_begin_t, R&>>,
                            std::disjunction<is_detected<ranges::std_end_t, R&>,
                                             is_detected<ranges::adl_end_t, R&>>)
  IRIS_DEFINE_UNARY_CONCEPT(is_iterator_range, R,
                            is_range<R>,
                            is_iterator<iterator_t<R>>)
  IRIS_DEFINE_UNARY_CONCEPT(is_input_range, R,
                            is_range<R>,
                            is_input_iterator<iterator_t<R>>)
  IRIS_DEFINE_BNARY_CONCEPT(is_output_range, R, T,
                            is_range<R>,
                            is_output_iterator<iterator_t<R>, T>)
  IRIS_DEFINE_UNARY_CONCEPT(is_forward_range, R,
                            is_range<R>,
                            is_forward_iterator<iterator_t<R>>)
  IRIS_DEFINE_UNARY_CONCEPT(is_bidirectional_range, R,
                            is_range<R>,
                            is_bidirectional_iterator<iterator_t<R>>)
  IRIS_DEFINE_UNARY_CONCEPT(is_random_access_range, R,
                            is_range<R>,
                            is_random_access_iterator<iterator_t<R>>)
  // clang-format on
}; // namespace iris
