// #ifndef RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
// #define RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
#pragma once

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#include <utility>
#endif

#include <string>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"
#include "./raymath.hpp"

namespace raylib {
/**
 * Vector4 类型
 */
class Vector4 : public ::Vector4 {
public:
    Vector4(const ::Vector4& vec) : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

    Vector4(float x, float y, float z, float w) : ::Vector4{x, y, z, w} {}
    Vector4(float x, float y, float z) : ::Vector4{x, y, z, 0} {}
    Vector4(float x, float y) : ::Vector4{x, y, 0, 0} {}
    Vector4(float x) : ::Vector4{x, 0, 0, 0} {}
    Vector4() : ::Vector4{0, 0, 0, 0} {}
    Vector4(::Rectangle rectangle) : ::Vector4{rectangle.x, rectangle.y, rectangle.width, rectangle.height} {}

    Vector4(::Color color) { set(ColorNormalize(color)); }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)
    GETTERSETTER(float, W, w)

    Vector4& operator=(const ::Vector4& vector4) {
        set(vector4);
        return *this;
    }

    bool operator==(const ::Vector4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const ::Vector4& other) const { return !(*this == other); }

    ::Rectangle ToRectangle() const { return {x, y, z, w}; }

    operator ::Rectangle() const { return {x, y, z, w}; }

    std::string ToString() const { return TextFormat("Vector4(%f, %f, %f, %f)", x, y, z, w); }

    operator std::string() const { return ToString(); }

#ifndef RAYLIB_CPP_NO_MATH
    /// 乘以一个Vector4类型的向量
    Vector4 Multiply(const ::Vector4& vector4) const { return QuaternionMultiply(*this, vector4); }

    /// 重载*运算符，实现四元数与向量的乘法
    Vector4 operator*(const ::Vector4& vector4) const { return QuaternionMultiply(*this, vector4); }

    /// 插值，实现四元数与向量的线性插值
    Vector4 Lerp(const ::Vector4& vector4, float amount) const { return QuaternionLerp(*this, vector4, amount); }

    /// 插值，实现四元数与向量的归一化插值
    Vector4 Nlerp(const ::Vector4& vector4, float amount) const { return QuaternionNlerp(*this, vector4, amount); }

    /// 插值，实现四元数与向量的球面插值
    Vector4 Slerp(const ::Vector4& vector4, float amount) const { return QuaternionSlerp(*this, vector4, amount); }

    /// 将四元数转换为矩阵
    Matrix ToMatrix() const { return QuaternionToMatrix(*this); }

    /// 计算四元数的长度
    float Length() const { return QuaternionLength(*this); }

    /// 归一化四元数
    Vector4 Normalize() const { return QuaternionNormalize(*this); }

    /// 逆四元数
    Vector4 Invert() const { return QuaternionInvert(*this); }

    /// 将四元数转换为轴角
    void ToAxisAngle(::Vector3* outAxis, float* outAngle) const { QuaternionToAxisAngle(*this, outAxis, outAngle); }

    /**
     * 获取给定四元数的旋转角度和轴
     */
    std::pair<Vector3, float> ToAxisAngle() const {
        Vector3 outAxis;
        float outAngle;
        QuaternionToAxisAngle(*this, &outAxis, &outAngle);

        return std::pair<Vector3, float>(outAxis, outAngle);
    }

    /// 将四元数转换为矩阵
    Vector4 Transform(const ::Matrix& matrix) const { return ::QuaternionTransform(*this, matrix); }

    /// 返回单位四元数
    static Vector4 Identity() { return ::QuaternionIdentity(); }

    /// 将一个向量转换为另一个向量
    static Vector4 FromVector3ToVector3(const ::Vector3& from, const ::Vector3& to) {
        return ::QuaternionFromVector3ToVector3(from, to);
    }

    /// 将矩阵转换为四元数
    static Vector4 FromMatrix(const ::Matrix& matrix) { return ::QuaternionFromMatrix(matrix); }

    /// 将一个轴和一个角度转换为四元数
    static Vector4 FromAxisAngle(const ::Vector3& axis, const float angle) {
        return ::QuaternionFromAxisAngle(axis, angle);
    }

    /// 将欧拉角转换为四元数
    static Vector4 FromEuler(const float pitch, const float yaw, const float roll) {
        return ::QuaternionFromEuler(pitch, yaw, roll);
    }

    /// 将一个向量转换为四元数
    static Vector4 FromEuler(const ::Vector3& vector3) {
        return ::QuaternionFromEuler(vector3.x, vector3.y, vector3.z);
    }

    /// 将四元数转换为欧拉角
    Vector3 ToEuler() const { return ::QuaternionToEuler(*this); }
#endif

    /// 从归一化值返回颜色
    Color ColorFromNormalized() const { return ::ColorFromNormalized(*this); }

    operator Color() const { return ColorFromNormalized(); }
protected:
    void set(const ::Vector4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }
};

/// 将 Vector4 别名为 Quaternion
using Quaternion = Vector4;

} // namespace raylib

using RVector4 = raylib::Vector4;
using RQuaternion = raylib::Quaternion;

// #endif // RAYLIB_CPP_INCLUDE_VECTOR4_HPP_