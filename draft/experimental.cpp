#include <iris/iostream.hpp>
namespace iris {
  template <typename T, enable_if_t<std::is_floating_point_v<T>> = nullptr>
  inline constexpr T pi_v = static_cast<T>(3.141592653589793238462643383279502884L);

  // https://en.cppreference.com/w/cpp/utility/variant/visit
  template <class... Ts>
  struct overloaded : Ts... { using Ts::operator()...; };
  template <class... Ts>
  overloaded(Ts...)->overloaded<Ts...>;

  template <typename Fn>
  struct scope_exit {
  private:
    Fn fn;

  public:
    constexpr explicit scope_exit(Fn const& fn) noexcept : fn(fn) {}
    constexpr explicit scope_exit(Fn&& fn) noexcept : fn(std::move(fn)) {}
    scope_exit()                  = delete;
    scope_exit(scope_exit const&) = delete;
    scope_exit(scope_exit&&)      = delete;
    void operator=(scope_exit const&) = delete;
    void operator=(scope_exit&&) = delete;
    ~scope_exit() noexcept { fn(); }
  };

  template <class T>
  [[deprecated]] void type(T&&) {}
} // namespace iris
int main() {
  using std::cout;
  std::cout << iris::pi_v<double> << std::endl;
}
