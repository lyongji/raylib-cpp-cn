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
class Ray : public ::Ray {
public:
    Ray(const ::Ray& ray) { set(ray); }

    Ray(::Vector3 position = {0.0f, 0.0f, 0.0f}, ::Vector3 direction = {0.0f, 0.0f, 0.0f})
        : ::Ray{position, direction} {
        // 无操作
    }

    Ray(::Vector2 mousePosition, const ::Camera& camera) { set(::GetMouseRay(mousePosition, camera)); }

    Ray& operator=(const ::Ray& ray) {
        set(ray);
        return *this;
    }

    GETTERSETTER(::Vector3, Position, position)
    GETTERSETTER(::Vector3, Direction, direction)

    /**
     * 绘制射线
     */
    void Draw(::Color color) const { DrawRay(*this, color); }

    /**
     * 获取射线与球体的碰撞信息
     */
    RayCollision GetCollision(::Vector3 center, float radius) const {
        return ::GetRayCollisionSphere(*this, center, radius);
    }

    /**
     * 检测射线与包围盒的碰撞
     */
    RayCollision GetCollision(const ::BoundingBox& box) const { return ::GetRayCollisionBox(*this, box); }

    /**
     * 获取射线与网格的碰撞信息
     */
    RayCollision GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const {
        return ::GetRayCollisionMesh(*this, mesh, transform);
    }

    /**
     * 获取射线与三角形的碰撞信息
     */
    RayCollision GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3) const {
        return ::GetRayCollisionTriangle(*this, p1, p2, p3);
    }

    /**
     * 获取射线与四边形的碰撞信息
     */
    RayCollision GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3, ::Vector3 p4) const {
        return ::GetRayCollisionQuad(*this, p1, p2, p3, p4);
    }

    /**
     * 从鼠标位置获取射线
     */
    static Ray GetMouse(::Vector2 mousePosition, const ::Camera& camera) {
        return ::GetMouseRay(mousePosition, camera);
    }

    /**
     * 从鼠标位置获取射线
     */
    static Ray GetMouse(const ::Camera& camera) { return ::GetMouseRay(::GetMousePosition(), camera); }
protected:
    void set(const ::Ray& ray) {
        position = ray.position;
        direction = ray.direction;
    }
};
} // namespace raylib

using RRay = raylib::Ray;

// #endif // RAYLIB_CPP_INCLUDE_RAY_HPP_