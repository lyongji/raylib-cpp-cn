// #ifndef RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
// #define RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 包围盒类型
 */
class BoundingBox : public ::BoundingBox {
public:
    /*
     * 从另一个包围盒复制一个包围盒。
     */
    BoundingBox(const ::BoundingBox& box) : ::BoundingBox{box.min, box.max} {
        // 无操作
    }

    /**
     * 计算网格的包围盒限制
     */
    BoundingBox(const ::Mesh& mesh) { set(::GetMeshBoundingBox(mesh)); }

    BoundingBox(::Vector3 minMax = ::Vector3{0.0f, 0.0f, 0.0f}) : ::BoundingBox{minMax, minMax} {}
    BoundingBox(::Vector3 min, ::Vector3 max) : ::BoundingBox{min, max} {}

    GETTERSETTER(::Vector3, Min, min)
    GETTERSETTER(::Vector3, Max, max)

    BoundingBox& operator=(const ::BoundingBox& box) {
        set(box);
        return *this;
    }

    /**
     * 用线条绘制一个包围盒
     */
    void Draw(::Color color = {255, 255, 255, 255}) const { ::DrawBoundingBox(*this, color); }

    /**
     * 检测两个包围盒之间的碰撞
     */
    bool CheckCollision(const ::BoundingBox& box2) const { return CheckCollisionBoxes(*this, box2); }

    /**
     * 检测包围盒与球体之间的碰撞
     */
    bool CheckCollision(::Vector3 center, float radius) const { return CheckCollisionBoxSphere(*this, center, radius); }

    /**
     * 检测射线与包围盒之间的碰撞
     */
    bool CheckCollision(const ::Ray& ray) const { return GetRayCollisionBox(ray, *this).hit; }

    /**
     * 获取射线与包围盒之间的碰撞信息
     */
    RayCollision GetCollision(const ::Ray& ray) const { return GetRayCollisionBox(ray, *this); }
protected:
    void set(const ::BoundingBox& box) {
        min = box.min;
        max = box.max;
    }
    void set(const ::Vector3& _min, const ::Vector3& _max) {
        min = _min;
        max = _max;
    }
};
} // namespace raylib

using RBoundingBox = raylib::BoundingBox;

// #endif // RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_