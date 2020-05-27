#include <cassert>
#include <cstdint>
#include <iosfwd>
#include <numeric>
#include <tuple>
#include <type_traits>

namespace detail {
  template <typename T>
  constexpr T extended_euclid_impl(T a, T b, T& x, T& y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }
    T d = extended_euclid_impl(b, a % b, y, x);
    y -= a / b * x;
    return d;
  }
} // namespace detail
template <typename T, typename U>
constexpr auto extended_euclid(T a, U b) {
  using V = std::make_signed_t<std::common_type_t<T, U>>;
  std::pair<V, V> result;
  detail::extended_euclid_impl<V>(a, b, result.first, result.second);
  return result;
}

template <typename T, T N>
struct modint {
  static_assert(std::is_arithmetic_v<T>);
  using sint_type             = std::make_signed_t<T>;
  using uint_type             = std::make_unsigned_t<T>;
  static inline sint_type mod = sint_type(N);

private:
  sint_type v{0};
  // private member fn
  constexpr sint_type normalize(sint_type x) const {
    x %= mod;
    if (x < 0) x += mod;
    return x;
  }
  constexpr sint_type inverse(sint_type x) const {
    assert(std::gcd(x, mod) == 1);
    return normalize(extended_euclid(x, mod).first);
  }

public:
  // ctor
  constexpr modint()                  = default;
  constexpr modint(modint const& rhs) = default;
  constexpr modint(modint&& rhs)      = default;
  constexpr explicit modint(sint_type const v) : v{normalize(v)} {}
  constexpr explicit modint(uint_type const v) : v{(sint_type(v) >= mod ? sint_type(v) : sint_type(v) % mod)} {} // special
  // assignment op
  constexpr modint& operator=(modint const& rhs) = default;
  constexpr modint& operator=(modint&& rhs) = default;
  constexpr modint& operator                =(sint_type const rhs) {
    v = normalize(rhs);
    return *this;
  }
  // cast
  constexpr explicit operator sint_type() const noexcept { return v; }
  constexpr explicit operator uint_type() const noexcept { return uint_type(v); }
  // unary arithmetic op
  constexpr modint operator+() const& noexcept { return *this; }
  constexpr modint&& operator+() && noexcept { return std::move(*this); }
  constexpr modint operator-() const& noexcept { return modint{mod - v}; }
  constexpr modint&& operator-() && noexcept {
    v = mod - v;
    return std::move(*this);
  }
  constexpr modint inverse() const& { return modint{inverse(v)}; }
  constexpr modint&& inverse() && {
    v = inverse(v);
    return std::move(*this);
  }
  constexpr modint& operator++() noexcept {
    if (v == mod)
      v = 0;
    else
      ++v;
    return *this;
  }
  constexpr modint& operator--() noexcept {
    if (v == 0)
      v = mod - 1;
    else
      --v;
    return *this;
  }
  constexpr modint operator++(int) noexcept {
    modint result{*this};
    ++*this;
    return result;
  }
  constexpr modint operator--(int) noexcept {
    modint result{*this};
    --*this;
    return result;
  }
  // compound assignment
  constexpr modint& operator+=(modint const& rhs) noexcept {
    v += rhs.v;
    if (v >= mod) v -= mod;
    return *this;
  }
  constexpr modint& operator+=(modint&& rhs) noexcept {
    v += std::move(rhs.v);
    if (v >= mod) v -= mod;
    return *this;
  }
  constexpr modint& operator+=(sint_type const rhs) {
    v = normalize(v + rhs);
    return *this;
  }
  constexpr modint& operator-=(modint const& rhs) noexcept { return *this += -rhs; }
  constexpr modint& operator-=(modint&& rhs) noexcept { return *this += -std::move(rhs); }
  constexpr modint& operator-=(sint_type const rhs) { return *this += -rhs; }
  constexpr modint& operator*=(modint const& rhs) noexcept {
    v *= rhs.v;
    if (v >= mod) v %= mod;
    return *this;
  }
  constexpr modint& operator*=(modint&& rhs) noexcept {
    v *= std::move(rhs.v);
    if (v >= mod) v %= mod;
    return *this;
  }
  constexpr modint& operator*=(sint_type const rhs) {
    v = normalize(v * rhs);
    return *this;
  }
  constexpr modint& operator/=(modint const& rhs) { return *this *= rhs.inverse(); }
  constexpr modint& operator/=(modint&& rhs) { return *this *= std::move(rhs).inverse(); }
  constexpr modint& operator/=(sint_type const rhs) { return *this *= inverse(rhs); }
  // public member fn
  constexpr modint pow(std::size_t exp) const& {
    modint base{*this};
    return std::move(base).pow(exp);
  }
  constexpr modint pow(std::size_t exp) && {
    if (exp < 0) return std::move(*this).inverse().pow(-exp);
    modint result{1};
    while (exp > 0) {
      if (exp & 1) result *= *this;
      *this *= *this;
      exp >>= 1;
    }
    return result;
  }
#pragma region friend
  // equality compare
  friend constexpr bool operator==(modint const& lhs, modint const& rhs) noexcept { return lhs.v == rhs.v; }
  friend constexpr bool operator==(modint const& lhs, sint_type const& rhs) noexcept { return lhs.v == rhs; }
  friend constexpr bool operator==(sint_type const& lhs, modint const& rhs) noexcept { return rhs == lhs; }
  friend constexpr bool operator!=(modint const& lhs, modint const& rhs) noexcept { return !(lhs == rhs); }
  friend constexpr bool operator!=(modint const& lhs, sint_type const& rhs) noexcept { return !(lhs == rhs); }
  friend constexpr bool operator!=(sint_type const& lhs, modint const& rhs) noexcept { return !(lhs == rhs); }
  // compare
  friend constexpr bool operator<(modint const& lhs, modint const& rhs) noexcept { return lhs.v < rhs.v; }
  friend constexpr bool operator<(modint const& lhs, sint_type const& rhs) noexcept { return lhs.v < rhs; }
  friend constexpr bool operator<(sint_type const& lhs, modint const& rhs) noexcept { return lhs < rhs.v; }
  friend constexpr bool operator>(modint const& lhs, modint const& rhs) noexcept { return rhs < lhs; }
  friend constexpr bool operator>(modint const& lhs, sint_type const& rhs) noexcept { return rhs < lhs; }
  friend constexpr bool operator>(sint_type const& lhs, modint const& rhs) noexcept { return rhs < lhs; }
  friend constexpr bool operator<=(modint const& lhs, modint const& rhs) noexcept { return !(lhs > rhs); }
  friend constexpr bool operator<=(modint const& lhs, sint_type const& rhs) noexcept { return !(lhs > rhs); }
  friend constexpr bool operator<=(sint_type const& lhs, modint const& rhs) noexcept { return !(lhs > rhs); }
  friend constexpr bool operator>=(modint const& lhs, modint const& rhs) noexcept { return !(lhs < rhs); }
  friend constexpr bool operator>=(modint const& lhs, sint_type const& rhs) noexcept { return !(lhs < rhs); }
  friend constexpr bool operator>=(sint_type const& lhs, modint const& rhs) noexcept { return !(lhs < rhs); }
// binary arithmetic op
// clang-format off
  #define IRIS_DEFINE_BINARY_OP(Op)                                                 \
    friend constexpr modint operator Op(modint const& lhs, modint const& rhs) {     \
      modint result{lhs};                                                           \
      result Op## = rhs;                                                            \
      return result;                                                                \
    }                                                                               \
    friend constexpr modint&& operator Op(modint&& lhs, modint const& rhs) {        \
      lhs Op## = rhs;                                                               \
      return std::move(lhs);                                                        \
    }                                                                               \
    friend constexpr modint&& operator Op(modint const& lhs, modint&& rhs) {        \
      return std::move(rhs) Op lhs;                                                 \
    }                                                                               \
    friend constexpr modint&& operator Op(modint&& lhs, modint&& rhs) {             \
      return std::move(lhs) Op rhs;                                                 \
    }                                                                               \
    friend constexpr modint operator Op(modint const& lhs, sint_type const rhs) {   \
      modint result{lhs};                                                           \
      result Op## = rhs;                                                            \
      return result;                                                                \
    }                                                                               \
    friend constexpr modint&& operator Op(modint&& lhs, sint_type const rhs) {      \
      lhs Op## = rhs;                                                               \
      return std::move(lhs);                                                        \
    }                                                                               \
    friend constexpr modint&& operator Op(sint_type const lhs, modint const& rhs) { \
      return rhs Op lhs;                                                            \
    }                                                                               \
    friend constexpr modint&& operator Op(sint_type const lhs, modint&& rhs) {      \
      return std::move(rhs) Op lhs;                                                 \
    }
  IRIS_DEFINE_BINARY_OP(+)
  IRIS_DEFINE_BINARY_OP(-)
  IRIS_DEFINE_BINARY_OP(*)
  IRIS_DEFINE_BINARY_OP(/)
  #undef IRIS_DEFINE_BINARY_OP
  // clang-format on
  // stream insertion, extraction
  template <typename CharT, typename Traits>
  friend auto& operator<<(std::basic_ostream<CharT, Traits>& os, modint const& rhs) { return os << rhs.v; }
  template <typename CharT, typename Traits>
  friend auto& operator>>(std::basic_istream<CharT, Traits>& is, modint& rhs) {
    uint_type v;
    is >> v;
    rhs = modint{v};
    return is;
  }
#pragma endregion
};
// type alias
template <std::uint32_t N>
using modint32 = modint<std::uint32_t, N>;
template <std::uint64_t N>
using modint64 = modint<std::uint64_t, N>;

#include <iostream>
int main() {
  {
    std::uint64_t n{4};
    modint32<13> x{uint32_t(n)};
    std::ignore = x + n;
    std::ignore = x - n;
    std::ignore = x * n;
    std::ignore = x / n;
    std::ignore = x.inverse();
    std::ignore = x.pow(2);
    std::ignore = x == n;
    std::ignore = x != n;
    std::ignore = x < n;
    std::ignore = x > n;
    std::ignore = x <= n;
    std::ignore = x >= n;
  }
  {
    std::ignore = modint32<13>{-4} + (-4);
    std::ignore = modint32<13>{-4} - (-4);
    std::ignore = modint32<13>{-4} * (-4);
    std::ignore = modint32<13>{-4} / (-4);
    std::ignore = modint32<13>{-4}.inverse();
    std::ignore = modint32<13>{-4}.pow(2);
    std::ignore = modint32<13>{-4} == (-4);
    std::ignore = modint32<13>{-4} != (-4);
    std::ignore = modint32<13>{-4} < (-4);
    std::ignore = modint32<13>{-4} > (-4);
    std::ignore = modint32<13>{-4} <= (-4);
    std::ignore = modint32<13>{-4} >= (-4);
  }
}
