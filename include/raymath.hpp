/**
 * 用于封装 raymath.h 的 C++ 头文件。
 */
// #ifndef RAYLIB_CPP_INCLUDE_RAYMATH_HPP_
// #define RAYLIB_CPP_INCLUDE_RAYMATH_HPP_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#ifndef RAYLIB_CPP_NO_MATH
#ifndef RAYMATH_STATIC_INLINE
#define RAYMATH_STATIC_INLINE
#endif
#ifdef __GNUC__
#pragma GCC diagnostic push // 这些在 Visual Studio 上会引发警告，需要检查是否定义了 __GNUC__ 以使用它。
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#define RAYMATH_DISABLE_CPP_OPERATORS
#include "raymath.h" // NOLINT
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#endif
#ifdef __cplusplus
}
#endif

// #endif // RAYLIB_CPP_INCLUDE_RAYMATH_HPP_
