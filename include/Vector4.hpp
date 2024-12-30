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

    Vector4(::Color color) { 设(ColorNormalize(color)); }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)
    GETTERSETTER(float, W, w)

    Vector4& operator=(const ::Vector4& vector4) {
        设(vector4);
        return *this;
    }

    bool operator==(const ::Vector4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const ::Vector4& other) const { return !(*this == other); }

    [[nodiscard]] ::Rectangle 转矩形() const { return {x, y, z, w}; }

    operator ::Rectangle() const { return {x, y, z, w}; }

    [[nodiscard]] std::string 转文本() const { return TextFormat("Vector4(%f, %f, %f, %f)", x, y, z, w); }

    operator std::string() const { return 转文本(); }

#ifndef RAYLIB_CPP_NO_MATH
    [[nodiscard]] Vector4 乘(const ::Vector4& vector4) const { return QuaternionMultiply(*this, vector4); }

    /// 重载*运算符，实现四元数与向量的乘法
    Vector4 operator*(const ::Vector4& vector4) const { return QuaternionMultiply(*this, vector4); }

    [[nodiscard]] Vector4 线性插值(const ::Vector4& vector4, float 数量) const {
        return QuaternionLerp(*this, vector4, 数量);
    }

    [[nodiscard]] Vector4 归一化线性插值(const ::Vector4& vector4, float 数量) const {
        return QuaternionNlerp(*this, vector4, 数量);
    }

    [[nodiscard]] Vector4 球面线性插值(const ::Vector4& vector4, float 数量) const {
        return QuaternionSlerp(*this, vector4, 数量);
    }

    [[nodiscard]] Matrix 转矩阵() const { return QuaternionToMatrix(*this); }

    [[nodiscard]] float 长度() const { return QuaternionLength(*this); }

    [[nodiscard]] Vector4 归一化() const { return QuaternionNormalize(*this); }

    /// 四元数取逆
    [[nodiscard]] Vector4 逆() const { return QuaternionInvert(*this); }

    /// 将四元数转换为轴角
    void 转轴角(::Vector3* 输出轴, float* 输出角度) const { QuaternionToAxisAngle(*this, 输出轴, 输出角度); }

    /**
     * 获取给定四元数的旋转角度和轴
     */
    [[nodiscard]] std::pair<Vector3, float> 转轴角() const {
        Vector3 输出轴;
        float 输出角度;
        QuaternionToAxisAngle(*this, &输出轴, &输出角度);

        return {输出轴, 输出角度};
    }

    [[nodiscard]] Vector4 变换(const ::Matrix& 矩阵) const { return ::QuaternionTransform(*this, 矩阵); }

    /// 返回单位四元数
    static Vector4 单位四元数() { return ::QuaternionIdentity(); }

    /// 将一个向量转换为另一个向量
    static Vector4 从Vector3转换为Vector3(const ::Vector3& 从, const ::Vector3& 到) {
        return ::QuaternionFromVector3ToVector3(从, 到);
    }

    /// 将矩阵转换为四元数
    static Vector4 从矩阵转(const ::Matrix& 矩阵) { return ::QuaternionFromMatrix(矩阵); }

    /// 将一个轴和一个角度转换为四元数
    static Vector4 从轴角转(const ::Vector3& 轴, const float 角度) { return ::QuaternionFromAxisAngle(轴, 角度); }

    /// 将欧拉角转换为四元数
    static Vector4 从欧拉角转(const float 俯仰, const float yaw, const float roll) {
        return ::QuaternionFromEuler(俯仰, yaw, roll);
    }

    /// 将一个向量转换为四元数
    static Vector4 从欧拉角转(const ::Vector3& vector3) {
        return ::QuaternionFromEuler(vector3.x, vector3.y, vector3.z);
    }

    [[nodiscard]] Vector3 转欧拉角() const { return ::QuaternionToEuler(*this); }
#endif

    [[nodiscard]] Color 从归一化转为颜色() const { return ::ColorFromNormalized(*this); }

    operator Color() const { return 从归一化转为颜色(); }
protected:
    void 设(const ::Vector4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }
};

/// 将 Vector4 别名为 Quaternion
using 四元数 = Vector4;

} // namespace raylib

using RVector4 = raylib::Vector4;
using R四元数 = raylib::四元数;
using RVec4 = raylib::Vector4;

// #endif // RAYLIB_CPP_INCLUDE_VECTOR4_HPP_