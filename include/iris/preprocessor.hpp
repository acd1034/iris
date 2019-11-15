#pragma once
#define IRIS_TO_STR_IMPL(x) #x
#define IRIS_TO_STR(x) IRIS_TO_STR_IMPL(x)
#define IRIS_CONCAT_IMPL(x, y) x##y
#define IRIS_CONCAT(x, y) IRIS_CONCAT_IMPL(x, y)
