// #ifndef RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
// #define RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
#pragma once

#include "./RaylibException.hpp"
#include "./TextureUnmanaged.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * RenderTexture 类型，用于纹理渲染
 */
class 渲染纹理 : public ::RenderTexture {
public:
    /**
     * 默认构造函数，用于构建一个空的 RenderTexture。
     */
    渲染纹理() { id = 0; }

    渲染纹理(const ::RenderTexture& 渲染纹理) { 设(渲染纹理); }

    渲染纹理(unsigned int id, const ::Texture& 纹理, const ::Texture& 深度) : ::RenderTexture{id, 纹理, 深度} {}

    /**
     * 加载用于渲染的纹理（帧缓冲区）
     */
    渲染纹理(int 宽, int 高) { 设(::LoadRenderTexture(宽, 高)); }

    渲染纹理(const 渲染纹理&) = delete;

    渲染纹理(渲染纹理&& other) {
        设(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};
    }

    GETTER(unsigned int, Id, id)

    /**
     * 获取颜色缓冲区附件纹理。
     */
    R非托管纹理 取纹理() { return texture; }

    void 设纹理(const ::Texture& 新纹理) { texture = 新纹理; }

    /**
     * 深度缓冲区附件纹理
     */
    R非托管纹理 取深度() { return depth; }

    void 设深度(const ::Texture& 新深度) { depth = 新深度; }

    渲染纹理& operator=(const ::RenderTexture& 纹理) {
        设(纹理);
        return *this;
    }

    渲染纹理& operator=(const 渲染纹理&) = delete;

    渲染纹理& operator=(渲染纹理&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};

        return *this;
    }

    ~渲染纹理() { 卸载(); }

    /// 卸载渲染纹理
    void 卸载() { UnloadRenderTexture(*this); }

    /**
     * 初始化渲染纹理以进行绘制
     */
    渲染纹理& 开始() {
        ::BeginTextureMode(*this);
        return *this;
    }

    /**
     * 结束绘制到渲染纹理
     */
    渲染纹理& 结束() {
        ::EndTextureMode();
        return *this;
    }

    /**
     * 加载用于渲染的纹理（帧缓冲区）
     */
    static 渲染纹理 加载(int 宽, int 高) { return ::LoadRenderTexture(宽, 高); }

    /**
     * 检索渲染纹理是否准备就绪。
     */
    bool 是有效() const { return ::IsRenderTextureValid(*this); }
protected:
    void 设(const ::RenderTexture& 渲染纹理) {
        id = 渲染纹理.id;
        texture = 渲染纹理.texture;
        depth = 渲染纹理.depth;
    }
};

using 渲染纹理2D = 渲染纹理;

} // namespace raylib

using R渲染纹理 = raylib::渲染纹理;
using R渲染纹理2D = raylib::渲染纹理2D;

// #endif // RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_