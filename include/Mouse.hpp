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
namespace Mouse {
/**
 * 检测鼠标按钮是否被按下一次
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

/**
 * 检测鼠标按钮是否正在被按下
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

/**
 * 检测鼠标按钮是否被释放一次
 */
[[maybe_unused]] RLCPPAPI inline bool IsButtonReleased(int button) {
    return ::IsMouseButtonReleased(button);
}

[[maybe_unused]] RLCPPAPI inline bool IsButtonUp(int button) {
    return ::IsMouseButtonUp(button);
}

[[maybe_unused]] RLCPPAPI inline int GetX() {
    return ::GetMouseX();
}

[[maybe_unused]] RLCPPAPI inline int GetY() {
    return ::GetMouseY();
}

[[maybe_unused]] RLCPPAPI inline void SetX(int x) {
    ::SetMousePosition(x, GetY());
}

[[maybe_unused]] RLCPPAPI inline void SetY(int y) {
    ::SetMousePosition(GetX(), y);
}

[[maybe_unused]] RLCPPAPI inline Vector2 GetPosition() {
    return ::GetMousePosition();
}

[[maybe_unused]] RLCPPAPI inline void SetPosition(int x, int y) {
    ::SetMousePosition(x, y);
}

[[maybe_unused]] RLCPPAPI inline void SetPosition(::Vector2 position) {
    ::SetMousePosition(static_cast<int>(position.x), static_cast<int>(position.y));
}

/**
 * 获取鼠标在帧之间的增量
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetDelta() {
    return ::GetMouseDelta();
}

[[maybe_unused]] RLCPPAPI inline void SetOffset(int offsetX = 0, int offsetY = 0) {
    ::SetMouseOffset(offsetX, offsetY);
}

[[maybe_unused]] RLCPPAPI inline void SetOffset(::Vector2 offset) {
    ::SetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
}

[[maybe_unused]] RLCPPAPI inline void SetScale(float scaleX = 1.0f, float scaleY = 1.0f) {
    ::SetMouseScale(scaleX, scaleY);
}

[[maybe_unused]] RLCPPAPI inline void SetScale(::Vector2 scale) {
    ::SetMouseScale(scale.x, scale.y);
}

/**
 * 获取鼠标滚轮在X或Y方向上的移动量（取较大值）
 */
[[maybe_unused]] RLCPPAPI inline float GetWheelMove() {
    return ::GetMouseWheelMove();
}

/**
 * 获取鼠标滚轮在X和Y方向上的移动量
 *
 * @see ::GetMouseWheelMoveV()
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetWheelMoveV() {
    return GetMouseWheelMoveV();
}

/**
 * 设置当前鼠标光标图标
 *
 * @see ::MouseCursor
 */
[[maybe_unused]] RLCPPAPI inline void SetCursor(int cursor = MOUSE_CURSOR_DEFAULT) {
    ::SetMouseCursor(cursor);
}

/**
 * 获取触摸点0的X坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int GetTouchX() {
    return ::GetTouchX();
}

/**
 * 获取触摸点0的Y坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline int GetTouchY() {
    return ::GetTouchY();
}

/**
 * 获取触摸点索引的XY坐标（相对于屏幕大小）
 */
[[maybe_unused]] RLCPPAPI inline Vector2 GetTouchPosition(int index) {
    return ::GetTouchPosition(index);
}

/**
 * 从鼠标位置获取光线追踪
 */
[[maybe_unused]] RLCPPAPI inline Ray GetRay(::Vector2 mousePosition, const ::Camera& camera) {
    return ::GetMouseRay(mousePosition, camera);
}

/**
 * 从鼠标位置获取光线追踪
 */
[[maybe_unused]] RLCPPAPI inline Ray GetRay(const ::Camera& camera) {
    return ::GetMouseRay(::GetMousePosition(), camera);
}
} // namespace Mouse
} // namespace raylib

namespace RMouse = raylib::Mouse;

// #endif // RAYLIB_CPP_INCLUDE_MOUSE_HPP_