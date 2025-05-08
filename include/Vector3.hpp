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
    Vector3() : ::Vector3{0, 0, 0} {}

    Vector3(::Color color) { set(ColorToHSV(color)); }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)

    Vector3& operator=(const ::Vector3& vector3) {
        set(vector3);
        return *this;
    }

    bool operator==(const ::Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

    bool operator!=(const ::Vector3& other) const { return !(*this == other); }

    [[nodiscard]] std::string ToString() const { return TextFormat("Vector3(%f, %f, %f)", x, y, z); }

    operator std::string() const { return ToString(); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * 向量相加
     */
    [[nodiscard]] Vector3 Add(const ::Vector3& vector3) const { return Vector3Add(*this, vector3); }

    /**
     * 向量相加
     */
    Vector3 operator+(const ::Vector3& vector3) const { return Vector3Add(*this, vector3); }

    Vector3& operator+=(const ::Vector3& vector3) {
        set(Vector3Add(*this, vector3));

        return *this;
    }

    /**
     * 向量相减
     */
    [[nodiscard]] Vector3 Subtract(const ::Vector3& vector3) const { return Vector3Subtract(*this, vector3); }

    /**
     * 向量相减
     */
    Vector3 operator-(const ::Vector3& vector3) const { return Vector3Subtract(*this, vector3); }

    Vector3& operator-=(const ::Vector3& vector3) {
        set(Vector3Subtract(*this, vector3));

        return *this;
    }

    /**
     * 向量取反（反转方向）
     */
    [[nodiscard]] Vector3 Negate() const { return Vector3Negate(*this); }

    /**
     * 向量取反（反转方向）
     */
    Vector3 operator-() const { return Vector3Negate(*this); }

    /**
     * 向量相乘
     */
    [[nodiscard]] Vector3 Multiply(const ::Vector3& vector3) const { return Vector3Multiply(*this, vector3); }

    /**
     * 向量相乘
     */
    Vector3 operator*(const ::Vector3& vector3) const { return Vector3Multiply(*this, vector3); }

    /**
     * 向量相乘
     */
    Vector3& operator*=(const ::Vector3& vector3) {
        set(Vector3Multiply(*this, vector3));

        return *this;
    }

    /**
     * 向量与标量相乘
     */
    [[nodiscard]] Vector3 Scale(const float scaler) const { return Vector3Scale(*this, scaler); }

    /**
     * 向量与标量相乘
     */
    Vector3 operator*(const float scaler) const { return Vector3Scale(*this, scaler); }

    /**
     * 向量与标量相乘
     */
    Vector3& operator*=(const float scaler) {
        set(Vector3Scale(*this, scaler));

        return *this;
    }

    /**
     * 向量相除
     */
    [[nodiscard]] Vector3 Divide(const ::Vector3& vector3) const { return Vector3Divide(*this, vector3); }

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
    [[nodiscard]] Vector3 Divide(const float div) const { return ::Vector3{x / div, y / div, z / div}; }

    /**
     * 向量与值相除
     */
    Vector3 operator/(const float div) const { return Divide(div); }

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
    [[nodiscard]] float Length() const { return Vector3Length(*this); }

    /**
     * 计算向量的平方长度
     */
    [[nodiscard]] float LengthSqr() const { return Vector3LengthSqr(*this); }

    [[nodiscard]] Vector3 Normalize() const { return Vector3Normalize(*this); }

    [[nodiscard]] float DotProduct(const ::Vector3& vector3) const { return Vector3DotProduct(*this, vector3); }

    [[nodiscard]] float Distance(const ::Vector3& vector3) const { return Vector3Distance(*this, vector3); }

    [[nodiscard]] Vector3 Lerp(const ::Vector3& vector3, const float amount) const {
        return Vector3Lerp(*this, vector3, amount);
    }

    [[nodiscard]] Vector3 CrossProduct(const ::Vector3& vector3) const { return Vector3CrossProduct(*this, vector3); }

    [[nodiscard]] Vector3 Perpendicular() const { return Vector3Perpendicular(*this); }

    [[nodiscard]] Vector3 Project(const ::Vector3& vector3) const { return Vector3Project(*this, vector3); }

    [[nodiscard]] Vector3 Reject(const ::Vector3& vector3) const { return Vector3Reject(*this, vector3); }

    /// 对向量进行正交归一化
    void OrthoNormalize(::Vector3* vector3) { Vector3OrthoNormalize(this, vector3); }

    [[nodiscard]] Vector3 Transform(const ::Matrix& matrix) const { return Vector3Transform(*this, matrix); }

    [[nodiscard]] Vector3 RotateByQuaternion(const ::Quaternion& quaternion) const {
        return Vector3RotateByQuaternion(*this, quaternion);
    }

    [[nodiscard]] Vector3 Reflect(const ::Vector3& normal) const { return Vector3Reflect(*this, normal); }

    [[nodiscard]] Vector3 Min(const ::Vector3& vector3) const { return Vector3Min(*this, vector3); }

    [[nodiscard]] Vector3 Max(const ::Vector3& vector3) const { return Vector3Max(*this, vector3); }

    [[nodiscard]] Vector3 Barycenter(const ::Vector3& a, const ::Vector3& b, const ::Vector3& c) const {
        return Vector3Barycenter(*this, a, b, c);
    }

    /// 返回零向量
    static Vector3 Zero() { return Vector3Zero(); }

    /// 返回单位向量
    static Vector3 One() { return Vector3One(); }
#endif

    /// 绘制三维线段
    void DrawLine3D(const ::Vector3& endPos, ::Color color) const { ::DrawLine3D(*this, endPos, color); }

    /// 绘制三维点
    void DrawPoint3D(::Color color) const { ::DrawPoint3D(*this, color); }

    /// 绘制三维圆
    void DrawCircle3D(float radius, const ::Vector3& rotationAxis, float rotationAngle, Color color) const {
        ::DrawCircle3D(*this, radius, rotationAxis, rotationAngle, color);
    }

    /// 绘制三维立方体
    void DrawCube(float width, float height, float length, ::Color color) const {
        ::DrawCube(*this, width, height, length, color);
    }

    /// 绘制三维立方体
    void DrawCube(const ::Vector3& size, ::Color color) const { ::DrawCubeV(*this, size, color); }

    /// 绘制三维立方体的线框
    void DrawCubeWires(float width, float height, float length, ::Color color) const {
        ::DrawCubeWires(*this, width, height, length, color);
    }

    /// 绘制三维立方体的线框
    void DrawCubeWires(const ::Vector3& size, ::Color color) const { ::DrawCubeWiresV(*this, size, color); }

    /// 绘制三维球体
    void DrawSphere(float radius, ::Color color) const { ::DrawSphere(*this, radius, color); }

    /// 绘制三维球体
    void DrawSphere(float radius, int rings, int slices, ::Color color) const {
        ::DrawSphereEx(*this, radius, rings, slices, color);
    }

    /// 绘制三维球体的线框
    void DrawSphereWires(float radius, int rings, int slices, ::Color color) const {
        ::DrawSphereWires(*this, radius, rings, slices, color);
    }

    /// 绘制三维圆柱体
    void DrawCylinder(float radiusTop, float radiusBottom, float height, int slices, ::Color color) const {
        ::DrawCylinder(*this, radiusTop, radiusBottom, height, slices, color);
    }

    /// 绘制三维圆柱体的线框
    void DrawCylinderWires(float radiusTop, float radiusBottom, float height, int slices, ::Color color) const {
        ::DrawCylinderWires(*this, radiusTop, radiusBottom, height, slices, color);
    }

    /// 绘制三维平面
    void DrawPlane(const ::Vector2& size, ::Color color) const { ::DrawPlane(*this, size, color); }

    /**
     * 检测两个球体之间的碰撞
     */
    [[nodiscard]] bool CheckCollision(float radius1, const ::Vector3& center2, float radius2) const {
        return CheckCollisionSpheres(*this, radius1, center2, radius2);
    }
protected:
    void set(const ::Vector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
};
} // namespace raylib

using RVector3 = raylib::Vector3;

// #endif // RAYLIB_CPP_INCLUDE_VECTOR3_HPP_