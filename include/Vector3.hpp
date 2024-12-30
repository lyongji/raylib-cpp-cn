// #ifndef RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
// #define RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
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
 * Vector3 类型
 */
class Vector3 : public ::Vector3 {
public:
    Vector3(const ::Vector3& vec) : ::Vector3{vec.x, vec.y, vec.z} {}

    Vector3(float x, float y, float z) : ::Vector3{x, y, z} {}
    Vector3(float x, float y) : ::Vector3{x, y, 0} {}
    Vector3(float x) : ::Vector3{x, 0, 0} {}
    Vector3() : ::Vector3{0, 0, 0} {};

    Vector3(::Color color) { 设(ColorToHSV(color)); }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)

    Vector3& operator=(const ::Vector3& vector3) {
        设(vector3);
        return *this;
    }

    bool operator==(const ::Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

    bool operator!=(const ::Vector3& other) const { return !(*this == other); }

    [[nodiscard]] std::string 转文本() const { return TextFormat("Vector3(%f, %f, %f)", x, y, z); }

    operator std::string() const { return 转文本(); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * 向量相加
     */
    [[nodiscard]] Vector3 加(const ::Vector3& vector3) const { return Vector3Add(*this, vector3); }

    /**
     * 向量相加
     */
    Vector3 operator+(const ::Vector3& vector3) const { return Vector3Add(*this, vector3); }

    Vector3& operator+=(const ::Vector3& vector3) {
        设(Vector3Add(*this, vector3));

        return *this;
    }

    /**
     * 向量相减
     */
    [[nodiscard]] Vector3 减(const ::Vector3& vector3) const { return Vector3Subtract(*this, vector3); }

    /**
     * 向量相减
     */
    Vector3 operator-(const ::Vector3& vector3) const { return Vector3Subtract(*this, vector3); }

    Vector3& operator-=(const ::Vector3& vector3) {
        设(Vector3Subtract(*this, vector3));

        return *this;
    }

    /**
     * 向量取反（反转方向）
     */
    [[nodiscard]] Vector3 取反() const { return Vector3Negate(*this); }

    /**
     * 向量取反（反转方向）
     */
    Vector3 operator-() const { return Vector3Negate(*this); }

    /**
     * 向量相乘
     */
    [[nodiscard]] Vector3 乘(const ::Vector3& vector3) const { return Vector3Multiply(*this, vector3); }

    /**
     * 向量相乘
     */
    Vector3 operator*(const ::Vector3& vector3) const { return Vector3Multiply(*this, vector3); }

    /**
     * 向量相乘
     */
    Vector3& operator*=(const ::Vector3& vector3) {
        设(Vector3Multiply(*this, vector3));

        return *this;
    }

    /**
     * 向量与标量相乘
     */
    [[nodiscard]] Vector3 缩放(const float scaler) const { return Vector3Scale(*this, scaler); }

    /**
     * 向量与标量相乘
     */
    Vector3 operator*(const float scaler) const { return Vector3Scale(*this, scaler); }

    /**
     * 向量与标量相乘
     */
    Vector3& operator*=(const float scaler) {
        设(Vector3Scale(*this, scaler));

        return *this;
    }

    /**
     * 向量相除
     */
    [[nodiscard]] Vector3 除(const ::Vector3& vector3) const { return Vector3Divide(*this, vector3); }

    /**
     * 向量相除
     */
    Vector3 operator/(const ::Vector3& vector3) const { return Vector3Divide(*this, vector3); }

    /**
     * 向量相除
     */
    Vector3& operator/=(const ::Vector3& vector3) {
        x /= vector3.x;
        y /= vector3.y;
        z /= vector3.z;

        return *this;
    }

    /**
     * 向量与值相除
     */
    [[nodiscard]] Vector3 除(const float div) const { return ::Vector3{x / div, y / div, z / div}; }

    /**
     * 向量与值相除
     */
    Vector3 operator/(const float div) const { return 除(div); }

    /**
     * 向量与值相除
     */
    Vector3& operator/=(const float div) {
        x /= div;
        y /= div;
        z /= div;

        return *this;
    }

    /**
     * 计算向量的长度
     */
    [[nodiscard]] float 长度() const { return Vector3Length(*this); }

    /**
     * 计算向量的平方长度
     */
    [[nodiscard]] float 长度的平方() const { return Vector3LengthSqr(*this); }

    [[nodiscard]] Vector3 归一化() const { return Vector3Normalize(*this); }

    [[nodiscard]] float 点积(const ::Vector3& vector3) const { return Vector3DotProduct(*this, vector3); }

    [[nodiscard]] float 距离(const ::Vector3& vector3) const { return Vector3Distance(*this, vector3); }

    [[nodiscard]] Vector3 线性插值(const ::Vector3& vector3, const float 数量) const {
        return Vector3Lerp(*this, vector3, 数量);
    }

    [[nodiscard]] Vector3 叉积(const ::Vector3& vector3) const { return Vector3CrossProduct(*this, vector3); }

    [[nodiscard]] Vector3 垂直向量() const { return Vector3Perpendicular(*this); }

    [[nodiscard]] Vector3 投影(const ::Vector3& vector3) const { return Vector3Project(*this, vector3); }

    /// 计算向量的拒识Reject
    [[nodiscard]] Vector3 拒识(const ::Vector3& vector3) const { return Vector3Reject(*this, vector3); }

    /// 对向量进行正交归一化
    void 正交归一化(::Vector3* vector3) { Vector3OrthoNormalize(this, vector3); }

    [[nodiscard]] Vector3 变换(const ::Matrix& 矩阵) const { return Vector3Transform(*this, 矩阵); }

    [[nodiscard]] Vector3 四元数旋转(const ::Quaternion& 四元数) const {
        return Vector3RotateByQuaternion(*this, 四元数);
    }

    [[nodiscard]] Vector3 反射(const ::Vector3& 法线) const { return Vector3Reflect(*this, 法线); }

    [[nodiscard]] Vector3 最小值(const ::Vector3& vector3) const { return Vector3Min(*this, vector3); }

    [[nodiscard]] Vector3 最大值(const ::Vector3& vector3) const { return Vector3Max(*this, vector3); }

    [[nodiscard]] Vector3 重心(const ::Vector3& a, const ::Vector3& b, const ::Vector3& c) const {
        return Vector3Barycenter(*this, a, b, c);
    }

    /// 返回零向量
    static Vector3 归零() { return Vector3Zero(); }

    /// 返回单位向量
    static Vector3 归一() { return Vector3One(); }
#endif

    /// 绘制三维线段
    void 绘制三维线段(const ::Vector3& 终点, ::Color 颜色) const { ::DrawLine3D(*this, 终点, 颜色); }

    /// 绘制三维点
    void 绘制三维点(::Color 颜色) const { ::DrawPoint3D(*this, 颜色); }

    /// 绘制三维圆
    void 绘制三维圆(float 半径, const ::Vector3& 旋转轴, float 旋转角度, Color 颜色) const {
        ::DrawCircle3D(*this, 半径, 旋转轴, 旋转角度, 颜色);
    }

    /// 绘制三维立方体
    void 绘制立方体(float 宽, float 高, float 长, ::Color 颜色) const { ::DrawCube(*this, 宽, 高, 长, 颜色); }

    /// 绘制三维立方体
    void 绘制立方体(const ::Vector3& 尺寸, ::Color 颜色) const { ::DrawCubeV(*this, 尺寸, 颜色); }

    /// 绘制三维立方体的线框
    void 绘制立方体边框(float 宽, float 高, float 长, ::Color 颜色) const { ::DrawCubeWires(*this, 宽, 高, 长, 颜色); }

    /// 绘制三维立方体的线框
    void 绘制立方体边框(const ::Vector3& 尺寸, ::Color 颜色) const { ::DrawCubeWiresV(*this, 尺寸, 颜色); }

    /// 绘制三维球体
    void 绘制球体(float 半径, ::Color 颜色) const { ::DrawSphere(*this, 半径, 颜色); }

    /// 绘制三维球体
    void 绘制球体(float 半径, int 环数, int 段数, ::Color 颜色) const { ::DrawSphereEx(*this, 半径, 环数, 段数, 颜色); }

    /// 绘制三维球体的线框
    void 绘制球体线框(float 半径, int 环数, int 段数, ::Color 颜色) const {
        ::DrawSphereWires(*this, 半径, 环数, 段数, 颜色);
    }

    /// 绘制三维圆柱体
    void 绘制柱体(float 顶半径, float 底半径, float 高, int 段数, ::Color 颜色) const {
        ::DrawCylinder(*this, 顶半径, 底半径, 高, 段数, 颜色);
    }

    /// 绘制三维圆柱体的线框
    void 绘制柱体线框(float 顶半径, float 底半径, float 高, int 段数, ::Color 颜色) const {
        ::DrawCylinderWires(*this, 顶半径, 底半径, 高, 段数, 颜色);
    }

    /// 绘制三维平面
    void 绘制平面(const ::Vector2& 尺寸, ::Color 颜色) const { ::DrawPlane(*this, 尺寸, 颜色); }

    /**
     * 检测两个球体之间的碰撞
     */
    [[nodiscard]] bool 是碰撞(float 半径1, const ::Vector3& 球心2, float 半径2) const {
        return CheckCollisionSpheres(*this, 半径1, 球心2, 半径2);
    }
protected:
    void 设(const ::Vector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
};
} // namespace raylib

using RVector3 = raylib::Vector3;
using R点3 = raylib::Vector3;
using RVec3 = raylib::Vector3;
// #endif // RAYLIB_CPP_INCLUDE_VECTOR3_HPP_