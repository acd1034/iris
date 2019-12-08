#pragma once
#include <iterator>

#include <iris/concepts.hpp>

namespace iris {
  namespace iterator {
    template <typename I>
    using class_difference_type_t = typename I::difference_type;
    template <typename I>
    using class_value_type_t = typename I::value_type;
  } // namespace iterator

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
  IRIS_DEFINE_UNARY_CONCEPT(is_iterator_class, I,
                            is_copyable<I>,
                            // *i
                            is_detected_dissatisfy<std::is_void, indirection_t, I const&>,
                            // ++i
                            is_detected_exact<I&, prefix_increment_t, I&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_input_iterator_class, I,
                            is_iterator_class<I>,
                            // i++
                            is_detected<suffix_increment_t, I&>,
                            // i.operator->()
                            is_detected_dissatisfy<std::is_void, element_selection_t, I const&>,
                            is_detected_satisfy<std::is_signed, iterator::class_difference_type_t, I>,
                            is_detected_dissatisfy<std::is_void, iterator::class_value_type_t, I>/*,
                            // is_common_reference_with<indirection_t<T&>&&, iterator::class_value_type_t<T>&>*/)
  IRIS_DEFINE_BNARY_CONCEPT(is_output_iterator_class, I, T,
                            is_iterator_class<I>,
                            // *i = t, *i++ = t
                            std::is_assignable<detected_t<indirection_t, I&>, T const&>,
                            std::is_assignable<detected_t<indirection_t, detected_t<suffix_increment_t, I&>>, T const&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_forward_iterator_class, I,
                            is_input_iterator_class<I>,
                            // == , !=
                            is_equality_comparable<I>)
  IRIS_DEFINE_UNARY_CONCEPT(is_bidirectional_iterator_class, I,
                            is_forward_iterator_class<I>,
                            // --i
                            is_detected_exact<I&, prefix_decrement_t, I&>)
  IRIS_DEFINE_UNARY_CONCEPT(is_random_access_iterator_class, I,
                            is_bidirectional_iterator_class<I>,
                            // <, <=, >, >
                            is_totally_ordered<I>,
                            // i += n, i + n, n + i
                            is_detected_exact<I&, plus_assign_t, I&, detected_t<iterator::class_difference_type_t, I> const>,
                            is_detected_exact<I, plus_t, I, detected_t<iterator::class_difference_type_t, I> const>,
                            is_detected_exact<I, plus_t, detected_t<iterator::class_difference_type_t, I> const, I>,
                            // i -= n, i - n
                            is_detected_exact<I&, minus_assign_t, I&, detected_t<iterator::class_difference_type_t, I> const>,
                            is_detected_exact<I, minus_t, I, detected_t<iterator::class_difference_type_t, I> const>,
                            // i - j
                            is_detected_exact<detected_t<iterator::class_difference_type_t, I>, minus_t, I, I>,
                            // i[n]
                            is_detected_exact<indirection_t<I const&>, array_subscripting_t, I const&, detected_t<iterator::class_difference_type_t, I> const>)
  // clang-format on
#undef IRIS_DEFINE_UNARY_CONCEPT
#undef IRIS_DEFINE_BNARY_CONCEPT

  template <typename I, typename = void>
  struct iterator_traits {
    static_assert(false_v<I>, "candidate template ignored");
  };

// the number behind indicates where the macro is used
#define IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234                          \
private:                                                                       \
  using iterator_type = I;                                                     \
                                                                               \
public:                                                                        \
  using difference_type = detected_t<iterator::class_difference_type_t, I>;    \
  using pointer         = detected_t<element_selection_t, I const&>;           \
  using reference       = detected_t<indirection_t, I const&>;                 \
  using value_type      = detected_t<iterator::class_value_type_t, I>;         \
  static pointer to_address(iterator_type const& iter) noexcept {              \
    return iter.operator->();                                                  \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345                               \
  static reference deref(iterator_type const& iter) noexcept { return *iter; } \
  static auto advance(iterator_type&& iter, difference_type n = 1) {           \
    iterator_traits::advance(iter, n);                                         \
    return std::move(iter);                                                    \
  }                                                                            \
  static auto next(iterator_type iter, difference_type n = 1) {                \
    iterator_traits::advance(iter, n);                                         \
    return std::move(iter);                                                    \
  }                                                                            \
  static reference at(iterator_type iter, difference_type n) {                 \
    return iterator_traits::deref(iterator_traits::advance(iter, n));          \
  }                                                                            \
  template <typename X,                                                        \
            enable_if_t<                                                       \
              std::is_assignable_v<detected_t<indirection_t, iterator_type&>,  \
                                   X const&>> = nullptr>                       \
  static void assign(iterator_type const& iter, X const& x) {                  \
    *iter = x;                                                                 \
  }                                                                            \
  template <typename X,                                                        \
            enable_if_t<std::conjunction_v<                                    \
              std::negation<std::is_reference<X>>,                             \
              std::is_assignable<detected_t<indirection_t, iterator_type&>,    \
                                 X const&>>> = nullptr>                        \
  static void assign(iterator_type const& iter, X&& x) {                       \
    *iter = std::move(x);                                                      \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345                          \
  static bool equal_to(iterator_type const& lhs, iterator_type const& rhs) {   \
    return lhs == rhs;                                                         \
  }                                                                            \
  static bool not_equal_to(iterator_type const& lhs,                           \
                           iterator_type const& rhs) {                         \
    return !iterator_traits::equal_to(lhs, rhs);                               \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345                           \
  static iterator_type& retreat(iterator_type& iter, difference_type n = 1) {  \
    return iterator_traits::advance(iter, -n);                                 \
  }                                                                            \
  static auto prev(iterator_type const& iter, difference_type n = 1) {         \
    return iterator_traits::next(iter, -n);                                    \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_LESS_ETC_45                                \
  static bool less(iterator_type const& lhs, iterator_type const& rhs) {       \
    return lhs < rhs;                                                          \
  }                                                                            \
  static bool less_equal(iterator_type const& lhs, iterator_type const& rhs) { \
    return !iterator_traits::less(rhs, lhs);                                   \
  }                                                                            \
  static bool greater(iterator_type const& lhs, iterator_type const& rhs) {    \
    return iterator_traits::less(rhs, lhs);                                    \
  }                                                                            \
  static bool greater_equal(iterator_type const& lhs,                          \
                            iterator_type const& rhs) {                        \
    return !iterator_traits::less(lhs, rhs);                                   \
  }

  // 1
  template <typename I>
  struct iterator_traits<I,
                         std::enable_if_t<std::conjunction_v<
                           is_input_iterator_class<I>,
                           std::negation<is_forward_iterator_class<I>>>>> {
    using iterator_category = std::input_iterator_tag;
    IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234
    IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
    static iterator_type& advance(iterator_type& iter, difference_type n = 1) {
      for (; n > 0; --n) ++iter;
      return iter;
    }
  };

  // 2
  template <typename I>
  struct iterator_traits<
    I,
    std::enable_if_t<
      std::conjunction_v<is_forward_iterator_class<I>,
                         std::negation<is_bidirectional_iterator_class<I>>>>> {
    using iterator_category = std::forward_iterator_tag;
    IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234
    IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
    IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345
    static iterator_type& advance(iterator_type& iter, difference_type n = 1) {
      for (; n > 0; --n) ++iter;
      return iter;
    }
    static difference_type distance(iterator_type lhs,
                                    iterator_type const& rhs) {
      difference_type result{0};
      for (; iterator_traits::not_equal_to(lhs, rhs);
           iterator_traits::advance(lhs))
        ++result;
      return result;
    }
  };

  // 3
  template <typename I>
  struct iterator_traits<
    I,
    std::enable_if_t<
      std::conjunction_v<is_bidirectional_iterator_class<I>,
                         std::negation<is_random_access_iterator_class<I>>>>> {
    using iterator_category = std::bidirectional_iterator_tag;
    IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234
    IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
    IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345
    IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345
    static iterator_type& advance(iterator_type& iter, difference_type n = 1) {
      if (n >= 0)
        for (; n > 0; --n) ++iter;
      else
        for (; n < 0; ++n) --iter;
      return iter;
    }
    static difference_type distance(iterator_type lhs,
                                    iterator_type const& rhs) {
      difference_type result{0};
      for (; iterator_traits::not_equal_to(lhs, rhs);
           iterator_traits::advance(lhs))
        ++result;
      return result;
    }
  };

  // 4
  template <typename I>
  struct iterator_traits<
    I,
    std::enable_if_t<is_random_access_iterator_class_v<I>>> {
    using iterator_category = std::random_access_iterator_tag;
    IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234
    IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
    IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345
    IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345
    IRIS_DEFINE_ITERATOR_TRAITS_LESS_ETC_45
    static iterator_type& advance(iterator_type& iter, difference_type n = 1) {
      return iter += n;
    }
    static difference_type distance(iterator_type const& lhs,
                                    iterator_type const& rhs) {
      return rhs - lhs;
    }
  };

  // 5
  template <typename T>
  struct iterator_traits<T*, std::enable_if_t<std::is_object_v<T>>> {
  private:
    using iterator_type = T*;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    using value_type        = std::remove_cv_t<T>;
    IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
    IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345
    IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345
    IRIS_DEFINE_ITERATOR_TRAITS_LESS_ETC_45
    static pointer to_address(iterator_type const& iter) noexcept {
      return iter;
    }
    static iterator_type& advance(iterator_type& iter, difference_type n = 1) {
      return iter += n;
    }
    static difference_type distance(iterator_type const& lhs,
                                    iterator_type const& rhs) {
      return rhs - lhs;
    }
  };

#undef IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234
#undef IRIS_DEFINE_ITERATOR_TRAITS_COMMON_12345
#undef IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345
#undef IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345
#undef IRIS_DEFINE_ITERATOR_TRAITS_LESS_ETC_45

} // namespace iris
