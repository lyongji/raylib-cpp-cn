// #ifndef RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
// #define RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 光线投射碰撞信息
 */
class RayCollision : public ::RayCollision {
public:
    RayCollision(const ::RayCollision& ray) { set(ray); }

    RayCollision(bool hit, float distance, ::Vector3 point, ::Vector3 normal)
        : ::RayCollision{hit, distance, point, normal} {
        // 无操作
    }

    /**
     * 获取光线与包围盒的碰撞信息
     */
    RayCollision(const ::Ray& ray, const ::BoundingBox& box) { set(::GetRayCollisionBox(ray, box)); }

    /**
     * 获取光线与网格的碰撞信息
     */
    RayCollision(const ::Ray& ray, const ::Mesh& mesh, const ::Matrix& transform) {
        set(::GetRayCollisionMesh(ray, mesh, transform));
    }

    /**
     * 获取光线与四边形的碰撞信息
     */
    RayCollision(const ::Ray& ray, ::Vector3 p1, ::Vector3 p2, ::Vector3 p3, ::Vector3 p4) {
        set(::GetRayCollisionQuad(ray, p1, p2, p3, p4));
    }

    /**
     * 获取光线与球体的碰撞信息
     */
    RayCollision(const ::Ray& ray, ::Vector3 center, float radius) {
        set(::GetRayCollisionSphere(ray, center, radius));
    }

    /**
     * 获取光线与三角形的碰撞信息
     */
    RayCollision(const ::Ray& ray, ::Vector3 p1, ::Vector3 p2, ::Vector3 p3) {
        set(::GetRayCollisionTriangle(ray, p1, p2, p3));
    }

    RayCollision& operator=(const ::RayCollision& ray) {
        set(ray);
        return *this;
    }

    GETTERSETTER(bool, Hit, hit)
    GETTERSETTER(float, Distance, distance)
    GETTERSETTER(::Vector3, Position, point)
    GETTERSETTER(::Vector3, Normal, normal)
protected:
    void set(const ::RayCollision& ray) {
        hit = ray.hit;
        distance = ray.distance;
        point = ray.point;
        normal = ray.normal;
    }
};
} // namespace raylib

using RRayCollision = raylib::RayCollision;

// #endif // RAYLIB_CPP_INCLUDE_RAYCOLLISION_HPP_