// #ifndef RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
// #define RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
#pragma once

#include "./Functions.hpp"
#include "./raylib.hpp"

/**
 * 允许更改 raylib-cpp 全局函数的声明类型。默认为静态（static）。
 */
#ifndef RLCPPAPI
#define RLCPPAPI static
#endif

namespace raylib {
/**
 * 输入相关函数：键盘
 */
namespace 键盘 {
/**
 * 检测某个键是否被按下一次
 */
[[maybe_unused]] RLCPPAPI inline bool 是此键被按下(int 按键) {
    return ::IsKeyPressed(按键);
}

/**
 * 检测某个键是否被再次按下（仅限 PLATFORM_DESKTOP）
 */
[[maybe_unused]] RLCPPAPI inline bool 是此键被再次按下(int 按键) {
    return ::IsKeyPressedRepeat(按键);
}

/**
 * 检测某个键是否正在被按下
 */
[[maybe_unused]] RLCPPAPI inline bool 是此键为按下(int key) {
    return ::IsKeyDown(key);
}

/**
 * 检测某个键是否被释放一次
 */
[[maybe_unused]] RLCPPAPI inline bool 是此键被释放(int key) {
    return ::IsKeyReleased(key);
}

/**
 * 检测某个键是否没有被按下
 */
[[maybe_unused]] RLCPPAPI inline bool 是此键没被按下(int key) {
    return ::IsKeyUp(key);
}

/**
 * 获取按下的键（键码），多次调用以获取队列中的键，队列为空时返回 0
 */

[[maybe_unused]] RLCPPAPI inline int 取被按下的键() {
    return ::GetKeyPressed();
}

/**
 * 获取按下的字符（Unicode），多次调用以获取队列中的字符，队列为空时返回 0
 */
[[maybe_unused]] RLCPPAPI inline int 取被按下的字符() {
    return ::GetCharPressed();
}
} // namespace 键盘
} // namespace raylib

namespace R键盘 = raylib::键盘;

// #endif // RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_