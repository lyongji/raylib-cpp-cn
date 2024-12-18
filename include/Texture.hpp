// #ifndef RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
// #define RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
#pragma once

#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * 纹理类型
 *
 * 纹理将在对象销毁时自动卸载。如果不想自动卸载，请使用 raylib::TextureUnmanaged。
 *
 * @see raylib::TextureUnmanaged
 */
class 纹理 : public 非托管纹理 {
public:
    using 非托管纹理::非托管纹理;

    /**
     * 显式禁止拷贝构造函数。
     */
    纹理(const 纹理&) = delete;

    /**
     * 显式禁止拷贝赋值。
     */
    纹理& operator=(const 纹理&) = delete;

    /**
     * 移动构造函数。
     */
    纹理(纹理&& other) {
        设(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    /**
     * 在销毁时卸载纹理。
     */
    ~纹理() { 卸载(); }

    /**
     * 移动赋值。
     */
    纹理& operator=(纹理&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }
};

// 创建 Texture 的别名。
using 纹理2D = 纹理;
using 立方体贴图 = 纹理;

} // namespace raylib

using R纹理 = raylib::纹理;
using R纹理2D = raylib::纹理2D;
using R立方体贴图 = raylib::立方体贴图;

// #endif // RAYLIB_CPP_INCLUDE_TEXTURE_HPP_