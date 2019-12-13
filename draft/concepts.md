# Generic Concepts
進捗：`iris`なし以外

https://en.cppreference.com/w/cpp/concepts
https://cpprefjp.github.io/reference/concepts.html

## 型の関係
|name|at|
|:--|:--|
|`same_as`|`iris`|
|`convertible_to`|`iris`|
|`derived_from`|`iris`|
|`common_reference_with`|``|
|`common_with`|``|

## 型の種類
|name|at|
|:--|:--|
|`integral`|`std::is_integral`|
|`signed_integral`|`iris`|
|`unsigned_integral`|`iris`|
|`boolean`|``|
|`floating_point`|`std::is_floating_point`|

## 型の構築・破棄・代入操作
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

## 比較
|name|at|
|:--|:--|
|`equality_comparable`|``|
|`equality_comparable_with`|``|
|`totally_ordered	狭義`|``|
|`totally_ordered_with`|``|

## 値指向の操作
|name|at|
|:--|:--|
|`movable`|`iris`|
|`copyable`|`iris`|
|`semiregular`|`iris`|
|`regular`|`iris`|

# 関数呼び出し
|name|at|
|:--|:--|
|`invocable`|`std::is_invocable`|
|`regular_invocable`|`説明専用(invocableと同じ)`|
|`predicate`|`iris`|
|`relation`|`iris`|
|`strict_weak_order`|`説明専用(relationと同じ)`|
