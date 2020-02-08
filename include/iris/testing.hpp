#pragma once
#include <iris/concepts.hpp>
#include <iris/utility/semiregular_box.hpp>
#include <chrono>
#include <random>

namespace iris {
  // compile time type inspector
  template <typename... Ts>
  [[deprecated]] void type_of(Ts&&...) {}

  template <typename, typename = std::void_t<>>
  struct is_clock : std::false_type {};
  template <typename T>
  struct is_clock<T,
                  std::void_t<typename T::rep, typename T::period,
                              typename T::duration, typename T::time_point,
                              decltype(T::is_steady), decltype(T::now())> //
                  > : std::true_type {};
  template <typename T>
  inline constexpr bool is_clock_v = is_clock<T>::value;
  template <typename clock                 = std::chrono::high_resolution_clock,
            enable_if_t<is_clock_v<clock>> = nullptr>
  struct stop_watch {
  private:
    typename clock::time_point strt{}, end{};

  public:
    stop_watch() = default;
    void start() { strt = clock::now(); }
    void stop() { end = clock::now(); }
    auto seconds() {
      return 1e-6 * static_cast<double>( //
               std::chrono::duration_cast<std::chrono::microseconds>(end - strt).count());
    }
  };

  namespace testing {
    template <typename T>
    using urbg_min_t = decltype(T::min());
    template <typename T>
    using urbg_max_t = decltype(T::max());
  } // namespace testing
  IRIS_DEFINE_UNARY_CONCEPT(
    is_uniform_random_bit_generator, G,
    std::is_invocable<G&>,
    is_unsigned_integral<std::invoke_result_t<G&>>,
    is_detected_exact<std::invoke_result_t<G&>, testing::urbg_min_t, G>,
    is_detected_exact<std::invoke_result_t<G&>, testing::urbg_max_t, G>);
  template <typename T>
  using uniform_distribution =
    std::enable_if_t<std::is_arithmetic_v<T>,
                     std::conditional_t<std::is_integral_v<T>,
                                        std::uniform_int_distribution<T>,
                                        std::uniform_real_distribution<T>>>;
  template <typename T, typename Engine = std::mt19937, // should be std::default_random_engine?
            enable_if_t<std::is_arithmetic_v<T>         //
                        && is_uniform_random_bit_generator_v<Engine>> = nullptr>
  struct urng {
  private:
    Engine engine{std::random_device{}()};
    semiregular_box<uniform_distribution<T>> dist{};

  public:
    using result_type = T;
    urng(T min, type_identity_t<T> max)
      : dist{std::in_place, std::min(min, max), std::max(min, max)} {}
    void operator=(const urng&) = delete;
    void operator=(urng&&) = delete;
    auto operator()() -> decltype(dist->operator()(engine)) {
      return dist->operator()(engine);
    }
    auto min() -> decltype(dist->min()) {
      return dist->min();
    }
    auto max() -> decltype(dist->max()) {
      return dist->max();
    }
    void set_range(result_type min, result_type max) {
      dist.emplace(std::min(min, max), std::max(min, max));
    }
  };
} // namespace iris
