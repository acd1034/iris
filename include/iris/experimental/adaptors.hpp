#pragma once
#include <iris/ranges.hpp>
#include <iris/utility/semiregular_box.hpp>

namespace iris {
  namespace experimental {
    // folded
    template <typename T, typename BinaryOp>
    class folded_tag {
      T t;
      BinaryOp fn;

    public:
      folded_tag(T t, BinaryOp fn) : t(t), fn(fn) {}
      // clang-format off
    template <
      typename It1, typename It2,
      enable_if_t<
        is_iterator_v<It1>
        && is_sentinel_for_v<It2, It1>
        && is_assignable_from_v<T&, detected_t<std::invoke_result_t, BinaryOp, T, iter_value_t<It1>>>> =
        nullptr>
      // clang-format on
      auto operator()(It1 first, It2 last) const {
        T ret = t;
        while (first != last) {
          ret = fn(std::move(ret), *first);
          ++first;
        }
        return ret;
      }
      template <typename R, enable_if_t<is_range_v<R>> = nullptr>
      auto operator()(const R& r) const {
        using std::begin, std::end;
        return operator()(begin(r), end(r));
      }
      template <typename R,
                std::enable_if_t<is_range_v<R> && std::is_rvalue_reference_v<R>,
                                 std::nullptr_t> = nullptr>
      auto operator()(R&& r) const {
        using std::begin, std::end;
        return operator()(std::move_iterator{begin(r)},
                          std::move_iterator{end(r)});
      }
    };
    template <typename T, typename BinaryOp>
    auto folded(T&& t, BinaryOp&& fn) {
      return folded_tag{std::forward<T>(t), std::forward<BinaryOp>(fn)};
    }
    template <typename R, typename T, typename BinaryOp>
    auto operator|(R&& r, const folded_tag<T, BinaryOp>& tag) {
      return tag(std::forward<R>(r));
    }

    template <typename It1,
              typename It2,
              enable_if_t<is_iterator_v<It1> && is_sentinel_for_v<It2, It1>> =
                nullptr>
    struct range : std::pair<It1, It2> {
      using base = std::pair<It1, It2>;
      range(It1 first, It2 second) : base{first, second} {}
      auto begin() { return static_cast<base&>(*this).first; }
      auto end() { return static_cast<base&>(*this).second; }
      auto begin() const { return static_cast<const base&>(*this).first; }
      auto end() const { return static_cast<const base&>(*this).second; }
    };
    struct unreachable_sentinel_t {};
    inline constexpr unreachable_sentinel_t unreachable_sentinel;
    template <typename I, enable_if_t<is_iterator_v<I>> = nullptr>
    bool operator==(const I&, const unreachable_sentinel_t&) {
      return false;
    }
    template <typename I>
    bool operator==(const unreachable_sentinel_t& u, const I& i) {
      return (i == u);
    }
    template <typename I>
    bool operator!=(const I& i, const unreachable_sentinel_t& u) {
      return !(i == u);
    }
    template <typename I>
    bool operator!=(const unreachable_sentinel_t& u, const I& i) {
      return !(i == u);
    }

    // iota
    template <
      typename T,
      typename Fn,
      enable_if_t<
        is_assignable_from_v<T&, detected_t<std::invoke_result_t, Fn, T&&>>> =
        nullptr>
    struct iota_iterator {
      T t;
      semiregular_box<Fn> fn;

      // iota_iterator()                     = delete;
      // iota_iterator(iota_iterator&&)      = default;
      // iota_iterator(const iota_iterator&) = default;
      // iota_iterator& operator=(iota_iterator&&) = default;
      // iota_iterator& operator=(const iota_iterator&) = default;
      iota_iterator(T&& t, Fn&& fn) : t(std::forward<T>(t)), fn(std::forward<Fn>(fn)) {}

      using reference = T;
      reference operator*() const { return t; }
      iota_iterator& operator++() {
        t = (*fn)(std::move(t));
        return *this;
      }
      iota_iterator operator++(int) {
        auto old = *this;
        operator++();
        return old;
      }
    };
    // template <typename T>
    // auto iota(T&& t) {
    //   return range{iota_iterator{std::forward<T>(t), identity{}},
    //                unreachable_sentinel};
    // }
    template <typename T, typename Fn>
    auto iota(T&& t, Fn&& fn) {
      return range{iota_iterator{std::forward<T>(t), std::forward<Fn>(fn)},
                   unreachable_sentinel};
    }

    // counted
    template <typename I1,
              typename I2,
              enable_if_t<is_iterator_v<I1> && is_sentinel_for_v<I2, I1>> =
                nullptr>
    struct counted_iterator : I1 {
    private:
      I2 last;
      std::size_t current = 0;
      std::make_signed_t<decltype(current)> count;

    public:
      // counted_iterator()                        = delete;
      // counted_iterator(counted_iterator&&)      = default;
      // counted_iterator(const counted_iterator&) = default;
      // counted_iterator& operator=(counted_iterator&&) = default;
      // counted_iterator& operator=(const counted_iterator&) = default;
      counted_iterator(I1 first, I2 last, decltype(count) count)
        : I1{first}, last{last}, count{count} {}

      using base      = I1;
      using reference = iter_reference_t<I1>;
      reference operator*() const { return *static_cast<const base&>(*this); }
      counted_iterator& operator++() {
        ++static_cast<base&>(*this);
        ++current;
        return *this;
      }
      counted_iterator operator++(int) {
        auto old = *this;
        operator++();
        return old;
      }
      explicit operator bool() const noexcept {
        return static_cast<const base&>(*this) == last
               || static_cast<decltype(count)>(current) >= count;
      }
      bool operator!() const noexcept { return !static_cast<bool>(*this); }
    };
    struct default_sentinel_t {};
    inline constexpr default_sentinel_t default_sentinel;
    template <typename I1, typename I2>
    bool operator==(const counted_iterator<I1, I2>& i,
                    const default_sentinel_t&) {
      return bool(i);
    }
    template <typename I1, typename I2>
    bool operator==(const default_sentinel_t& d,
                    const counted_iterator<I1, I2>& i) {
      return (i == d);
    }
    template <typename I1, typename I2>
    bool operator!=(const counted_iterator<I1, I2>& i,
                    const default_sentinel_t& d) {
      return !(i == d);
    }
    template <typename I1, typename I2>
    bool operator!=(const default_sentinel_t& d,
                    const counted_iterator<I1, I2>& i) {
      return !(i == d);
    }

    class counted_tag {
      std::make_signed_t<std::size_t> count;

    public:
      counted_tag(decltype(count) count) : count(count) {}
      template <
        typename It1,
        typename It2,
        enable_if_t<is_iterator_v<It1> && is_sentinel_for_v<It2, It1>> = nullptr>
      auto operator()(It1 first, It2 last) const {
        return range{counted_iterator{first, last, count}, default_sentinel};
      }
      template <typename R, enable_if_t<is_range_v<R>> = nullptr>
      auto operator()(const R& r) const {
        using std::begin, std::end;
        return operator()(begin(r), end(r));
      }
      template <typename R,
                std::enable_if_t<is_range_v<R> && std::is_rvalue_reference_v<R>,
                                 std::nullptr_t> = nullptr>
      auto operator()(R&& r) const {
        using std::begin, std::end;
        return operator()(std::move_iterator{begin(r)},
                          std::move_iterator{end(r)});
      }
    };
    auto counted(std::make_signed_t<std::size_t> count) {
      return counted_tag{count};
    }
    template <typename R>
    auto operator|(R&& r, const counted_tag& tag) {
      return tag(std::forward<R>(r));
    }
  } // namespace experimental
} // namespace iris
