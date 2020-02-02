#include <bits/stdc++.h>
#include <iris/type_traits.hpp>
namespace ts {
  template <class... Ts>
  [[deprecated]] void type_of(Ts&&...) {}

  template <class T, std::size_t... Indicies>
  inline void measure_impl(T&& task, std::index_sequence<Indicies...>) {
    using swallow = std::initializer_list<std::size_t>;
    (void)swallow{(void(task()), Indicies)...};
  }
  template <std::size_t N = 1, class T>
  double measure(T&& task) {
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();
    measure_impl(std::forward<T>(task), std::make_index_sequence<N>{});
    end = std::chrono::system_clock::now();
    return 1e-6 * static_cast<double>( //
             std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
  }

  template <class T>
  using uniform_distribution = //
    std::enable_if_t<std::is_arithmetic_v<T>,
                     std::conditional_t<std::is_integral_v<T>,
                                        std::uniform_int_distribution<T>,
                                        std::uniform_real_distribution<T>>>;

  template <class T>
  struct uniform {
  private:
    T min, max;
    std::size_t limit = 0;
    std::mt19937 mt{std::random_device{}()};
    uniform_distribution<T> dist{min, max};

    template <class Pred, std::size_t... Indices>
    bool required_impl(Pred&& pred, std::index_sequence<Indices...>) {
      return std::forward<Pred>(pred)((void(Indices), dist(mt))...);
    }

  public:
    uniform(T min, iris::type_identity_t<T> max)
      : min(std::min(min, max)), max(std::max(min, max)) {}
    uniform(T min, iris::type_identity_t<T> max, std::size_t limit)
      : min(std::min(min, max)), max(std::max(min, max)), limit(limit) {}

    auto& take(std::size_t _limit) {
      limit = _limit;
      return *this;
    }

    template <int N = 1, class Pred>
    bool required(Pred&& pred) {
      bool result = true;
      for (std::size_t i = 0; i < limit && result; ++i)
        result = required_impl(std::forward<Pred>(pred), std::make_index_sequence<N>{});
      return result;
    }
  };
} // namespace ts

template <std::size_t N, class T>
inline void mm_square(const T& A, const T& B, T& C) {
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t k = 0; k < N; ++k) {
      for (std::size_t j = 0; j < N; ++j) {
        C[i * N + j] += A[i * N + k] * B[k * N + j];
      }
    }
  }
}

int main() {
  constexpr std::size_t N = 512;
  using Array             = std::array<float, N * N>;

  alignas(16) Array a, c;
  std::ifstream input("input");
  for (auto& x : a) input >> x;
  std::fill(begin(c), end(c), 0);
  // std::cout << ts::measure([&]() { mm_square<N>(a, a, c); }) << std::endl;
  ts::uniform test(0.0, 10, 2);
  std::cout << test.required<2>([](double, double) { return true; });
  std::cout << test.required([](double d) { std::cout << d << std::endl; return true; });
}
