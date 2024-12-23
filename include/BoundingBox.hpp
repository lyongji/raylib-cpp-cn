// #ifndef RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
// #define RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 包围盒类型
 */
class 包围盒 : public ::BoundingBox {
public:
    /*
     * 从另一个包围盒复制一个包围盒。
     */
    包围盒(const ::BoundingBox& box) : ::BoundingBox{box.min, box.max} {
        // 无操作
    }

    /**
     * 计算网格的包围盒限制
     */
    包围盒(const ::Mesh& 网格) { 设(::GetMeshBoundingBox(网格)); }

    包围盒(::Vector3 最大最小值 = ::Vector3{0.0f, 0.0f, 0.0f}) : ::BoundingBox{最大最小值, 最大最小值} {}
    包围盒(::Vector3 最小值, ::Vector3 最大值) : ::BoundingBox{最小值, 最大值} {}

    GETTERSETTER(::Vector3, 最小值, min)
    GETTERSETTER(::Vector3, 最大值, max)

    包围盒& operator=(const ::BoundingBox& 包围盒) {
        设(包围盒);
        return *this;
    }

    /**
     * 用线条绘制一个包围盒
     */
    void 绘制(::Color 颜色 = {255, 255, 255, 255}) const { ::DrawBoundingBox(*this, 颜色); }

    /**
     * 检测两个包围盒之间的碰撞
     */
    [[nodiscard]] bool 检测碰撞(const ::BoundingBox& 包围盒2) const { return CheckCollisionBoxes(*this, 包围盒2); }

    /**
     * 检测包围盒与球体之间的碰撞
     */
    [[nodiscard]] bool 检测碰撞(::Vector3 中心, float 半径) const { return CheckCollisionBoxSphere(*this, 中心, 半径); }

    /**
     * 检测射线与包围盒之间的碰撞
     */
    [[nodiscard]] bool 检测碰撞(const ::Ray& 射线) const { return GetRayCollisionBox(射线, *this).hit; }

    /**
     * 获取射线与包围盒之间的碰撞信息
     */
    RayCollision 取碰撞信息(const ::Ray& 射线) const { return GetRayCollisionBox(射线, *this); }
protected:
    void 设(const ::BoundingBox& 包围盒) {
        min = 包围盒.min;
        max = 包围盒.max;
    }
    void 设(const ::Vector3& _min, const ::Vector3& _max) {
        min = _min;
        max = _max;
    }
};
} // namespace raylib

using R包围盒 = raylib::包围盒;

// #endif // RAYLIB_CPP_INCLUDE_BOUNDINGBOX_HPP_