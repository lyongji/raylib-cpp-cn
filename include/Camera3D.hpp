// #ifndef RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
// #define RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
#pragma once

#include "./Vector3.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 相机类型，定义 3D 空间中的相机位置/方向
 */
class Camera3D : public ::Camera3D {
public:
    Camera3D(const ::Camera3D& camera) : ::Camera3D(camera) { }

    /**
     * 创建一个新的 Camera3D。
     *
     * @param position 相机位置
     * @param target 相机目标点（相机朝向）
     * @param up 相机上向量（绕其轴旋转）
     * @param fovy 相机视野在 Y 轴上的角度（透视模式下），正交模式下用作近裁剪面的宽度
     * @param projection 相机投影模式：CAMERA_PERSPECTIVE 或 CAMERA_ORTHOGRAPHIC
     */
    Camera3D(
        ::Vector3 position,
        ::Vector3 target = ::Vector3{0.0f, 0.0f, 0.0f},
        ::Vector3 up = ::Vector3{0.0f, 1.0f, 0.0f},
        float fovy = 0,
        int projection = CAMERA_PERSPECTIVE)
        : ::Camera3D{position, target, up, fovy, projection} {}

    Camera3D() {}

    GETTERSETTER(::Vector3, Position, position)
    GETTERSETTER(::Vector3, Target, target)
    GETTERSETTER(::Vector3, Up, up)
    GETTERSETTER(float, Fovy, fovy)
    GETTERSETTER(int, Projection, projection)

    Camera3D& operator=(const ::Camera3D& camera) {
        set(camera);
        return *this;
    }

    /**
     * 使用自定义相机初始化 3D 模式
     */
    Camera3D& BeginMode() {
        ::BeginMode3D(*this);
        return *this;
    }

    /**
     * 结束 3D 模式并返回默认的 2D 正交模式
     */
    Camera3D& EndMode() {
        ::EndMode3D();
        return *this;
    }

    /**
     * 获取相机的变换矩阵（视图矩阵）
     */
    Matrix GetMatrix() const { return ::GetCameraMatrix(*this); }

    /**
     * 更新相机位置（根据选择的模式）
     */
    Camera3D& Update(int mode) {
        ::UpdateCamera(this, mode);
        return *this;
    }

    /**
     * 更新相机的移动/旋转
     */
    Camera3D& Update(::Vector3 movement, ::Vector3 rotation, float zoom = 1.0f) {
        ::UpdateCameraPro(this, movement, rotation, zoom);
        return *this;
    }

    /**
     * 从鼠标位置返回一条射线
     */
    Ray GetMouseRay(::Vector2 mousePosition) const { return ::GetMouseRay(mousePosition, *this); }

    /**
     * 返回 3D 世界空间位置对应的屏幕空间位置
     */
    Vector2 GetWorldToScreen(::Vector3 position) const { return ::GetWorldToScreen(position, *this); }

    /**
     * 从屏幕位置（例如鼠标）在视口中的射线
     */
    Ray GetScreenToWorldRay(::Vector2 position, int width, int height) {
        return ::GetScreenToWorldRayEx(position, *this, width, height);
    }

    /**
     * 绘制一个公告板纹理
     */
    void
    DrawBillboard(const ::Texture2D& texture, ::Vector3 center, float size, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboard(*this, texture, center, size, tint);
    }

    /**
     * 绘制一个由源矩形定义的公告板纹理
     */
    void DrawBillboard(
        const ::Texture2D& texture,
        ::Rectangle sourceRec,
        ::Vector3 center,
        ::Vector2 size,
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboardRec(*this, texture, sourceRec, center, size, tint);
    }
protected:
    void set(const ::Camera3D& camera) {
        position = camera.position;
        target = camera.target;
        up = camera.up;
        fovy = camera.fovy;
        projection = camera.projection;
    }
};

using Camera = Camera3D;

} // namespace raylib

using RCamera = raylib::Camera;
using RCamera3D = raylib::Camera3D;

// #endif // RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_