// #ifndef RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
// #define RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
#pragma once

#include "./TextureUnmanaged.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * RenderTexture 类型，用于纹理渲染
 */
class RenderTexture : public ::RenderTexture {
public:
    /**
     * 默认构造函数，用于构建一个空的 RenderTexture。
     */
    RenderTexture() = default;

    RenderTexture(const ::RenderTexture& renderTexture)
        : ::RenderTexture(renderTexture) {
        // Nothing.
    }

    RenderTexture(unsigned int id, const ::Texture& texture, const ::Texture& depth)
        : ::RenderTexture{id, texture, depth} {}

    /**
     * 加载用于渲染的纹理（帧缓冲区）
     */
    RenderTexture(int width, int height)
        : ::RenderTexture(::LoadRenderTexture(width, height)) {
        // Nothing.
    }

    RenderTexture(const RenderTexture&) = delete;

    RenderTexture(RenderTexture&& other) noexcept
    {
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};
    }

    GETTER(unsigned int, Id, id)

    /**
     * 获取颜色缓冲区附件纹理。
     */
    TextureUnmanaged GetTexture() { return texture; }

    void SetTexture(const ::Texture& newTexture) { texture = newTexture; }

    /**
     * 深度缓冲区附件纹理
     */
    TextureUnmanaged GetDepth() { return depth; }

    void SetDepth(const ::Texture& newDepth) { depth = newDepth; }

    RenderTexture& operator=(const ::RenderTexture& texture) {
        set(texture);
        return *this;
    }

    RenderTexture& operator=(const RenderTexture&) = delete;

    RenderTexture& operator=(RenderTexture&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};

        return *this;
    }

    ~RenderTexture() { Unload(); }

    /// 卸载渲染纹理
    void Unload() { UnloadRenderTexture(*this); }

    /**
     * 初始化渲染纹理以进行绘制
     */
    RenderTexture& BeginMode() {
        ::BeginTextureMode(*this);
        return *this;
    }

    /**
     * 结束绘制到渲染纹理
     */
    RenderTexture& EndMode() {
        ::EndTextureMode();
        return *this;
    }

    /**
     * 加载用于渲染的纹理（帧缓冲区）
     */
    static RenderTexture Load(int width, int height) { return ::LoadRenderTexture(width, height); }

    /**
     * 检索渲染纹理是否准备就绪。
     */
    [[nodiscard]] bool IsValid() const { return ::IsRenderTextureValid(*this); }
protected:
    void set(const ::RenderTexture& renderTexture) {
        id = renderTexture.id;
        texture = renderTexture.texture;
        depth = renderTexture.depth;
    }
};

using RenderTexture2D = RenderTexture;

} // namespace raylib

using RRenderTexture = raylib::RenderTexture;
using RRenderTexture2D = raylib::RenderTexture2D;

// #endif // RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_