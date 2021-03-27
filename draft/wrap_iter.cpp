#include <iterator>
namespace ns {
  template <class Iter>
  struct wrap_iter {
  public:
    // type alias
    // clang-format off
    using iterator_type     = Iter;
    using iterator_category = typename std::iterator_traits<iterator_type>::iterator_category;
    using value_type        = typename std::iterator_traits<iterator_type>::value_type;
    using difference_type   = typename std::iterator_traits<iterator_type>::difference_type;
    using pointer           = typename std::iterator_traits<iterator_type>::pointer;
    using reference         = typename std::iterator_traits<iterator_type>::reference;
    // clang-format on

  private:
    // member variables
    iterator_type iter{};

  public:
    // ctor
    constexpr wrap_iter() noexcept                 = default;
    constexpr wrap_iter(const wrap_iter&) noexcept = default;
    constexpr wrap_iter(iterator_type iter) noexcept : iter(iter) {}
    template <class T,
              std::enable_if_t<std::is_convertible_v<T, iterator_type>, std::nullptr_t> = nullptr>
    constexpr wrap_iter(const wrap_iter<T>& other) noexcept : iter(other.iter) {}
    // assign
    constexpr wrap_iter& operator=(const wrap_iter&) noexcept = default;
    template <class T,
              std::enable_if_t<std::is_convertible_v<T, iterator_type>, std::nullptr_t> = nullptr>
    constexpr wrap_iter& operator=(const wrap_iter<T>& other) noexcept {
      iter = other.iter;
    }
    // operator
    constexpr pointer operator->() const noexcept {
      return static_cast<pointer>(std::addressof(*iter));
    }
    constexpr reference operator*() const noexcept { return *iter; }
    template <class U,
              std::enable_if_t<std::is_member_object_pointer_v<U>, std::nullptr_t> = nullptr>
    constexpr auto& operator->*(U u) const noexcept {
      return iter->*u;
    }
    template <class U,
              std::enable_if_t<std::is_member_function_pointer_v<U>, std::nullptr_t> = nullptr>
    constexpr auto operator->*(U u) const noexcept {
      return
        [u, this](auto&&... args) { return (iter->*u)(std::forward<decltype(args)>(args)...); };
    }
    constexpr wrap_iter& operator++() noexcept {
      ++iter;
      return *this;
    }
    constexpr wrap_iter& operator--() noexcept {
      --iter;
      return *this;
    }
    constexpr wrap_iter& operator+=(difference_type n) noexcept {
      iter += n;
      return *this;
    }
    constexpr wrap_iter& operator-=(difference_type n) noexcept {
      iter -= n;
      return *this;
    }
    constexpr reference operator[](difference_type n) const noexcept { return iter[n]; }
    // friend
    template <class T>
    friend struct wrap_iter;
    constexpr friend difference_type operator-(const wrap_iter& x, const wrap_iter& y) noexcept {
      return x.iter - y.iter;
    }
    constexpr friend bool operator==(const wrap_iter& x, const wrap_iter& y) noexcept {
      return x.iter == y.iter;
    }
    constexpr friend bool operator<(const wrap_iter& x, const wrap_iter& y) noexcept {
      return x.iter < y.iter;
    }

    // boilerplate
    constexpr wrap_iter operator++(int) noexcept(noexcept(++*this)) {
      wrap_iter tmp{*this};
      ++*this;
      return tmp;
    }
    constexpr wrap_iter operator--(int) noexcept(noexcept(--*this)) {
      wrap_iter tmp{*this};
      --*this;
      return tmp;
    }
    constexpr friend wrap_iter
    operator+(wrap_iter x, typename wrap_iter::difference_type n) noexcept(noexcept(x += n)) {
      return x += n;
    }
    constexpr friend wrap_iter operator+(typename wrap_iter::difference_type n,
                                         wrap_iter x) noexcept(noexcept(x += n)) {
      return x += n;
    }
    constexpr friend wrap_iter
    operator-(wrap_iter x, typename wrap_iter::difference_type n) noexcept(noexcept(x -= n)) {
      return x -= n;
    }
    constexpr friend bool operator!=(const wrap_iter& x,
                                     const wrap_iter& y) noexcept(noexcept(x == y)) {
      return !(x == y);
    }
    constexpr friend bool operator>(const wrap_iter& x,
                                    const wrap_iter& y) noexcept(noexcept(y < x)) {
      return y < x;
    }
    constexpr friend bool operator<=(const wrap_iter& x,
                                     const wrap_iter& y) noexcept(noexcept(y < x)) {
      return !(y < x);
    }
    constexpr friend bool operator>=(const wrap_iter& x,
                                     const wrap_iter& y) noexcept(noexcept(x < y)) {
      return !(x < y);
    }
  };
} // namespace ns

#include <iostream>
#include <vector>
int main() {
  std::vector v{1, 2, 3, 4, 5};
  ns::wrap_iter w{std::end(v)};
  for (ns::wrap_iter i{std::begin(v)}; i < w;) std::cout << *i++ << '\n';
  std::ignore = ns::wrap_iter{w};
}
