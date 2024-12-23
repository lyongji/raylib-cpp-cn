// #ifndef RAYLIB_CPP_INCLUDE_TOUCH_HPP_
// #define RAYLIB_CPP_INCLUDE_TOUCH_HPP_
#pragma once

#include "./Functions.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 输入相关函数：触摸
 */
namespace 触摸 {
/**
 * 获取触摸点 0 的触摸位置 X（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int 取X() {
    return ::GetTouchX();
}

/**
 * 获取触摸点 0 的触摸位置 Y（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int 取Y() {
    return ::GetTouchY();
}

/**
 * 获取触摸点索引的触摸位置 XY（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline Vector2 取位置(int 索引) {
    return ::GetTouchPosition(索引);
}

/**
 * 获取给定索引的触摸点标识符
 */
[[maybe_unused]] RLCPPAPI inline int 取点ID(int 索引) {
    return ::GetTouchPointId(索引);
}

/**
 * 获取触摸点数量
 */
[[maybe_unused]] RLCPPAPI inline int 取点数量() {
    return ::GetTouchPointCount();
}
} // namespace 触摸
} // namespace raylib

namespace R触摸 = raylib::触摸;

// #endif // RAYLIB_CPP_INCLUDE_TOUCH_HPP_