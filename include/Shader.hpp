// #ifndef RAYLIB_CPP_INCLUDE_SHADER_HPP_
// #define RAYLIB_CPP_INCLUDE_SHADER_HPP_
#pragma once

#include <string>

#include "ShaderUnmanaged.hpp"
#include "Texture.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Shader 类型（通用）
 */
class Shader : public ShaderUnmanaged {
public:
    using ShaderUnmanaged::ShaderUnmanaged;

    Shader(const Shader&) = delete;

    Shader(Shader&& other) {
        set(other);

        other.id = 0;
        other.locs = nullptr;
    }

    Shader& operator=(const Shader&) = delete;

    Shader& operator=(Shader&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.locs = nullptr;

        return *this;
    }

    /**
     * 从 GPU 内存（VRAM）中卸载着色器
     */
    ~Shader() { Unload(); }

    /**
     * 从 GPU 内存（VRAM）中卸载着色器
     */
    void Unload() {
        if (locs != nullptr) {
            ::UnloadShader(*this);
        }
    }
};
} // namespace raylib

using RShader = raylib::Shader;

// #endif // RAYLIB_CPP_INCLUDE_SHADER_HPP_