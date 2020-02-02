#pragma once
#include <iterator>
#include <iris/iterator.hpp>
#include <iris/type_traits/type_operation.hpp>

namespace iris {

  template <typename I, typename = void>
  struct iterator_traits {
    static_assert([]() { return false; }(), "candidate template ignored");
  };

// the number behind indicates where the macro is used
#define IRIS_DEFINE_ITERATOR_TRAITS_TYPE_ALIASES_1234                         \
private:                                                                      \
  using iterator_type = I;                                                    \
                                                                              \
public:                                                                       \
  using difference_type = detected_t<iterator::class_difference_t, I>;        \
  using pointer         = detected_t<concepts::member_selection_t, I const&>; \
  using reference       = detected_t<concepts::indirection_t, I const&>;      \
  using value_type      = detected_t<iterator::class_value_t, I>;             \
  static pointer to_address(iterator_type const& iter) noexcept {             \
    return iter.operator->();                                                 \
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
            enable_if_t<std::is_assignable_v<                                  \
              detected_t<concepts::indirection_t, iterator_type&>,             \
              X const&>> = nullptr>                                            \
  static void assign(iterator_type const& iter, X const& x) {                  \
    *iter = x;                                                                 \
  }                                                                            \
  template <                                                                   \
    typename X,                                                                \
    enable_if_t<std::conjunction_v<                                            \
      std::negation<std::is_reference<X>>,                                     \
      std::is_assignable<detected_t<concepts::indirection_t, iterator_type&>,  \
                         X const&>>> = nullptr>                                \
  static void assign(iterator_type const& iter, X&& x) {                       \
    *iter = std::move(x);                                                      \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_EQUAL_TO_ETC_2345                        \
  static bool equal_to(iterator_type const& lhs, iterator_type const& rhs) { \
    return lhs == rhs;                                                       \
  }                                                                          \
  static bool not_equal_to(iterator_type const& lhs,                         \
                           iterator_type const& rhs) {                       \
    return !iterator_traits::equal_to(lhs, rhs);                             \
  }
#define IRIS_DEFINE_ITERATOR_TRAITS_RETREAT_PREV_345                          \
  static iterator_type& retreat(iterator_type& iter, difference_type n = 1) { \
    return iterator_traits::advance(iter, -n);                                \
  }                                                                           \
  static auto prev(iterator_type const& iter, difference_type n = 1) {        \
    return iterator_traits::next(iter, -n);                                   \
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
                           is_input_iterator<I>,
                           std::negation<is_forward_iterator<I>>>>> {
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
  struct iterator_traits<I,
                         std::enable_if_t<std::conjunction_v<
                           is_forward_iterator<I>,
                           std::negation<is_bidirectional_iterator<I>>>>> {
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
  struct iterator_traits<I,
                         std::enable_if_t<std::conjunction_v<
                           is_bidirectional_iterator<I>,
                           std::negation<is_random_access_iterator<I>>>>> {
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
  struct iterator_traits<I, std::enable_if_t<is_random_access_iterator_v<I>>> {
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
