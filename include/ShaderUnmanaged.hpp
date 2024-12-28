// #ifndef RAYLIB_CPP_INCLUDE_UNMANAGEDSHADER_HPP_
// #define RAYLIB_CPP_INCLUDE_UNMANAGEDSHADER_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

#include <rlgl.h>
#include <string>

namespace raylib {

/**
 * Shader 类型（通用），不由 C++ RAII 管理。
 */
class 非托管着色器 : public ::Shader {
public:
    非托管着色器() : ::Shader{rlGetShaderIdDefault(), rlGetShaderLocsDefault()} {}

    非托管着色器(const ::Shader& 着色器) : ::Shader(着色器) {}

    非托管着色器(unsigned int id, int* 位置数组 = nullptr) : ::Shader{id, 位置数组} {}

    非托管着色器(const std::string& 顶点着色器文件名, const std::string& 片段着色器文件名) {
        设(::LoadShader(顶点着色器文件名.c_str(), 片段着色器文件名.c_str()));
    }
    非托管着色器(const char* 顶点着色器文件名, const char* 片段着色器文件名) {
        设(::LoadShader(顶点着色器文件名, 片段着色器文件名));
    }

    /**
     * 从文件加载着色器并绑定默认位置。
     *
     * @see ::LoadShader
     */
    static ::Shader 加载(const std::string& 顶点着色器文件名, const std::string& 片段着色器文件名) {
        return ::LoadShader(顶点着色器文件名.c_str(), 片段着色器文件名.c_str());
    }
    static ::Shader 加载(const char* 顶点着色器文件名, const char* 片段着色器文件名) {
        return ::LoadShader(顶点着色器文件名, 片段着色器文件名);
    }

    /**
     * 从内存加载着色器。
     *
     * @see ::LoadShaderFromMemory
     */
    static ::Shader 加载于内存(const std::string& 顶点着色器代码, const std::string& 片段着色器代码) {
        return ::LoadShaderFromMemory(顶点着色器代码.c_str(), 片段着色器代码.c_str());
    }
    static ::Shader 加载于内存(const char* 顶点着色器代码, const char* 片段着色器代码) {
        return ::LoadShaderFromMemory(顶点着色器代码, 片段着色器代码);
    }

    GETTER(unsigned int, Id, id)
    GETTER(int*, 位置数组, locs)

    非托管着色器& operator=(const ::Shader& 着色器) {
        设(着色器);
        return *this;
    }

    /**
     * 开始自定义着色器绘制。
     */
    非托管着色器& 开始() {
        ::BeginShaderMode(*this);
        return *this;
    }

    /**
     * 结束自定义着色器绘制（使用默认着色器）。
     */
    非托管着色器& 结束() {
        ::EndShaderMode();
        return *this;
    }

    /**
     * 获取着色器统一变量的位置
     *
     * @see GetShaderLocation()
     */
    [[nodiscard]] int 取位置(const std::string& 统一变量名) const {
        return ::GetShaderLocation(*this, 统一变量名.c_str());
    }

    /**
     * 获取着色器属性的位置
     *
     * @see GetShaderLocationAttrib()
     */
    [[nodiscard]] int 取属性位置(const std::string& 属性名) const {
        return ::GetShaderLocationAttrib(*this, 属性名.c_str());
    }

    /**
     * 设置着色器统一变量的值
     *
     * @see SetShaderValue()
     */
    非托管着色器& 设变量(int 变量位置, const void* 变量值, int 变量类型) {
        ::SetShaderValue(*this, 变量位置, 变量值, 变量类型);
        return *this;
    }

    /**
     * 设置着色器统一变量的向量值
     *
     * @see SetShaderValueV()
     */
    非托管着色器& 设变量(int 变量位置, const void* 变量值, int 变量类型, int 数量) {
        ::SetShaderValueV(*this, 变量位置, 变量值, 变量类型, 数量);
        return *this;
    }

    /**
     * 设置着色器统一变量的值（4x4 矩阵）
     *
     * @see SetShaderValueMatrix()
     */
    非托管着色器& 设变量(int 变量位置, const ::Matrix& 矩阵) {
        ::SetShaderValueMatrix(*this, 变量位置, 矩阵);
        return *this;
    }

    /**
     * 设置着色器统一变量的纹理值
     *
     * @see SetShaderValueTexture()
     */
    非托管着色器& 设变量(int 变量位置, const ::Texture2D& 纹理) {
        ::SetShaderValueTexture(*this, 变量位置, 纹理);
        return *this;
    }

    /**
     * 检索着色器是否准备就绪。
     */
    [[nodiscard]] bool 是就绪() const { return ::IsShaderValid(*this); }
protected:
    void 设(const ::Shader& 着色器) {
        id = 着色器.id;
        locs = 着色器.locs;
    }
};
} // namespace raylib

using R非托管着色器 = raylib::非托管着色器;

// #endif // RAYLIB_CPP_INCLUDE_UNMANAGEDSHADER_HPP_