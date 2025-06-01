// #ifndef RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
// #define RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
#pragma once

#include "./Vector2.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 矩形类型
 */
class 矩形 : public ::Rectangle {
public:
  矩形(const ::Rectangle &矩形)
      : ::Rectangle{矩形.x, 矩形.y, 矩形.width, 矩形.height} {}

  矩形(float x, float y, float 宽, float 高) : ::Rectangle{x, y, 宽, 高} {}
  矩形(float x, float y, float 宽) : ::Rectangle{x, y, 宽, 0} {}
  矩形(float x, float y) : ::Rectangle{x, y, 0, 0} {}
  矩形(float x) : ::Rectangle{x, 0, 0, 0} {}
  矩形() : ::Rectangle{0, 0, 0, 0} {}

  矩形(::Vector2 位置, ::Vector2 大小)
      : ::Rectangle{位置.x, 位置.y, 大小.x, 大小.y} {}
  矩形(::Vector2 大小) : ::Rectangle{0, 0, 大小.x, 大小.y} {}
  矩形(::Vector4 矩形) : ::Rectangle{矩形.x, 矩形.y, 矩形.z, 矩形.w} {}

  GETTERSETTER(float, X, x)
  GETTERSETTER(float, Y, y)
  GETTERSETTER(float, 宽, width)
  GETTERSETTER(float, 高, height)

  矩形 &operator=(const ::Rectangle &矩形) {
    设(矩形);
    return *this;
  }

  ::Vector4 转换为Vector4() { return {x, y, width, height}; }

  explicit operator ::Vector4() const { return {x, y, width, height}; }

  void 绘制(::Color 颜色) const { ::DrawRectangleRec(*this, 颜色); }

  void 绘制(::Vector2 原点, float 旋转, ::Color 颜色) const {
    ::DrawRectanglePro(*this, 原点, 旋转, 颜色);
  }

  void 绘制垂直渐变矩形(::Color 颜色1, ::Color 颜色2) const {
    ::DrawRectangleGradientV(static_cast<int>(x), static_cast<int>(y),
                             static_cast<int>(width), static_cast<int>(height),
                             颜色1, 颜色2);
  }

  void 绘制水平渐变矩形(::Color 颜色1, ::Color 颜色2) const {
    ::DrawRectangleGradientH(static_cast<int>(x), static_cast<int>(y),
                             static_cast<int>(width), static_cast<int>(height),
                             颜色1, 颜色2);
  }

  void 绘制四角渐变矩形(::Color 左上, ::Color 左下, ::Color 右上,
                        ::Color 右下) const {
    ::DrawRectangleGradientEx(*this, 左上, 左下, 右上, 右下);
  }

  void 绘制边框(::Color 颜色) const {
    ::DrawRectangleLines(static_cast<int>(x), static_cast<int>(y),
                         static_cast<int>(width), static_cast<int>(height),
                         颜色);
  }

  void 绘制边框(::Color 颜色, float 线宽) const {
    ::DrawRectangleLinesEx(*this, 线宽, 颜色);
  }

  void 绘制圆角矩形(float 圆度, int 段数, ::Color 颜色) const {
    ::DrawRectangleRounded(*this, 圆度, 段数, 颜色);
  }

  void 绘制圆角矩形边框(float 圆度, int 段数, ::Color 颜色) const {
    ::DrawRectangleRoundedLines(*this, 圆度, 段数, 颜色);
  }

  void 绘制圆角矩形边框(float 圆度, int 段数, float 线宽, ::Color 颜色) const {
    DrawRectangleRoundedLinesEx(*this, 圆度, 段数, 线宽, 颜色);
  }

  /**
   * 检查两个矩形之间的碰撞
   */
  [[nodiscard]] bool 检查碰撞(::Rectangle 矩形2) const {
    return ::CheckCollisionRecs(*this, 矩形2);
  }

  /**
   * 获取两个矩形碰撞的矩形
   */
  [[nodiscard]] ::Rectangle 取碰撞区域(::Rectangle 矩形2) const {
    return ::GetCollisionRec(*this, 矩形2);
  }

  /**
   * 检查点是否在矩形内
   */
  [[nodiscard]] bool 检查点是否在矩形内(::Vector2 点) const {
    return ::CheckCollisionPointRec(点, *this);
  }

  /**
   * 检查圆形和矩形之间的碰撞
   */
  [[nodiscard]] bool 检查碰撞(::Vector2 圆心, float 半径) const {
    return ::CheckCollisionCircleRec(圆心, 半径, *this);
  }

  [[nodiscard]] Vector2 取尺寸() const { return {width, height}; }

  /// 设置矩形的尺寸
  矩形 &设尺寸(float 新宽, float 新高) {
    width = 新宽;
    height = 新高;
    return *this;
  }

  /// 设置矩形的尺寸
  矩形 &设尺寸(const ::Vector2 &尺寸) { return 设尺寸(尺寸.x, 尺寸.y); }

  /// 设置矩形的纹理
  矩形 &设形状纹理(const ::Texture2D &纹理) {
    ::SetShapesTexture(纹理, *this);
    return *this;
  }

  [[nodiscard]] Vector2 取位置() const { return {x, y}; }

  /// 设置矩形的坐标
  矩形 &设位置(float 新X, float 新Y) {
    x = 新X;
    y = 新Y;
    return *this;
  }

  /// 设置矩形的坐标
  矩形 &设位置(const ::Vector2 &位置) { return 设位置(位置.x, 位置.y); }

protected:
  void 设(const ::Rectangle &矩形) {
    x = 矩形.x;
    y = 矩形.y;
    width = 矩形.width;
    height = 矩形.height;
  }
};
} // namespace raylib

using R矩形 = raylib::矩形;

// #endif // RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_