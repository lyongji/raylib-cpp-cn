// #ifndef RAYLIB_CPP_INCLUDE_VECTOR2_HPP_
// #define RAYLIB_CPP_INCLUDE_VECTOR2_HPP_
#pragma once

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

#include <string>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"
#include "./raymath.hpp"

namespace raylib {
/**
 * Vector2 类型
 */
class Vector2 : public ::Vector2 {
public:
    Vector2(const ::Vector2& vec) : ::Vector2{vec.x, vec.y} {}

    Vector2(float x, float y) : ::Vector2{x, y} {}
    Vector2(float x) : ::Vector2{x, 0} {}
    Vector2() : ::Vector2{0, 0} {}

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)

    /**
     * 将 Vector2 设置为与给定的 Vector2 相同。
     */
    Vector2& operator=(const ::Vector2& vector2) {
        set(vector2);
        return *this;
    }

    /**
     * 确定两个向量是否相等。
     */
    bool operator==(const ::Vector2& other) const { return x == other.x && y == other.y; }

    /**
     * 确定两个向量是否不相等。
     */
    bool operator!=(const ::Vector2& other) const { return !(*this == other); }

    std::string ToString() const { return TextFormat("Vector2(%f, %f)", x, y); }

    operator std::string() const { return ToString(); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2 Add(const ::Vector2& vector2) const { return Vector2Add(*this, vector2); }

    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2 operator+(const ::Vector2& vector2) const { return Vector2Add(*this, vector2); }

    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2& operator+=(const ::Vector2& vector2) {
        set(Vector2Add(*this, vector2));

        return *this;
    }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    Vector2 Subtract(const ::Vector2& vector2) const { return Vector2Subtract(*this, vector2); }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    Vector2 operator-(const ::Vector2& vector2) const { return Vector2Subtract(*this, vector2); }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    Vector2& operator-=(const ::Vector2& vector2) {
        set(Vector2Subtract(*this, vector2));

        return *this;
    }

    /**
     * 向量取反
     */
    Vector2 Negate() const { return Vector2Negate(*this); }

    /**
     * 向量取反
     */
    Vector2 operator-() const { return Vector2Negate(*this); }

    /**
     * 向量与向量相乘
     */
    Vector2 Multiply(const ::Vector2& vector2) const { return Vector2Multiply(*this, vector2); }

    /**
     * 向量与向量相乘
     */
    Vector2 operator*(const ::Vector2& vector2) const { return Vector2Multiply(*this, vector2); }

    /**
     * 向量与向量相乘
     */
    Vector2& operator*=(const ::Vector2& vector2) {
        set(Vector2Multiply(*this, vector2));

        return *this;
    }

    /**
     * 向量缩放（乘以值）
     */
    Vector2 Scale(const float scale) const { return Vector2Scale(*this, scale); }

    /**
     * 向量缩放（乘以值）
     */
    Vector2 operator*(const float scale) const { return Vector2Scale(*this, scale); }

    /**
     * 向量缩放（乘以值）
     */
    Vector2& operator*=(const float scale) {
        set(Vector2Scale(*this, scale));

        return *this;
    }

    /**
     * 向量除以向量
     */
    Vector2 Divide(const ::Vector2& vector2) const { return Vector2Divide(*this, vector2); }

    /**
     * 向量除以向量
     */
    Vector2 operator/(const ::Vector2& vector2) const { return Vector2Divide(*this, vector2); }

    /**
     * 向量除以向量
     */
    Vector2& operator/=(const ::Vector2& vector2) {
        set(Vector2Divide(*this, vector2));

        return *this;
    }

    /**
     * 向量除以值
     */
    Vector2 Divide(const float div) const { return ::Vector2{x / div, y / div}; }

    /**
     * 向量除以值
     */
    Vector2 operator/(const float div) const { return Divide(div); }

    /**
     * 向量除以值
     */
    Vector2& operator/=(const float div) {
        this->x /= div;
        this->y /= div;

        return *this;
    }

    /**
     * 归一化向量
     */
    Vector2 Normalize() const { return Vector2Normalize(*this); }

    /**
     * 通过给定的矩阵变换向量
     */
    Vector2 Transform(::Matrix mat) const { return ::Vector2Transform(*this, mat); }

    /**
     * 计算两个向量之间的线性插值
     */
    Vector2 Lerp(const ::Vector2& vector2, float amount) const { return Vector2Lerp(*this, vector2, amount); }

    /**
     * 计算反射向量到法线
     */
    Vector2 Reflect(const ::Vector2& normal) const { return Vector2Reflect(*this, normal); }

    /**
     * 按浮点数（弧度）旋转向量
     */
    Vector2 Rotate(float angle) const { return Vector2Rotate(*this, angle); }

    /**
     * 向目标移动向量
     */
    Vector2 MoveTowards(const ::Vector2& target, float maxDistance) const {
        return Vector2MoveTowards(*this, target, maxDistance);
    }

    /**
     * 反转给定的向量
     */
    Vector2 Invert() const { return ::Vector2Invert(*this); }

    /**
     * 将向量的分量限制在最小值和最大值之间
     */
    Vector2 Clamp(::Vector2 min, ::Vector2 max) const { return ::Vector2Clamp(*this, min, max); }

    /**
     * 将向量的长度限制在最小值和最大值之间
     */
    Vector2 Clamp(float min, float max) const { return ::Vector2ClampValue(*this, min, max); }

    /**
     * 检查两个给定的向量是否几乎相等
     */
    int Equals(::Vector2 q) const { return ::Vector2Equals(*this, q); }

    /**
     * 计算向量的长度
     */
    float Length() const { return Vector2Length(*this); }

    /**
     * 计算向量的平方长度
     */
    float LengthSqr() const { return Vector2LengthSqr(*this); }

    /**
     * 计算两个向量的点积
     */
    float DotProduct(const ::Vector2& vector2) const { return Vector2DotProduct(*this, vector2); }

    /**
     * 计算两个向量之间的距离
     */
    float Distance(const ::Vector2& vector2) const { return Vector2Distance(*this, vector2); }

    /**
     * 计算两个向量之间的平方距离
     */
    float DistanceSqr(::Vector2 v2) const { return ::Vector2DistanceSqr(*this, v2); }

    /**
     * 计算两个向量在 X 轴上的角度
     */
    float Angle(const ::Vector2& vector2) const { return Vector2Angle(*this, vector2); }

    /**
     * 向量分量值为 0.0f
     */
    static Vector2 Zero() { return Vector2Zero(); }

    /**
     * 向量分量值为 1.0f
     */
    static Vector2 One() { return Vector2One(); }
#endif

    /// 绘制一个像素
    void DrawPixel(::Color color = {0, 0, 0, 255}) const { ::DrawPixelV(*this, color); }

    /// 绘制一条线
    void DrawLine(::Vector2 endPos, ::Color color = {0, 0, 0, 255}) const { ::DrawLineV(*this, endPos, color); }

    /// 绘制一条带厚度的线
    void DrawLine(::Vector2 endPos, float thick, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineEx(*this, endPos, thick, color);
    }

    /// 绘制一条贝塞尔曲线
    void DrawLineBezier(::Vector2 endPos, float thick, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineBezier(*this, endPos, thick, color);
    }

    /**
     * 绘制一个颜色填充的圆（Vector 版本）
     */
    void DrawCircle(float radius, ::Color color = {0, 0, 0, 255}) const { ::DrawCircleV(*this, radius, color); }

    /// 绘制矩形
    void DrawRectangle(::Vector2 size, ::Color color = {0, 0, 0, 255}) const { ::DrawRectangleV(*this, size, color); }

    /// 绘制多边形
    void DrawPoly(int sides, float radius, float rotation, ::Color color = {0, 0, 0, 255}) const {
        ::DrawPoly(*this, sides, radius, rotation, color);
    }

    /**
     * 检查两个圆之间的碰撞
     */
    bool CheckCollisionCircle(float radius1, ::Vector2 center2, float radius2) const {
        return ::CheckCollisionCircles(*this, radius1, center2, radius2);
    }

    /**
     * 检查圆和矩形之间的碰撞
     */
    bool CheckCollisionCircle(float radius, ::Rectangle rec) const {
        return ::CheckCollisionCircleRec(*this, radius, rec);
    }

    /**
     * 检查点是否在矩形内
     */
    bool CheckCollision(::Rectangle rec) const { return ::CheckCollisionPointRec(*this, rec); }

    /**
     * 检查点是否在圆内
     */
    bool CheckCollision(::Vector2 center, float radius) const {
        return ::CheckCollisionPointCircle(*this, center, radius);
    }

    /**
     * 检查点是否在三角形内
     */
    bool CheckCollision(::Vector2 p1, ::Vector2 p2, ::Vector2 p3) const {
        return ::CheckCollisionPointTriangle(*this, p1, p2, p3);
    }

    /**
     * 检查两条由两点定义的线段之间的碰撞，返回碰撞点
     */
    bool
    CheckCollisionLines(::Vector2 endPos1, ::Vector2 startPos2, ::Vector2 endPos2, ::Vector2* collisionPoint) const {
        return ::CheckCollisionLines(*this, endPos1, startPos2, endPos2, collisionPoint);
    }

    /**
     * 检查点是否属于由两点 [p1] 和 [p2] 创建的线段，定义的像素阈值 [threshold]
     */
    bool CheckCollisionPointLine(::Vector2 p1, ::Vector2 p2, int threshold = 1) const {
        return ::CheckCollisionPointLine(*this, p1, p2, threshold);
    }
protected:
    void set(const ::Vector2& vec) {
        x = vec.x;
        y = vec.y;
    }
};

} // namespace raylib

using RVector2 = raylib::Vector2;

// #endif // RAYLIB_CPP_INCLUDE_VECTOR2_HPP_