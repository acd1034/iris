https://en.cppreference.com/w/cpp/concepts
https://cpprefjp.github.io/reference/concepts.html
# 型の関係
same_as	2つの型が同じ	C++20
derived_from	継承関係にある	C++20
convertible_to	変換可能	C++20
common_reference_with	共通の参照型	C++20
common_with	共通の型	C++20

# 型の種類
integral	整数型	C++20
signed_integral	符号付き整数型	C++20
unsigned_integral	符号なし整数型	C++20
boolean	真理値型	C++20
floating_point	浮動小数点数型	C++20

# 型の構築・破棄・代入操作
constructible_from	構築可能	C++20
default_constructible	デフォルト構築可能	C++20
copy_constructible	コピー構築可能	C++20
move_constructible	ムーブ構築可能	C++20
destructible	破棄可能	C++20
assignable_from	代入可能	C++20
swappable	入れ替え可能	C++20
swappable_with	特定の型と入れ替え可能	C++20

# 比較
equality_comparable	等値比較可能	C++20
equality_comparable_with	特定の型と等値比較可能	C++20
totally_ordered	狭義の全順序	C++20
totally_ordered_with	特定の型と狭義の全順序	C++20

# 値指向の操作
movable	ムーブ可能	C++20
copyable	コピー可能	C++20
semiregular	半正則	C++20
regular	正則	C++20

# 関数呼び出し
invocable	INVOKEコンセプトに従った関数呼び出しが可能	C++20
regular_invocable	正則呼び出し可能	C++20
predicate	述語	C++20
relation	述語関係	C++20
strict_weak_order	狭義の弱順序	C++20
