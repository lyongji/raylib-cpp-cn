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
class 相机3D : public ::Camera3D {
public:
    相机3D(const ::Camera3D& 相机) { 设(相机); }

    /**
     * 创建一个新的 相机3D。
     *
     * @param position 相机位置
     * @param target 相机目标点（相机朝向）
     * @param up 相机上向量（绕其轴旋转）
     * @param fovy 相机视野在 Y 轴上的角度（透视模式下），正交模式下用作近裁剪面的宽度Fovy 是 "Field of View in the
     * Y-axis" 的缩写，表示相机在垂直方向上的视野角度。
     * @param projection 相机投影模式：CAMERA_PERSPECTIVE 或 CAMERA_ORTHOGRAPHIC
     */
    相机3D(
        ::Vector3 位置,
        ::Vector3 目标点 = ::Vector3{0.0f, 0.0f, 0.0f},
        ::Vector3 上向量 = ::Vector3{0.0f, 1.0f, 0.0f},
        float 视场角 = 0,
        int 投影模式 = CAMERA_PERSPECTIVE)
        : ::Camera3D{位置, 目标点, 上向量, 视场角, 投影模式} {}

    相机3D() {}

    GETTERSETTER(::Vector3, 位置, position)
    GETTERSETTER(::Vector3, 目标点, target)
    GETTERSETTER(::Vector3, 上向量, up)
    GETTERSETTER(float, 视场角, fovy)
    GETTERSETTER(int, 投影模式, projection)

    相机3D& operator=(const ::Camera3D& 相机) {
        设(相机);
        return *this;
    }

    /**
     * 使用自定义相机初始化 3D 模式
     */
    相机3D& 开始3D模式() {
        ::BeginMode3D(*this);
        return *this;
    }

    /**
     * 结束 3D 模式并返回默认的 2D 正交模式
     */
    相机3D& 结束3D模式() {
        ::EndMode3D();
        return *this;
    }

    /**
     * 获取相机的变换矩阵（视图矩阵）
     */
    Matrix 取矩阵() const { return ::GetCameraMatrix(*this); }

    /**
     * 更新相机位置（根据选择的模式）
     */
    相机3D& 更新(int 模式) {
        ::UpdateCamera(this, 模式);
        return *this;
    }

    /**
     * 更新相机的移动/旋转
     */
    相机3D& 更新(::Vector3 移动, ::Vector3 旋转, float 变焦 = 1.0f) {
        ::UpdateCameraPro(this, 移动, 旋转, 变焦);
        return *this;
    }

    /**
     * 从鼠标位置返回一条射线
     */
    Ray 取鼠标射线(::Vector2 鼠标位置) const { return ::GetMouseRay(鼠标位置, *this); }

    /**
     * 返回 3D 世界空间位置对应的屏幕空间位置
     */
    Vector2 取世界到屏幕(::Vector3 位置) const { return ::GetWorldToScreen(位置, *this); }

    /**
     * 从屏幕位置（例如鼠标）在视口中的射线
     */
    Ray 取屏幕到世界的射线(::Vector2 位置, int 宽, int 高) { return ::GetScreenToWorldRayEx(位置, *this, 宽, 高); }

    /**
     * 绘制一个公告板纹理
     */
    void 绘制公告板(const ::Texture2D& 纹理, ::Vector3 中心, float 缩放, ::Color 色彩 = {255, 255, 255, 255}) const {
        ::DrawBillboard(*this, 纹理, 中心, 缩放, 色彩);
    }

    /**
     * 绘制一个由源矩形定义的公告板纹理
     */
    void 绘制公告板(
        const ::Texture2D& 纹理,
        ::Rectangle 源矩形,
        ::Vector3 中心,
        ::Vector2 尺寸,
        ::Color 色彩 = {255, 255, 255, 255}) const {
        ::DrawBillboardRec(*this, 纹理, 源矩形, 中心, 尺寸, 色彩);
    }
protected:
    void 设(const ::Camera3D& 相机) {
        position = 相机.position;
        target = 相机.target;
        up = 相机.up;
        fovy = 相机.fovy;
        projection = 相机.projection;
    }
};

using 相机 = 相机3D;

} // namespace raylib

using R相机 = raylib::相机;
using R相机3D = raylib::相机3D;

// #endif // RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_