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
    iterator_type iter{};

  public:
    // ctor
    constexpr wrap_iter() noexcept {}
    constexpr wrap_iter(iterator_type iter) noexcept : iter(iter) {}
    template <class U, std::enable_if_t<std::is_convertible_v<U, iterator_type>,
                                        std::nullptr_t> = nullptr>
    constexpr wrap_iter(const wrap_iter<U>& u) noexcept : iter(u.get()) {}

    // operator
    constexpr reference operator*() const noexcept { return *iter; }
    constexpr pointer operator->() const noexcept {
      return static_cast<pointer>(std::addressof(*iter));
    }
    constexpr wrap_iter& operator++() noexcept {
      ++iter;
      return *this;
    }
    constexpr wrap_iter operator++(int) noexcept {
      wrap_iter tmp{*this};
      ++(*this);
      return tmp;
    }
    constexpr wrap_iter& operator--() noexcept {
      --iter;
      return *this;
    }
    constexpr wrap_iter operator--(int) noexcept {
      wrap_iter tmp{*this};
      --(*this);
      return tmp;
    }
    constexpr wrap_iter& operator+=(difference_type n) noexcept {
      iter += n;
      return *this;
    }
    constexpr wrap_iter& operator-=(difference_type n) noexcept {
      *this += -n;
      return *this;
    }
    constexpr reference operator[](difference_type n) const noexcept {
      return iter[n];
    }

  private:
    // member
    constexpr iterator_type get() const noexcept { return iter; }

    // friend
    template <class Iter1, class Iter2>
    constexpr friend bool operator==(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter2>& y) noexcept {
      return x.get() == y.get();
    }

    template <class Iter1, class Iter2>
    constexpr friend bool operator<(const wrap_iter<Iter1>& x,
                                    const wrap_iter<Iter2>& y) noexcept {
      return x.get() < y.get();
    }

    template <class Iter1, class Iter2>
    constexpr friend bool operator!=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter2>& y) noexcept {
      return !(x == y);
    }

    template <class Iter1, class Iter2>
    constexpr friend bool operator>(const wrap_iter<Iter1>& x,
                                    const wrap_iter<Iter2>& y) noexcept {
      return y < x;
    }

    template <class Iter1, class Iter2>
    constexpr friend bool operator>=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter2>& y) noexcept {
      return !(x < y);
    }

    template <class Iter1, class Iter2>
    constexpr friend bool operator<=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter2>& y) noexcept {
      return !(y < x);
    }

    template <class Iter1>
    constexpr friend bool operator!=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter1>& y) noexcept {
      return !(x == y);
    }

    template <class Iter1>
    constexpr friend bool operator>(const wrap_iter<Iter1>& x,
                                    const wrap_iter<Iter1>& y) noexcept {
      return y < x;
    }

    template <class Iter1>
    constexpr friend bool operator>=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter1>& y) noexcept {
      return !(x < y);
    }

    template <class Iter1>
    constexpr friend bool operator<=(const wrap_iter<Iter1>& x,
                                     const wrap_iter<Iter1>& y) noexcept {
      return !(y < x);
    }

    template <class Iter1>
    constexpr friend wrap_iter<Iter1>
    operator+(wrap_iter<Iter1> x,
              typename wrap_iter<Iter1>::difference_type n) noexcept {
      return x += n;
    }

    template <class Iter1>
    constexpr friend wrap_iter<Iter1>
    operator+(typename wrap_iter<Iter1>::difference_type n,
              wrap_iter<Iter1> x) noexcept {
      return x += n;
    }

    template <class Iter1>
    constexpr friend wrap_iter<Iter1>
    operator-(wrap_iter<Iter1> x,
              typename wrap_iter<Iter1>::difference_type n) noexcept {
      return x -= n;
    }

    template <class Iter1, class Iter2>
    constexpr friend auto operator-(const wrap_iter<Iter1>& x,
                                    const wrap_iter<Iter2>& y) noexcept
      -> decltype(x.get() - y.get()) {
      return x.get() - y.get();
    }

    template <class T, std::enable_if_t<std::is_trivially_copy_assignable_v<T>,
                                        std::nullptr_t> = nullptr>
    constexpr friend T* unwrap_iter(wrap_iter<T*> iter) {
      return iter.get();
    }

    template <class T, std::enable_if_t<std::is_trivially_copy_assignable_v<T>,
                                        std::nullptr_t> = nullptr>
    constexpr friend const T* unwrap_iter(wrap_iter<const T*> iter) {
      return iter.get();
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
