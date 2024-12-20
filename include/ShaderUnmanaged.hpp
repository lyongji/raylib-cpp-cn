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
class ShaderUnmanaged : public ::Shader {
public:
    ShaderUnmanaged() : ::Shader{rlGetShaderIdDefault(), rlGetShaderLocsDefault()} {}

    ShaderUnmanaged(const ::Shader& shader) : ::Shader(shader) { }

    ShaderUnmanaged(unsigned int id, int* locs = nullptr) : ::Shader{id, locs} {}

    ShaderUnmanaged(const std::string& vsFileName, const std::string& fsFileName) {
        set(::LoadShader(vsFileName.c_str(), fsFileName.c_str()));
    }
    ShaderUnmanaged(const char* vsFileName, const char* fsFileName) { set(::LoadShader(vsFileName, fsFileName)); }

    /**
     * 从文件加载着色器并绑定默认位置。
     *
     * @see ::LoadShader
     */
    static ::Shader Load(const std::string& vsFileName, const std::string& fsFileName) {
        return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
    }
    static ::Shader Load(const char* vsFileName, const char* fsFileName) {
        return ::LoadShader(vsFileName, fsFileName);
    }

    /**
     * 从内存加载着色器。
     *
     * @see ::LoadShaderFromMemory
     */
    static ::Shader LoadFromMemory(const std::string& vsCode, const std::string& fsCode) {
        return ::LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
    }
    static ::Shader LoadFromMemory(const char* vsCode, const char* fsCode) {
        return ::LoadShaderFromMemory(vsCode, fsCode);
    }

    GETTER(unsigned int, Id, id)
    GETTER(int*, Locs, locs)

    ShaderUnmanaged& operator=(const ::Shader& shader) {
        set(shader);
        return *this;
    }

    /**
     * 开始自定义着色器绘制。
     */
    ShaderUnmanaged& BeginMode() {
        ::BeginShaderMode(*this);
        return *this;
    }

    /**
     * 结束自定义着色器绘制（使用默认着色器）。
     */
    ShaderUnmanaged& EndMode() {
        ::EndShaderMode();
        return *this;
    }

    /**
     * 获取着色器统一变量的位置
     *
     * @see GetShaderLocation()
     */
    [[nodiscard]] int GetLocation(const std::string& uniformName) const { return ::GetShaderLocation(*this, uniformName.c_str()); }

    /**
     * 获取着色器属性的位置
     *
     * @see GetShaderLocationAttrib()
     */
    [[nodiscard]] int GetLocationAttrib(const std::string& attribName) const {
        return ::GetShaderLocationAttrib(*this, attribName.c_str());
    }

    /**
     * 设置着色器统一变量的值
     *
     * @see SetShaderValue()
     */
    ShaderUnmanaged& SetValue(int uniformLoc, const void* value, int uniformType) {
        ::SetShaderValue(*this, uniformLoc, value, uniformType);
        return *this;
    }

    /**
     * 设置着色器统一变量的向量值
     *
     * @see SetShaderValueV()
     */
    ShaderUnmanaged& SetValue(int uniformLoc, const void* value, int uniformType, int count) {
        ::SetShaderValueV(*this, uniformLoc, value, uniformType, count);
        return *this;
    }

    /**
     * 设置着色器统一变量的值（4x4 矩阵）
     *
     * @see SetShaderValueMatrix()
     */
    ShaderUnmanaged& SetValue(int uniformLoc, const ::Matrix& mat) {
        ::SetShaderValueMatrix(*this, uniformLoc, mat);
        return *this;
    }

    /**
     * 设置着色器统一变量的纹理值
     *
     * @see SetShaderValueTexture()
     */
    ShaderUnmanaged& SetValue(int uniformLoc, const ::Texture2D& texture) {
        ::SetShaderValueTexture(*this, uniformLoc, texture);
        return *this;
    }

    /**
     * 检索着色器是否准备就绪。
     */
    [[nodiscard]] bool IsValid() const { return ::IsShaderValid(*this); }
protected:
    void set(const ::Shader& shader) {
        id = shader.id;
        locs = shader.locs;
    }
};
} // namespace raylib

using RShaderUnmanaged = raylib::ShaderUnmanaged;

// #endif // RAYLIB_CPP_INCLUDE_UNMANAGEDSHADER_HPP_