#pragma once
namespace iris {
  struct identity {
    template <class T>
    constexpr T&& operator()(T&& t) const noexcept(
      noexcept(std::forward<T>(t))) {
      return std::forward<T>(t);
    }
  };

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

  template <class... Ts>
  [[deprecated]] void type_of(Ts&&...) {}
} // namespace iris
