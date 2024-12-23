// #ifndef RAYLIB_CPP_INCLUDE_MOUSE_HPP_
// #define RAYLIB_CPP_INCLUDE_MOUSE_HPP_
#pragma once

#include "./Functions.hpp"
#include "./Vector2.hpp"
#include "./raylib.hpp"


namespace raylib {
/**
 * 输入相关函数：鼠标
 */
namespace 鼠标 {
/**
 * 检测鼠标按钮是否被按下一次
 */
[[maybe_unused]] RLCPPAPI inline bool 是此按钮被按下(int 按钮) {
    return ::IsMouseButtonPressed(按钮);
}

/**
 * 检测鼠标按钮是否正在被按下
 */
[[maybe_unused]] RLCPPAPI inline bool 是此按钮为按下(int 按钮) {
    return ::IsMouseButtonDown(按钮);
}

/**
 * 检测鼠标按钮是否被释放一次
 */
[[maybe_unused]] RLCPPAPI inline bool 是此按钮被释放(int 按钮) {
    return ::IsMouseButtonReleased(按钮);
}

[[maybe_unused]] RLCPPAPI inline bool 是此按钮没被按下(int 按钮) {
    return ::IsMouseButtonUp(按钮);
}

[[maybe_unused]] RLCPPAPI inline int 取X() {
    return ::GetMouseX();
}

[[maybe_unused]] RLCPPAPI inline int 取Y() {
    return ::GetMouseY();
}

[[maybe_unused]] RLCPPAPI inline void 设X(int x) {
    ::SetMousePosition(x, 取Y());
}

[[maybe_unused]] RLCPPAPI inline void 设Y(int y) {
    ::SetMousePosition(取X(), y);
}

[[maybe_unused]] RLCPPAPI inline Vector2 取位置() {
    return ::GetMousePosition();
}

[[maybe_unused]] RLCPPAPI inline void 设位置(int x, int y) {
    ::SetMousePosition(x, y);
}

[[maybe_unused]] RLCPPAPI inline void 设位置(::Vector2 位置) {
    ::SetMousePosition(static_cast<int>(位置.x), static_cast<int>(位置.y));
}

/**
 * 获取鼠标在帧之间的增量,取鼠标移动差值
 */
[[maybe_unused]] RLCPPAPI inline Vector2 取相差值() {
    return ::GetMouseDelta();
}

/// 设置鼠标偏移量
[[maybe_unused]] RLCPPAPI inline void 设偏移量(int 偏移X = 0, int 偏移Y = 0) {
    ::SetMouseOffset(偏移X, 偏移Y);
}

[[maybe_unused]] RLCPPAPI inline void 设偏移量(::Vector2 偏移量) {
    ::SetMouseOffset(static_cast<int>(偏移量.x), static_cast<int>(偏移量.y));
}

[[maybe_unused]] RLCPPAPI inline void 设缩放(float 缩放X = 1.0f, float 缩放Y = 1.0f) {
    ::SetMouseScale(缩放X, 缩放Y);
}

[[maybe_unused]] RLCPPAPI inline void 设缩放(::Vector2 缩放) {
    ::SetMouseScale(缩放.x, 缩放.y);
}

/**
 * 获取鼠标滚轮在X或Y方向上的移动量（取较大值）
 */
[[maybe_unused]] RLCPPAPI inline float 取滚轮移动值() {
    return ::GetMouseWheelMove();
}

/**
 * 获取鼠标滚轮在X和Y方向上的移动量
 *
 * @see ::GetMouseWheelMoveV()
 */
[[maybe_unused]] RLCPPAPI inline Vector2 取滚轮移动向量() {
    return GetMouseWheelMoveV();
}

/**
 * 设置当前鼠标光标图标
 *
 * @see ::MouseCursor
 */
[[maybe_unused]] RLCPPAPI inline void 设光标(int 光标 = MOUSE_CURSOR_DEFAULT) {
    ::SetMouseCursor(光标);
}

/**
 * 获取触摸点0的X坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int 取触摸点X() {
    return ::GetTouchX();
}

/**
 * 获取触摸点0的Y坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int 取触摸点Y() {
    return ::GetTouchY();
}

/**
 * 获取触摸点索引的XY坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline Vector2 取触摸点坐标(int 索引) {
    return ::GetTouchPosition(索引);
}

/**
 * 从鼠标位置获取光线追踪
 */
[[maybe_unused]] RLCPPAPI inline Ray 取射线(::Vector2 鼠标位置, const ::Camera& 相机) {
    return ::GetMouseRay(鼠标位置, 相机);
}

/**
 * 从鼠标位置获取光线追踪
 */
[[maybe_unused]] RLCPPAPI inline Ray 取射线(const ::Camera& 相机) {
    return ::GetMouseRay(::GetMousePosition(), 相机);
}
} // namespace 鼠标
} // namespace raylib

namespace R鼠标 = raylib::鼠标;

// #endif // RAYLIB_CPP_INCLUDE_MOUSE_HPP_