#pragma once
#include <chrono>
#include <random>
#include <iris/utility/semiregular_box.hpp>

namespace iris {
  // compile time type inspector
  template <typename... Ts>
  [[deprecated]] void type_of(Ts&&...) {}

  struct stop_watch {
  private:
    std::chrono::system_clock::time_point begin, end;

  public:
    stop_watch() = default;
    void start() { begin = std::chrono::system_clock::now(); }
    void stop() { end = std::chrono::system_clock::now(); }
    auto value() {
      return 1e-6 * static_cast<double>( //
               std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
    }
  };

  template <typename T>
  using uniform_distribution =
    std::enable_if_t<std::is_arithmetic_v<T>,
                     std::conditional_t<std::is_integral_v<T>,
                                        std::uniform_int_distribution<T>,
                                        std::uniform_real_distribution<T>>>;
  template <typename T, typename Engine = std::mt19937,
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
    auto operator()() -> decltype(dist->operator(engine)) {
      return dist->operator(engine);
    }
    auto min() -> decltype(dist->min();) {
      return dist->min();
    }
    auto max() -> decltype(dist->max();) {
      return dist->max();
    }
    void set_range(result_type min, result_type max) {
      dist.emplace(std::min(min, max), std::max(min, max));
    }
  };
} // namespace iris
