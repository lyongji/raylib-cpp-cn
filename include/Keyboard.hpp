// #ifndef RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
// #define RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_
#pragma once

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
namespace Keyboard {
/**
 * 检测某个键是否被按下一次
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyPressed(int key) {
    return ::IsKeyPressed(key);
}

/**
 * 检测某个键是否被再次按下（仅限 PLATFORM_DESKTOP）
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyPressedRepeat(int key) {
    return ::IsKeyPressedRepeat(key);
}

/**
 * 检测某个键是否正在被按下
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyDown(int key) {
    return ::IsKeyDown(key);
}

/**
 * 检测某个键是否被释放一次
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyReleased(int key) {
    return ::IsKeyReleased(key);
}

/**
 * 检测某个键是否没有被按下
 */
[[maybe_unused]] RLCPPAPI inline bool IsKeyUp(int key) {
    return ::IsKeyUp(key);
}

/**
 * 获取按下的键（键码），多次调用以获取队列中的键，队列为空时返回 0
 */

[[maybe_unused]] RLCPPAPI inline int GetKeyPressed() {
    return ::GetKeyPressed();
}

/**
 * 获取按下的字符（Unicode），多次调用以获取队列中的字符，队列为空时返回 0
 */
[[maybe_unused]] RLCPPAPI inline int GetCharPressed() {
    return ::GetCharPressed();
}
} // namespace Keyboard
} // namespace raylib
namespace RKeyboard = raylib::Keyboard;

// #endif // RAYLIB_CPP_INCLUDE_KEYBOARD_HPP_