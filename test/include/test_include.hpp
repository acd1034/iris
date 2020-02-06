#pragma once
// container
#include <array>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
// associative container
#include <map>
#include <set>
// tuple
#include <tuple>
// safe container
#include <any>
#include <optional>
#include <variant>
// others
#include <chrono>
#include <functional>

namespace mini {
  template <typename T>
  using strange_t1 = std::tuple<std::in_place_t, std::vector<T>, std::set<T>, std::map<std::string, T>, std::any, std::optional<T>, std::chrono::system_clock::time_point>;
  template <typename T>
  using strange_t2 = std::function<T(std::variant<std::in_place_t, std::vector<T>, std::set<T>, std::map<std::string, T>, std::any, std::optional<T>, std::chrono::system_clock::time_point>)>;
  using strange_t  = std::pair<strange_t1<strange_t1<int>>, strange_t2<int>>;

  struct iter {
    using value_type = int;
    iter()           = default;
    int operator*() const { return 0; }
    iter& operator++() { return *this; }
    iter operator++(int) {
      auto result = *this;
      return result;
    }
  };
  struct sentinel {
    using value_type = int;
    sentinel()       = default;
    int operator*() const { return 0; }
    sentinel& operator++() { return *this; }
    sentinel operator++(int) {
      auto result = *this;
      return result;
    }
  };
  bool operator==(const iter&, const sentinel&) { return true; }
  bool operator==(const sentinel&, const iter&) { return true; }
  bool operator!=(const iter&, const sentinel&) { return false; }
  bool operator!=(const sentinel&, const iter&) { return false; }
  template <typename T>
  struct range {
    range() = default;
    T begin() { return T{}; }
    T end() { return T{}; }
  };
} // namespace mini
