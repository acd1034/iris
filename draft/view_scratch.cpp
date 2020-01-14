#include <bits/stdc++.h>
// #include <range/v3/all.hpp>

template <typename t>
using iterator_t = decltype(std::begin(std::declval<t&>()));

template <typename t>
using range_reference_t = decltype(*std::begin(std::declval<t&>()));

template <typename urng_t>
//     requires (bool)ranges::InputRange<urng_t>() &&
//              (bool)ranges::CommonReference<range_reference_t<urng_t>, uint64_t>()
class view_add_constant
// : public ranges::view_base
{
private:
  /* data members == "the state" */
  struct data_members_t {
    urng_t urange;
  };
  std::shared_ptr<data_members_t> data_members;

  /* the iterator type */
  struct iterator_type : iterator_t<urng_t> {
    using base      = iterator_t<urng_t>;
    using reference = uint64_t;

    iterator_type() = default;
    iterator_type(base const& b) : base{b} {}

    iterator_type operator++(int) { return static_cast<base&>(*this)++; }
    iterator_type& operator++() {
      ++static_cast<base&>(*this);
      return (*this);
    }

    reference operator*() const { return *static_cast<base>(*this) + 42; }
  };

public:
  /* member type definitions */
  using reference       = uint64_t;
  using const_reference = uint64_t;
  using value_type      = uint64_t;
  using iterator        = iterator_type;
  using const_iterator  = iterator_type;

  /* constructors and deconstructors */
  view_add_constant()                                       = default;
  constexpr view_add_constant(view_add_constant const& rhs) = default;
  constexpr view_add_constant(view_add_constant&& rhs)      = default;
  constexpr view_add_constant&
  operator=(view_add_constant const& rhs) = default;
  constexpr view_add_constant& operator=(view_add_constant&& rhs) = default;
  ~view_add_constant()                                            = default;
  view_add_constant(urng_t&& urange)
    : data_members{new data_members_t{std::forward<urng_t>(urange)}} {}

  /* begin and end */
  iterator begin() const { return std::begin(data_members->urange); }
  const_iterator cbegin() const { return begin(); }
  iterator end() const { return std::end(data_members->urange); }
  const_iterator cend() const { return end(); }
};

template <typename urng_t>
//     requires (bool)ranges::InputRange<urng_t>() &&
//              (bool)ranges::CommonReference<range_reference_t<urng_t>, uint64_t>()
view_add_constant(urng_t &&)->view_add_constant<urng_t>;

// static_assert((bool)ranges::InputRange<view_add_constant<std::vector<uint64_t>>>());
// static_assert((bool)ranges::View<view_add_constant<std::vector<uint64_t>>>());

struct add_constant_fn {
  template <typename urng_t>
  //         requires (bool)ranges::InputRange<urng_t>() &&
  //                  (bool)ranges::CommonReference<range_reference_t<urng_t>, uint64_t>()
  auto operator()(urng_t&& urange) const {
    return view_add_constant{std::forward<urng_t>(urange)};
  }

  template <typename urng_t>
  //         requires (bool)ranges::InputRange<urng_t>() &&
  //                  (bool)ranges::CommonReference<range_reference_t<urng_t>, uint64_t>()
  friend auto operator|(urng_t&& urange, add_constant_fn const&) {
    return view_add_constant{std::forward<urng_t>(urange)};
  }
};

namespace view {
  add_constant_fn constexpr add_constant;
}

int main() {
  std::vector<uint64_t> in{1, 4, 6, 89, 56, 45, 7};
  for (auto&& i : in | view::add_constant) std::cout << i << ' ';
  std::cout << '\n'; // should print: 43 47 64 131 98 87 49
}
