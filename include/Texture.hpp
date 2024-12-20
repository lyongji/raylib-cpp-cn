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
class Texture : public TextureUnmanaged {
public:
    using TextureUnmanaged::TextureUnmanaged;

    /**
     * 显式禁止拷贝构造函数。
     */
    Texture(const Texture&) = delete;

    /**
     * 显式禁止拷贝赋值。
     */
    Texture& operator=(const Texture&) = delete;

    /**
     * 移动构造函数。
     */
    Texture(Texture&& other)  noexcept {
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    /**
     * 在销毁时卸载纹理。
     */
    ~Texture() { Unload(); }

    /**
     * 移动赋值。
     */
    Texture& operator=(Texture&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }
};

// 创建 Texture 的别名。
using Texture2D = Texture;
using TextureCubemap = Texture;

} // namespace raylib

using RTexture = raylib::Texture;
using RTexture2D = raylib::Texture2D;
using RTextureCubemap = raylib::TextureCubemap;

// #endif // RAYLIB_CPP_INCLUDE_TEXTURE_HPP_