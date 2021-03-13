/** @file test.hpp */
#include <numeric>
#include <utility>

namespace ns {
  /// @defgroup hoge hogehoge

  /**
   * @defgroup fuga fugafuga
   * @ingroup hoge
   * @{
   */

  /**
   * @brief id
   * @param x ensures: nothing
   * @return expects: nothing
   */
  int id(int x) { return x; }
  /// float
  float id(float x) { return x; }
  /// @cond
  namespace detail {
    int addone(int x) { return x + 1; }
  } // namespace detail
  /// @endcond
  int addtwo(int x) { return detail::addone(detail::addone(x)); }
  /// @}

  using index = int;

  /// @addtogroup fuga
  /// @{
  int minusone(int x) { return x - 1; }
  /// @}
} // namespace ns
