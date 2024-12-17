// #ifndef RAYLIB_CPP_INCLUDE_RAY_HPP_
// #define RAYLIB_CPP_INCLUDE_RAY_HPP_
#pragma once

#include "./RayCollision.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 射线类型（用于光线投射）
 */
class 射线 : public ::Ray {
public:
    射线(const ::Ray& 射线) { 设(射线); }

    射线(::Vector3 位置 = {0.0f, 0.0f, 0.0f}, ::Vector3 指向 = {0.0f, 0.0f, 0.0f}) : ::Ray{位置, 指向} {
        // 无操作
    }

    射线(::Vector2 鼠标位置, const ::Camera& 相机) { 设(::GetMouseRay(鼠标位置, 相机)); }

    射线& operator=(const ::Ray& 射线) {
        设(射线);
        return *this;
    }

    GETTERSETTER(::Vector3, 位置, position)
    GETTERSETTER(::Vector3, 指向, direction)

    /**
     * 绘制射线
     */
    void Draw(::Color 颜色) const { DrawRay(*this, 颜色); }

    /**
     * 获取射线与球体的碰撞信息
     */
    射线碰撞 取碰撞(::Vector3 中心, float 半径) const { return ::GetRayCollisionSphere(*this, 中心, 半径); }

    /**
     * 检测射线与包围盒的碰撞
     */
    射线碰撞 取碰撞(const ::BoundingBox& 盒子) const { return ::GetRayCollisionBox(*this, 盒子); }

    /**
     * 获取射线与网格的碰撞信息
     */
    射线碰撞 取碰撞(const ::Mesh& 网格, const ::Matrix& 变换) const { return ::GetRayCollisionMesh(*this, 网格, 变换); }

    /**
     * 获取射线与三角形的碰撞信息
     */
    射线碰撞 取碰撞(::Vector3 顶点1, ::Vector3 顶点2, ::Vector3 顶点3) const {
        return ::GetRayCollisionTriangle(*this, 顶点1, 顶点2, 顶点3);
    }

    /**
     * 获取射线与四边形的碰撞信息
     */
    射线碰撞 取碰撞(::Vector3 顶点1, ::Vector3 顶点2, ::Vector3 顶点3, ::Vector3 顶点4) const {
        return ::GetRayCollisionQuad(*this, 顶点1, 顶点2, 顶点3, 顶点4);
    }

    /**
     * 从鼠标位置获取射线
     */
    static 射线 取鼠标射线(::Vector2 鼠标位置, const ::Camera& 相机) { return ::GetMouseRay(鼠标位置, 相机); }

    /**
     * 从鼠标位置获取射线
     */
    static 射线 取鼠标射线(const ::Camera& 相机) { return ::GetMouseRay(::GetMousePosition(), 相机); }
protected:
    void 设(const ::Ray& 射线) {
        position = 射线.position;
        direction = 射线.direction;
    }
};
} // namespace raylib

using R射线 = raylib::射线;

// #endif // RAYLIB_CPP_INCLUDE_RAY_HPP_