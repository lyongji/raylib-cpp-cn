// #ifndef RAYLIB_CPP_INCLUDE_TOUCH_HPP_
// #define RAYLIB_CPP_INCLUDE_TOUCH_HPP_
#pragma once

#include "./raylib.hpp"

namespace raylib {
/**
 * 输入相关函数：触摸
 */
namespace Touch {
/**
 * 获取触摸点 0 的触摸位置 X（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int GetX() {
    return ::GetTouchX();
}

/**
 * 获取触摸点 0 的触摸位置 Y（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int GetY() {
    return ::GetTouchY();
}

/**
 * 获取触摸点索引的触摸位置 XY（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetPosition(int index) {
    return ::GetTouchPosition(index);
}

/**
 * 获取给定索引的触摸点标识符
 */
[[maybe_unused]] RLCPPAPI inline int GetPointId(int index) {
    return ::GetTouchPointId(index);
}

/**
 * 获取触摸点数量
 */
[[maybe_unused]] RLCPPAPI inline int GetPointCount() {
    return ::GetTouchPointCount();
}
} // namespace Touch
} // namespace raylib

namespace RTouch = raylib::Touch;

// #endif // RAYLIB_CPP_INCLUDE_TOUCH_HPP_