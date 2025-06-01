// #ifndef RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
// #define RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
#pragma once

#include "./TextureUnmanaged.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * RenderTexture 类型，用于纹理渲染
 */
class 渲染纹理 : public ::RenderTexture {
public:
  渲染纹理() = default;

  渲染纹理(const ::RenderTexture &渲染纹理) : ::RenderTexture(渲染纹理) {}

  渲染纹理(unsigned int id, const ::Texture &纹理, const ::Texture &深度)
      : ::RenderTexture{id, 纹理, 深度} {}

  /**
   * 加载用于渲染的纹理（帧缓冲区）
   */
  渲染纹理(int 宽, int 高) : ::RenderTexture(::LoadRenderTexture(宽, 高)) {}

  渲染纹理(const 渲染纹理 &) = delete;

  渲染纹理(渲染纹理 &&other) noexcept {
    设(other);

    other.id = 0;
    other.texture = {};
    other.depth = {};
  }

  GETTER(unsigned int, 纹理ID, id)

  /**
   * 获取颜色缓冲区附件纹理。
   */
  R非托管纹理 取颜色纹理() { return texture; }

  void 设颜色纹理(const ::Texture &新纹理) { texture = 新纹理; }

  /**
   * 深度缓冲区附件纹理
   */
  R非托管纹理 取深度纹理() { return depth; }

  void 设深度纹理(const ::Texture &新深度) { depth = 新深度; }

  渲染纹理 &operator=(const ::RenderTexture &纹理) {
    设(纹理);
    return *this;
  }

  渲染纹理 &operator=(const 渲染纹理 &) = delete;

  渲染纹理 &operator=(渲染纹理 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载渲染纹理();
    设(other);

    other.id = 0;
    other.texture = {};
    other.depth = {};

    return *this;
  }

  ~渲染纹理() { 卸载渲染纹理(); }

  void 卸载渲染纹理() { UnloadRenderTexture(*this); }

  /**
   * 初始化渲染纹理以进行绘制
   */
  渲染纹理 &开始绘制() {
    ::BeginTextureMode(*this);
    return *this;
  }

  /**
   * 结束绘制到渲染纹理
   */
  渲染纹理 &结束绘制() {
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
  [[nodiscard]] bool 检查可用性() const {
    return ::IsRenderTextureValid(*this);
  }

protected:
  void 设(const ::RenderTexture &渲染纹理) {
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