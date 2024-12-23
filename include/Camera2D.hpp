// #ifndef RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
// #define RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
#pragma once

#include "./Vector2.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Camera2D 类型，定义一个 2D 相机
 */
class 相机2D : public ::Camera2D {
public:
    相机2D(const ::Camera2D& 相机) : ::Camera2D(相机) {}


    相机2D() : ::Camera2D() {}
    相机2D(::Vector2 偏移量, ::Vector2 目标, float 旋转 = 0.0f, float 变焦 = 1.0f)
        : ::Camera2D{偏移量, 目标, 旋转, 变焦} {}

    /**
     * 开始使用 2D 相机模式
     */
    相机2D& 开始2D模式() {
        ::BeginMode2D(*this);
        return *this;
    }

    /**
     * 结束使用 2D 相机模式
     */
    相机2D& 结束2D模式() {
        ::EndMode2D();
        return *this;
    }

    GETTERSETTER(::Vector2, 偏移量, offset)
    GETTERSETTER(::Vector2, 目标, target)
    GETTERSETTER(float, 旋转, rotation)
    GETTERSETTER(float, 变焦, zoom)

    相机2D& operator=(const ::Camera2D& 相机) {
        设(相机);
        return *this;
    }

    /**
     * 返回 2D 相机的变换矩阵
     */
    [[nodiscard]] Matrix 取矩阵() const { return ::GetCameraMatrix2D(*this); }

    /**
     * 返回 2D 相机屏幕空间位置对应的 2D 世界空间位置
     */
    [[nodiscard]] Vector2 取屏幕到世界(::Vector2 位置) const { return ::GetScreenToWorld2D(位置, *this); }

    /**
     * 返回 2D 世界空间位置对应的 2D 屏幕空间位置
     */
    [[nodiscard]] Vector2 取世界到屏幕(::Vector2 位置) const { return ::GetWorldToScreen2D(位置, *this); }
protected:
    void 设(const ::Camera2D& 相机) {
        offset = 相机.offset;
        target = 相机.target;
        rotation = 相机.rotation;
        zoom = 相机.zoom;
    }
};
} // namespace raylib

using R相机2D = raylib::相机2D;

// #endif // RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_