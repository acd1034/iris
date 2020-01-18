#pragma once
#include <type_traits>

namespace iris {
  // https://en.cppreference.com/w/cpp/types/type_identity
  template <class T>
  struct type_identity {
    using type = T;
  };
  template <class T>
  using type_identity_t = typename type_identity<T>::type;

  // https://en.cppreference.com/w/cpp/experimental/is_detected
  namespace type_traits {
    struct nonesuch {
      nonesuch()                = delete;
      ~nonesuch()               = delete;
      nonesuch(nonesuch const&) = delete;
      void operator=(nonesuch const&) = delete;
    };

    template <typename Default,
              typename AlwaysVoid,
              template <typename...> typename Op,
              typename... Args>
    struct detected_or_impl {
      using value_t = std::false_type;
      using type    = Default;
    };

    template <typename Default,
              template <typename...> typename Op,
              typename... Args>
    struct detected_or_impl<Default, std::void_t<Op<Args...>>, Op, Args...> {
      using value_t = std::true_type;
      using type    = Op<Args...>;
    };
  } // namespace type_traits

  template <typename Default,
            template <typename...> typename Op,
            typename... Args>
  using is_detected_or =
    typename type_traits::detected_or_impl<Default, void, Op, Args...>::value_t;

  template <typename Default,
            template <typename...> typename Op,
            typename... Args>
  using detected_or_t =
    typename type_traits::detected_or_impl<Default, void, Op, Args...>::type;

  template <typename Default,
            template <typename...> typename Op,
            typename... Args>
  inline constexpr bool is_detected_or_v =
    is_detected_or<Default, Op, Args...>::value;

  template <template <typename...> typename Op, typename... Args>
  using is_detected = is_detected_or<type_traits::nonesuch, Op, Args...>;

  template <template <typename...> typename Op, typename... Args>
  using detected_t = detected_or_t<type_traits::nonesuch, Op, Args...>;

  template <template <typename...> typename Op, typename... Args>
  inline constexpr bool is_detected_v = is_detected<Op, Args...>::value;

  template <typename Expected,
            template <typename...> typename Op,
            typename... Args>
  using is_detected_exact = std::is_same<Expected, detected_t<Op, Args...>>;

  template <typename Expected,
            template <typename...> typename Op,
            typename... Args>
  inline constexpr bool is_detected_exact_v =
    is_detected_exact<Expected, Op, Args...>::value;

  template <typename To, template <typename...> typename Op, typename... Args>
  using is_detected_convertible =
    std::is_convertible<detected_t<Op, Args...>, To>;

  template <typename To, template <typename...> typename Op, typename... Args>
  inline constexpr bool is_detected_convertible_v =
    is_detected_convertible<To, Op, Args...>::value;

  // detected_satisfy == (detected && satisfy)
  template <template <typename> typename Concept,
            template <typename...> typename Op,
            typename... Args>
  using is_detected_satisfy = Concept<detected_t<Op, Args...>>;

  template <template <typename> typename Concept,
            template <typename...> typename Op,
            typename... Args>
  inline constexpr bool is_detected_satisfy_v =
    is_detected_satisfy<Concept, Op, Args...>::value;

  // detected_dissatisfy == (detected && !satisfy) != !detected_satisfy
  template <template <typename> typename Concept,
            template <typename...> typename Op,
            typename... Args>
  using is_detected_dissatisfy =
    std::conjunction<is_detected<Op, Args...>,
                     std::negation<is_detected_satisfy<Concept, Op, Args...>>>;

  template <template <typename> typename Concept,
            template <typename...> typename Op,
            typename... Args>
  inline constexpr bool is_detected_dissatisfy_v =
    is_detected_dissatisfy<Concept, Op, Args...>::value;

  template <typename T>
  struct remove_cvref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
  };

  template <typename T>
  using remove_cvref_t = typename remove_cvref<T>::type;

  template <bool B, typename T = std::nullptr_t>
  using enable_if_t = typename std::enable_if<B, T>::type;

  template <typename...>
  inline constexpr bool false_v = false;
} // namespace iris
