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
class 着色器 : public 非托管着色器 {
public:
    using 非托管着色器::非托管着色器;

    着色器(const 着色器&) = delete;

    着色器(着色器&& other) noexcept {
        设(other);

        other.id = 0;
        other.locs = nullptr;
    }

    着色器& operator=(const 着色器&) = delete;

    着色器& operator=(着色器&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.id = 0;
        other.locs = nullptr;

        return *this;
    }

    /**
     * 从 GPU 内存（VRAM）中卸载着色器
     */
    ~着色器() { 卸载(); }

    /**
     * 从 GPU 内存（VRAM）中卸载着色器
     */
    void 卸载() {
        if (locs != nullptr) {
            ::UnloadShader(*this);
        }
    }
};
} // namespace raylib

using R着色器 = raylib::着色器;

// #endif // RAYLIB_CPP_INCLUDE_SHADER_HPP_