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
        设(vector2);
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

    [[nodiscard]] std::string ToString() const { return TextFormat("Vector2(%f, %f)", x, y); }

    operator std::string() const { return ToString(); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2 加(const ::Vector2& vector2) const { return Vector2Add(*this, vector2); }

    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2 operator+(const ::Vector2& vector2) const { return Vector2Add(*this, vector2); }

    /**
     * 将两个向量相加 (v1 + v2)
     */
    Vector2& operator+=(const ::Vector2& vector2) {
        设(Vector2Add(*this, vector2));

        return *this;
    }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    [[nodiscard]] Vector2 减(const ::Vector2& vector2) const { return Vector2Subtract(*this, vector2); }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    Vector2 operator-(const ::Vector2& vector2) const { return Vector2Subtract(*this, vector2); }

    /**
     * 将两个向量相减 (v1 - v2)
     */
    Vector2& operator-=(const ::Vector2& vector2) {
        设(Vector2Subtract(*this, vector2));

        return *this;
    }

    /**
     * 向量取反
     */
    [[nodiscard]] Vector2 取反() const { return Vector2Negate(*this); }

    /**
     * 向量取反
     */
    Vector2 operator-() const { return Vector2Negate(*this); }

    /**
     * 向量与向量相乘
     */
    [[nodiscard]] Vector2 乘(const ::Vector2& vector2) const { return Vector2Multiply(*this, vector2); }

    /**
     * 向量与向量相乘
     */
    Vector2 operator*(const ::Vector2& vector2) const { return Vector2Multiply(*this, vector2); }

    /**
     * 向量与向量相乘
     */
    Vector2& operator*=(const ::Vector2& vector2) {
        设(Vector2Multiply(*this, vector2));

        return *this;
    }

    /**
     * 向量缩放（乘以值）
     */
    [[nodiscard]] Vector2 缩放(const float scale) const { return Vector2Scale(*this, scale); }

    /**
     * 向量缩放（乘以值）
     */
    Vector2 operator*(const float scale) const { return Vector2Scale(*this, scale); }

    /**
     * 向量缩放（乘以值）
     */
    Vector2& operator*=(const float scale) {
        设(Vector2Scale(*this, scale));

        return *this;
    }

    /**
     * 向量除以向量
     */
    [[nodiscard]] Vector2 除(const ::Vector2& vector2) const { return Vector2Divide(*this, vector2); }

    /**
     * 向量除以向量
     */
    Vector2 operator/(const ::Vector2& vector2) const { return Vector2Divide(*this, vector2); }

    /**
     * 向量除以向量
     */
    Vector2& operator/=(const ::Vector2& vector2) {
        设(Vector2Divide(*this, vector2));

        return *this;
    }

    /**
     * 向量除以值
     */
    [[nodiscard]] Vector2 除(const float div) const { return ::Vector2{x / div, y / div}; }

    /**
     * 向量除以值
     */
    Vector2 operator/(const float div) const { return 除(div); }

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
    [[nodiscard]] Vector2 归一化() const { return Vector2Normalize(*this); }

    /**
     * 通过给定的矩阵变换向量
     */
    [[nodiscard]] Vector2 变换(::Matrix 矩阵) const { return ::Vector2Transform(*this, 矩阵); }

    /**
     * 计算两个向量之间的线性插值
     */
    [[nodiscard]] Vector2 线性插值(const ::Vector2& vector2, float 数量) const {
        return Vector2Lerp(*this, vector2, 数量);
    }

    /**
     * 计算反射向量到法线
     */
    [[nodiscard]] Vector2 反射(const ::Vector2& 法线) const { return Vector2Reflect(*this, 法线); }

    /**
     * 按浮点数（弧度）旋转向量
     */
    [[nodiscard]] Vector2 旋转(float 弧度) const { return Vector2Rotate(*this, 弧度); }

    /**
     * 向目标移动向量
     */
    [[nodiscard]] Vector2 向目标移动(const ::Vector2& 目标, float 最大距离) const {
        return Vector2MoveTowards(*this, 目标, 最大距离);
    }

    /**
     * 反转给定的向量
     */
    [[nodiscard]] Vector2 反转() const { return ::Vector2Invert(*this); }

    /**
     * 将向量的分量限制在最小值和最大值之间
     */
    [[nodiscard]] Vector2 限制(::Vector2 最小值, ::Vector2 最大值) const {
        return ::Vector2Clamp(*this, 最小值, 最大值);
    }

    /**
     * 将向量的长度限制在最小值和最大值之间
     */
    [[nodiscard]] Vector2 限制(float 最小值, float 最大值) const { return ::Vector2ClampValue(*this, 最小值, 最大值); }

    /**
     * 检查两个给定的向量是否几乎相等
     */
    [[nodiscard]] int 相等(::Vector2 Vec2) const { return ::Vector2Equals(*this, Vec2); }

    /**
     * 计算向量的长度
     */
    [[nodiscard]] float 长度() const { return Vector2Length(*this); }

    /**
     * 计算向量的平方长度
     */
    [[nodiscard]] float 长度的平方() const { return Vector2LengthSqr(*this); }

    /**
     * 计算两个向量的点积
     */
    [[nodiscard]] float 点积(const ::Vector2& vector2) const { return Vector2DotProduct(*this, vector2); }

    /**
     * 计算两个向量之间的距离
     */
    [[nodiscard]] float 距离(const ::Vector2& vector2) const { return Vector2Distance(*this, vector2); }

    /**
     * 计算两个向量之间的平方距离
     */
    [[nodiscard]] float 距离的平方(::Vector2 vec2) const { return ::Vector2DistanceSqr(*this, vec2); }

    /**
     * 计算两个向量在 X 轴上的角度
     */
    [[nodiscard]] float 夹角(const ::Vector2& vec2) const { return Vector2Angle(*this, vec2); }

    /**
     * 向量分量值为 0.0f
     */
    static Vector2 归零() { return Vector2Zero(); }

    /**
     * 向量分量值为 1.0f
     */
    static Vector2 归一() { return Vector2One(); }
#endif

    /// 绘制一个像素
    void 绘制像素(::Color 颜色 = {0, 0, 0, 255}) const { ::DrawPixelV(*this, 颜色); }

    /// 绘制一条线
    void 绘制线段(::Vector2 终点, ::Color 颜色 = {0, 0, 0, 255}) const { ::DrawLineV(*this, 终点, 颜色); }

    /// 绘制一条带厚度的线
    void 绘制线段(::Vector2 终点, float 厚度, ::Color 颜色 = {0, 0, 0, 255}) const {
        ::DrawLineEx(*this, 终点, 厚度, 颜色);
    }

    /// 绘制一条贝塞尔曲线
    void 绘制贝塞尔曲线(::Vector2 终点, float 厚度, ::Color 颜色 = {0, 0, 0, 255}) const {
        ::DrawLineBezier(*this, 终点, 厚度, 颜色);
    }

    /**
     * 绘制一个颜色填充的圆（Vector 版本）
     */
    void 绘制圆形(float 半径, ::Color 颜色 = {0, 0, 0, 255}) const { ::DrawCircleV(*this, 半径, 颜色); }

    /// 绘制矩形
    void 绘制矩形(::Vector2 尺寸, ::Color 颜色 = {0, 0, 0, 255}) const { ::DrawRectangleV(*this, 尺寸, 颜色); }

    /// 绘制多边形
    void 绘制多边形(int 边, float 半径, float 旋转, ::Color 颜色 = {0, 0, 0, 255}) const {
        ::DrawPoly(*this, 边, 半径, 旋转, 颜色);
    }

    /**
     * 检查两个圆之间的碰撞
     */
    [[nodiscard]] bool 是圆在碰撞(float 半径1, ::Vector2 圆心2, float 半径2) const {
        return ::CheckCollisionCircles(*this, 半径1, 圆心2, 半径2);
    }

    /**
     * 检查圆和矩形之间的碰撞
     */
    [[nodiscard]] bool 是矩形在碰撞(float 半径, ::Rectangle 矩形) const {
        return ::CheckCollisionCircleRec(*this, 半径, 矩形);
    }

    /**
     * 检查点是否在矩形内
     */
    [[nodiscard]] bool 是碰撞(::Rectangle 矩形) const { return ::CheckCollisionPointRec(*this, 矩形); }

    /**
     * 检查点是否在圆内
     */
    [[nodiscard]] bool 是碰撞(::Vector2 圆心, float 半径) const {
        return ::CheckCollisionPointCircle(*this, 圆心, 半径);
    }

    /**
     * 检查点是否在三角形内
     */
    [[nodiscard]] bool 是碰撞(::Vector2 p1, ::Vector2 p2, ::Vector2 p3) const {
        return ::CheckCollisionPointTriangle(*this, p1, p2, p3);
    }

    /**
     * 检查两条由两点定义的线段之间的碰撞，返回碰撞点
     */
    bool 是线段碰撞(::Vector2 终点1, ::Vector2 起点2, ::Vector2 终点2, ::Vector2* 交叉点) const {
        return ::CheckCollisionLines(*this, 终点1, 起点2, 终点2, 交叉点);
    }

    /**
     * 检查点是否属于由两点 [p1] 和 [p2] 创建的线段，定义的像素阈值 [threshold]
     */
    [[nodiscard]] bool 是点与线碰撞(::Vector2 p1, ::Vector2 p2, int 阈值 = 1) const {
        return ::CheckCollisionPointLine(*this, p1, p2, 阈值);
    }
protected:
    void 设(const ::Vector2& vec) {
        x = vec.x;
        y = vec.y;
    }
};

} // namespace raylib

using RVector2 = raylib::Vector2;
using R点2 = raylib::Vector2;
using RVec2 = raylib::Vector2;

// #endif // RAYLIB_CPP_INCLUDE_VECTOR2_HPP_