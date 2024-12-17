// #ifndef RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
// #define RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 光线投射碰撞信息
 */
class 射线碰撞 : public ::RayCollision {
public:
    射线碰撞(const ::RayCollision& 射线碰撞) { 设(射线碰撞); }

    射线碰撞(bool 命中, float 相距, ::Vector3 碰撞点, ::Vector3 点法线) : ::RayCollision{命中, 相距, 碰撞点, 点法线} {
        // 无操作
    }

    /**
     * 获取光线与包围盒的碰撞信息
     */
    射线碰撞(const ::Ray& 射线, const ::BoundingBox& 包围盒) { 设(::GetRayCollisionBox(射线, 包围盒)); }

    /**
     * 获取光线与网格的碰撞信息
     */
    射线碰撞(const ::Ray& 射线, const ::Mesh& 网格, const ::Matrix& 变换) {
        设(::GetRayCollisionMesh(射线, 网格, 变换));
    }

    /**
     * 获取光线与四边形的碰撞信息
     */
    射线碰撞(const ::Ray& 射线, ::Vector3 顶点1, ::Vector3 顶点2, ::Vector3 顶点3, ::Vector3 顶点4) {
        设(::GetRayCollisionQuad(射线, 顶点1, 顶点2, 顶点3, 顶点4));
    }

    /**
     * 获取光线与球体的碰撞信息
     */
    射线碰撞(const ::Ray& 射线, ::Vector3 球心, float 半径) { 设(::GetRayCollisionSphere(射线, 球心, 半径)); }

    /**
     * 获取光线与三角形的碰撞信息
     */
    射线碰撞(const ::Ray& 射线, ::Vector3 顶点1, ::Vector3 顶点2, ::Vector3 顶点3) {
        设(::GetRayCollisionTriangle(射线, 顶点1, 顶点2, 顶点3));
    }

    射线碰撞& operator=(const ::RayCollision& 射线碰撞) {
        设(射线碰撞);
        return *this;
    }

    GETTERSETTER(bool, 命中, hit)
    GETTERSETTER(float, 相距, distance)
    GETTERSETTER(::Vector3, 碰撞点, point)
    GETTERSETTER(::Vector3, 法线, normal)
protected:
    void 设(const ::RayCollision& 射线碰撞) {
        hit = 射线碰撞.hit;
        distance = 射线碰撞.distance;
        point = 射线碰撞.point;
        normal = 射线碰撞.normal;
    }
};
} // namespace raylib

using R射线碰撞 = raylib::射线碰撞;

// #endif // RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_