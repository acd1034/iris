# Light Concept Library for C++17
supported metafunctions:

## `<concepts>`
https://en.cppreference.com/w/cpp/concepts
### 型の関係
|name|at|
|:--|:--|
|`same_as`|`iris`|
|`convertible_to`|`std::is_convertible`|
|`derived_from`|`iris`|
|`common_reference_with`|``|
|`common_with`|``|

### 型の種類
|name|at|
|:--|:--|
|`integral`|`std::is_integral`|
|`signed_integral`|`iris`|
|`unsigned_integral`|`iris`|
|`boolean`|``|
|`floating_point`|`std::is_floating_point`|

### 型の構築・破棄・代入操作
|name|at|
|:--|:--|
|`destructible`|`iris`|
|`constructible_from`|`iris`|
|`default_constructible`|`iris`|
|`move_constructible`|`iris`|
|`copy_constructible`|`iris`|
|`assignable_from`|`iris`|
|`swappable`|`iris`|
|`swappable_with`|`iris`|

### 比較
|name|at|
|:--|:--|
|`equality_comparable`|``|
|`equality_comparable_with`|``|
|`totally_ordered`|``|
|`totally_ordered_with`|``|

### 値指向の操作
|name|at|
|:--|:--|
|`movable`|`iris`|
|`copyable`|`iris`|
|`semiregular`|`iris`|
|`regular`|`iris`|

### 関数呼び出し
|name|at|
|:--|:--|
|`invocable`|`std::is_invocable`|
|`regular_invocable`|`説明専用(invocableと同じ)`|
|`predicate`|`iris`|
|`relation`|`iris`|
|`strict_weak_order`|`説明専用(relationと同じ)`|

## `<iterator>`
https://ja.cppreference.com/w/cpp/iterator

|name|at|
|:--|:--|
|`readable`|``|
|`writable`|``|
|`weakly_incrementable`|``|
|`incrementable`|``|
|`input_or_output_iterator`|``|
|`sentinel_for`|`WIP`|
|`sized_sentinel_for`|``|
|`input_iterator`|`WIP`|
|`output_iterator`|`WIP`|
|`forward_iterator`|`WIP`|
|`bidirectional_iterator`|`WIP`|
|`random_access_iterator`|`WIP`|
|`contiguous_iterator`|``|

## `<ranges>`
https://en.cppreference.com/w/cpp/header/ranges

|name|at|
|:--|:--|
|`range`|`iris`|
|`sized_range`|``|
|`view`|``|
|`input_range`|`iris`|
|`output_range`|`iris`|
|`forward_range`|`iris`|
|`bidirectional_range`|`iris`|
|`random_access_range`|`iris`|
|`contiguous_range`|``|
|`common_range`|``|
|`viewable_range`|``|

## `<utility>`
|name|at|
|:--|:--|
|`tuple_like`|`iris`|
