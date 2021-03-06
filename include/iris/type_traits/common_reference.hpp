#pragma once
#include <iris/type_traits/is_detected.hpp> // is_detected_v
#include <type_traits>
#include <utility>

namespace iris {
  /// @cond
  namespace type_traits {
    namespace _common_reference {
      // https://ericniebler.github.io/std/wg21/D0022.html
      // clang-format off
    template <class T>
    using __t = typename T::type;

    template <class T>
    inline constexpr typename __t<T>::value_type __v = __t<T>::value;

    template <class T, class... Args>
    using __apply = typename T::template apply<Args...>;

    template <class T, class U>
    struct __compose {
      template <class V>
      using apply = __apply<T, __apply<U, V>>;
    };

    template <class T>
    struct __id {
      using type = T;
    };

    template <template <class...> class T, class... U>
    inline constexpr bool _Valid = is_detected_v<T, U...>;

    template <class U, template <class...> class T, class... V>
    inline constexpr bool _Is = _Valid<T, U, V...> && __v<T<U, V...>>;

    template <class U, class V>
    inline constexpr bool _ConvertibleTo = _Is<U, std::is_convertible, V>;

    template <class, template <class...> class T, class... U>
    struct __defer {};
    template <template <class...> class T, class... U>
    struct __defer<std::enable_if_t<_Valid<T, U...>>, T, U...> : __id<T<U...>> {};

    template <template <class...> class T>
    struct __q {
      template <class... U>
      using apply = __t<__defer<void, T, U...>>;
    };

    template <class T, class = void>
    struct __has_type : std::false_type {};
    template <class T>
    struct __has_type<T, std::enable_if_t<_Valid<__t, T>>> : std::true_type {};

    template <class T, class X = std::remove_reference_t<T>>
    using __cref = std::add_lvalue_reference_t<std::add_const_t<X>>;
    template <class T>
    using __uncvref = std::remove_cv_t<std::remove_reference_t<T>>;
    template <class T, class U>
    using __cond_res = decltype(true ? std::declval<T>() : std::declval<U>());

    template <class From, class To>
    struct __copycv_ : __id<To> {};
    template <class From, class To>
    struct __copycv_<From const, To> : std::add_const<To> {};
    template <class From, class To>
    struct __copycv_<From volatile, To> : std::add_volatile<To> {};
    template <class From, class To>
    struct __copycv_<From const volatile, To> : std::add_cv<To> {};
    template <class From, class To>
    using __copycv = __t<__copycv_<From, To>>;

    template <class T, class U, class = void>
    struct __builtin_common {};
    template <class T, class U>
    using __builtin_common_t = __t<__builtin_common<T, U>>;
    template <class T, class U>
    struct __builtin_common<T, U, std::enable_if_t<_Valid<__cond_res, __cref<T>, __cref<U>>>>
      : std::decay<__cond_res<__cref<T>, __cref<U>>> {};
    template <class T, class U, class R = detected_t<__builtin_common_t, T&, U&>>
    using __rref_res =
      std::conditional_t<__v<std::is_reference<R>>, std::remove_reference_t<R>&&, R>;
    template <class T, class U>
    struct __builtin_common<T&&, U&&,
      std::enable_if_t<_Valid<__builtin_common_t, T&, U&>
        && _ConvertibleTo<T&&, __rref_res<T, U>>
        && _ConvertibleTo<U&&, __rref_res<T, U>>>>
      : __id<__rref_res<T, U>> {};
    template <class T, class U>
    using __lref_res = __cond_res<__copycv<T, U>&, __copycv<U, T>&>;
    template <class T, class U>
    struct __builtin_common<T&, U&> : __defer<void, __lref_res, T, U> {};
    template <class T, class U>
    struct __builtin_common<T&, U&&,
      std::enable_if_t<_Valid<__builtin_common_t, T&, U const&>
        && _ConvertibleTo<U&&, __builtin_common_t<T&, U const&>>>>
      : __builtin_common<T&, U const&> {};
    template <class T, class U>
    struct __builtin_common<T&&, U&> : __builtin_common<U&, T&&> {};

    // common_type
    template <class, class... Ts>
    struct common_type {};

    template <class... T>
    using common_type_t = __t<common_type<void, T...>>;

    template <class T>
    struct common_type<void, T> : std::decay<T> {};

    template <class T>
    inline constexpr bool _Decayed = __v<std::is_same<std::decay_t<T>, T>>;

    template <class T, class U, class = void>
    struct __common_type2 : common_type<void, std::decay_t<T>, std::decay_t<U>> {};

    template <class T, class U>
    struct __common_type2<T, U, std::enable_if_t<_Decayed<T> && _Decayed<U>>>
      : __builtin_common<T, U> {};

    template <class T, class U>
    struct common_type<void, T, U> : __common_type2<T, U> {};

    template <class T, class U, class V, class... W>
    struct common_type<std::enable_if_t<_Valid<common_type_t, T, U>>, T, U, V, W...>
      : common_type<void, common_type_t<T, U>, V, W...> {};

    namespace __qual {
      using __rref = __q<std::add_rvalue_reference_t>;
      using __lref = __q<std::add_lvalue_reference_t>;
      template <class>
      struct __xref : __id<__compose<__q<__t>, __q<__id>>> {};
      template <class T>
      struct __xref<T&> : __id<__compose<__lref, __t<__xref<T>>>> {};
      template <class T>
      struct __xref<T&&> : __id<__compose<__rref, __t<__xref<T>>>> {};
      template <class T>
      struct __xref<const T> : __id<__q<std::add_const_t>> {};
      template <class T>
      struct __xref<volatile T> : __id<__q<std::add_volatile_t>> {};
      template <class T>
      struct __xref<const volatile T> : __id<__q<std::add_cv_t>> {};
    } // namespace __qual

    template <class T, class U, template <class> class TQual, template <class> class UQual>
    struct basic_common_reference {};

    template <class T, class U>
    using __basic_common_reference =
      basic_common_reference<__uncvref<T>,
                             __uncvref<U>,
                             __qual::__xref<T>::type::template apply,
                             __qual::__xref<U>::type::template apply>;

    // common_reference
    template <class, class... T>
    struct common_reference {};

    template <class... T>
    using common_reference_t = __t<common_reference<void, T...>>;

    template <class T>
    struct common_reference<void, T> : __id<T> {};

    template <class T, class U, class = void>
    struct __common_reference2 : std::conditional_t<__v<__has_type<__basic_common_reference<T, U>>>,
                                                    __basic_common_reference<T, U>,
                                                    common_type<void, T, U>> {};

    template <class T, class U>
    struct __common_reference2<T, U,
      std::enable_if_t<_Valid<__builtin_common_t, T, U>
        && _Is<__builtin_common_t<T, U>, std::is_reference>>>
      : __builtin_common<T, U> {};

    template <class T, class U>
    struct common_reference<void, T, U> : __common_reference2<T, U> {};

    template <class T, class U, class V, class... W>
    struct common_reference<std::enable_if_t<_Valid<common_reference_t, T, U>>, T, U, V, W...>
      : common_reference<void, common_reference_t<T, U>, V, W...> {};
      // clang-format on
    } // namespace _common_reference
  }   // namespace type_traits
  /// @endcond
  using type_traits::_common_reference::common_reference;
  using type_traits::_common_reference::common_reference_t;
} // namespace iris
