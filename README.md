# Lite Concept Library for C++17
## Documentation
Click [here](https://acd1034.github.io/iris/html/index.html).

## Noteworthy Features:

1. metafunctions supporting C++20 `<concepts>`, `<iterator>` and `<ranges>`
1. `iris::semiregular_box` to make lambdas or other non-semiregular classes semiregular
1. original concept `tuple-like`
1. stream insertion (`operator<<`) supporting `range` and `tuple-like`
1. some testing utilities

## Supported Compilers
The author's environment is:

- Apple clang version 11.0.0 (clang-1100.0.33.8)

The code does not work on GCC (mainly because of `<iris/concepts>`).
