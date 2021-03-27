#include <iterator>
struct MyIterator {
public:
  // type alias
  // clang-format off
  using iterator_category = /* implementation */;
  using value_type        = /* implementation */;
  using difference_type   = std::ptrdiff_t;
  using pointer           = /* implementation */;
  using reference         = /* implementation */;
  // clang-format on

private:
  // member object

public:
  // ctor
  constexpr MyIterator() noexcept                  = default;
  constexpr MyIterator(const MyIterator&) noexcept = default;
  // assign
  constexpr MyIterator& operator=(const MyIterator&) noexcept = default;
  // operator
  constexpr pointer operator->() const noexcept { return /* implementation */; }
  constexpr reference operator*() const noexcept { return /* implementation */; }
  template <class U, std::enable_if_t<std::is_member_object_pointer_v<U>, std::nullptr_t> = nullptr>
  constexpr auto& operator->*(U u) const noexcept {
    return /* implementation */->*u;
  }
  template <class U,
            std::enable_if_t<std::is_member_function_pointer_v<U>, std::nullptr_t> = nullptr>
  constexpr auto operator->*(U u) const noexcept {
    // This correctly works.
    // See https://cpprefjp.github.io/lang/cpp20/familiar_template_syntax_for_generic_lambdas.html
    return [u, this](auto&&... args) {
      return (/* implementation */->*u)(std::forward<decltype(args)>(args)...);
    };
  }
  constexpr MyIterator& operator++() noexcept {
    /* implementation */
    return *this;
  }
  constexpr MyIterator& operator--() noexcept {
    /* implementation */
    return *this;
  }
  constexpr MyIterator& operator+=(difference_type n) noexcept {
    /* implementation */
    return *this;
  }
  constexpr MyIterator& operator-=(difference_type n) noexcept {
    /* implementation */
    return *this;
  }
  constexpr reference operator[](difference_type n) const noexcept { return /* implementation */; }
  // friend
  constexpr friend difference_type operator-(const MyIterator& x, const MyIterator& y) noexcept {
    return /* implementation */;
  }
  constexpr friend bool operator==(const MyIterator& x, const MyIterator& y) noexcept {
    return /* implementation */;
  }
  constexpr friend bool operator<(const MyIterator& x, const MyIterator& y) noexcept {
    return /* implementation */;
  }

  // boilerplate
  constexpr MyIterator operator++(int) noexcept(noexcept(++*this)) {
    MyIterator tmp{*this};
    ++*this;
    return tmp;
  }
  constexpr MyIterator operator--(int) noexcept(noexcept(--*this)) {
    MyIterator tmp{*this};
    --*this;
    return tmp;
  }
  constexpr friend MyIterator
  operator+(MyIterator x, typename MyIterator::difference_type n) noexcept(noexcept(x += n)) {
    return x += n;
  }
  constexpr friend MyIterator operator+(typename MyIterator::difference_type n,
                                        MyIterator x) noexcept(noexcept(x += n)) {
    return x += n;
  }
  constexpr friend MyIterator
  operator-(MyIterator x, typename MyIterator::difference_type n) noexcept(noexcept(x -= n)) {
    return x -= n;
  }
  constexpr friend bool operator!=(const MyIterator& x,
                                   const MyIterator& y) noexcept(noexcept(x == y)) {
    return !(x == y);
  }
  constexpr friend bool operator>(const MyIterator& x,
                                  const MyIterator& y) noexcept(noexcept(y < x)) {
    return y < x;
  }
  constexpr friend bool operator<=(const MyIterator& x,
                                   const MyIterator& y) noexcept(noexcept(y < x)) {
    return !(y < x);
  }
  constexpr friend bool operator>=(const MyIterator& x,
                                   const MyIterator& y) noexcept(noexcept(x < y)) {
    return !(x < y);
  }
};
