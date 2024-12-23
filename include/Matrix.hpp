// #ifndef RAYLIB_CPP_INCLUDE_MATRIX_HPP_
// #define RAYLIB_CPP_INCLUDE_MATRIX_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"
#include "./raymath.hpp"

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

namespace raylib {
/**
 * 矩阵类型（OpenGL风格4x4 - 右手系，列优先）
 */
class 矩阵 : public ::Matrix {
public:
    矩阵(const ::Matrix& 矩阵) : ::Matrix(矩阵) {}

    矩阵(
        float m0 = 0,
        float m4 = 0,
        float m8 = 0,
        float m12 = 0,
        float m1 = 0,
        float m5 = 0,
        float m9 = 0,
        float m13 = 0,
        float m2 = 0,
        float m6 = 0,
        float m10 = 0,
        float m14 = 0,
        float m3 = 0,
        float m7 = 0,
        float m11 = 0,
        float m15 = 0)
        : ::Matrix{m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15} {
        // 无操作
    }

    GETTERSETTER(float, M0, m0)
    GETTERSETTER(float, M1, m1)
    GETTERSETTER(float, M2, m2)
    GETTERSETTER(float, M3, m3)
    GETTERSETTER(float, M4, m4)
    GETTERSETTER(float, M5, m5)
    GETTERSETTER(float, M6, m6)
    GETTERSETTER(float, M7, m7)
    GETTERSETTER(float, M8, m8)
    GETTERSETTER(float, M9, m9)
    GETTERSETTER(float, M10, m10)
    GETTERSETTER(float, M11, m11)
    GETTERSETTER(float, M12, m12)
    GETTERSETTER(float, M13, m13)
    GETTERSETTER(float, M14, m14)
    GETTERSETTER(float, M15, m15)

    矩阵& operator=(const ::Matrix& 矩阵) {
        if (this != &矩阵) {
            设(矩阵);
        }
        return *this;
    }

    矩阵& operator=(const 矩阵& 矩阵值) {
        if (this != &矩阵值) {
            设(矩阵值);
        }
        return *this;
    }

    bool operator==(const ::Matrix& other) {
        return m0 == other.m0 && m1 == other.m1 && m2 == other.m2 && m3 == other.m3 && m4 == other.m4 &&
               m5 == other.m5 && m6 == other.m6 && m7 == other.m7 && m8 == other.m8 && m9 == other.m9 &&
               m10 == other.m10 && m11 == other.m11 && m12 == other.m12 && m13 == other.m13 && m14 == other.m14 &&
               m15 == other.m15;
    }

    bool operator!=(const ::Matrix& other) { return !(*this == other); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * 返回矩阵的迹（对角线元素之和）
     */
    [[nodiscard]] float 阵迹() const { return ::MatrixTrace(*this); }

    /**
     * 转置提供的矩阵
     */
    [[nodiscard]] 矩阵 转置() const { return ::MatrixTranspose(*this); }

    [[nodiscard]] 矩阵 反矩阵() const { return ::MatrixInvert(*this); }

    static 矩阵 单位矩阵() { return ::MatrixIdentity(); }

    矩阵 加(const ::Matrix& 右) { return ::MatrixAdd(*this, 右); }

    矩阵 operator+(const ::Matrix& 矩阵) { return ::MatrixAdd(*this, 矩阵); }

    矩阵 减(const ::Matrix& 右) { return ::MatrixSubtract(*this, 右); }

    矩阵 operator-(const ::Matrix& 矩阵) { return ::MatrixSubtract(*this, 矩阵); }

    static 矩阵 平移(float x, float y, float z) { return ::MatrixTranslate(x, y, z); }

    static 矩阵 旋转(Vector3 转轴, float 角度) { return ::MatrixRotate(转轴, 角度); }

    static 矩阵 旋转XYZ(Vector3 角度) { return ::MatrixRotateXYZ(角度); }

    static 矩阵 旋转X(float 角度) { return ::MatrixRotateX(角度); }

    static 矩阵 旋转Y(float 角度) { return ::MatrixRotateY(角度); }

    static 矩阵 旋转Z(float 角度) { return ::MatrixRotateZ(角度); }

    static 矩阵 缩放(float x, float y, float z) { return ::MatrixScale(x, y, z); }

    [[nodiscard]] 矩阵 乘(const ::Matrix& 右) const { return ::MatrixMultiply(*this, 右); }

    矩阵 operator*(const ::Matrix& 矩阵) { return ::MatrixMultiply(*this, 矩阵); }

    static 矩阵 视锥体(double 左, double 右, double 下, double 上, double 近, double 远) {
        return ::MatrixFrustum(左, 右, 下, 上, 近, 远);
    }

    static 矩阵 透视(double 视角, double 宽高比, double 近, double 远) {
        return ::MatrixPerspective(视角, 宽高比, 近, 远);
    }

    static 矩阵 正交(double 左, double 右, double 下, double 上, double 近, double 远) {
        return ::MatrixOrtho(左, 右, 下, 上, 近, 远);
    }

    static 矩阵 注视(Vector3 眼, Vector3 目标, Vector3 上方向) { return ::MatrixLookAt(眼, 目标, 上方向); }

    [[nodiscard]] float16 转浮点向量() const { return ::MatrixToFloatV(*this); }

    operator float16() const { return 转浮点向量(); }

    /**
     * 设置着色器统一值（4x4矩阵）
     */
    矩阵& 设着色器值(const ::Shader& 着色器, int 统一变量位置) {
        ::SetShaderValueMatrix(着色器, 统一变量位置, *this);
        return *this;
    }

    static 矩阵 取相机(const ::Camera& 相机) { return ::GetCameraMatrix(相机); }

    static 矩阵 取相机(const ::Camera2D& 相机) { return ::GetCameraMatrix2D(相机); }

#endif
protected:
    void 设(const ::Matrix& mat) {
        m0 = mat.m0;
        m1 = mat.m1;
        m2 = mat.m2;
        m3 = mat.m3;
        m4 = mat.m4;
        m5 = mat.m5;
        m6 = mat.m6;
        m7 = mat.m7;
        m8 = mat.m8;
        m9 = mat.m9;
        m10 = mat.m10;
        m11 = mat.m11;
        m12 = mat.m12;
        m13 = mat.m13;
        m14 = mat.m14;
        m15 = mat.m15;
    }
};
} // namespace raylib

using R矩阵 = raylib::矩阵;

// #endif // RAYLIB_CPP_INCLUDE_MATRIX_HPP_