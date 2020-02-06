#pragma once
#include <iris/utility/semiregular_box.hpp>
#include <chrono>
#include <random>

namespace iris {
  // compile time type inspector
  template <typename... Ts>
  [[deprecated]] void type_of(Ts&&...) {}

  template <typename clock = std::chrono::high_resolution_clock>
  struct stop_watch {
  private:
    typename clock::time_point strt, end;

  public:
    stop_watch() = default;
    void start() { strt = clock::now(); }
    void stop() { end = clock::now(); }
    auto value() {
      return 1e-6 * static_cast<double>( //
               std::chrono::duration_cast<std::chrono::microseconds>(end - strt).count());
    }
  };

  template <typename T>
  using uniform_distribution =
    std::enable_if_t<std::is_arithmetic_v<T>,
                     std::conditional_t<std::is_integral_v<T>,
                                        std::uniform_int_distribution<T>,
                                        std::uniform_real_distribution<T>>>;
  template <typename T, typename Engine = std::mt19937, // should be std::default_random_engine?
            enable_if_t<std::is_arithmetic_v<T>> = nullptr>
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
