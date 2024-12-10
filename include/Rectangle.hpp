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
class Rectangle : public ::Rectangle {
public:
    Rectangle(const ::Rectangle& rect) : ::Rectangle{rect.x, rect.y, rect.width, rect.height} {}

    Rectangle(float x, float y, float width, float height) : ::Rectangle{x, y, width, height} {}
    Rectangle(float x, float y, float width) : ::Rectangle{x, y, width, 0} {}
    Rectangle(float x, float y) : ::Rectangle{x, y, 0, 0} {}
    Rectangle(float x) : ::Rectangle{x, 0, 0, 0} {}
    Rectangle() : ::Rectangle{0, 0, 0, 0} {}

    Rectangle(::Vector2 position, ::Vector2 size) : ::Rectangle{position.x, position.y, size.x, size.y} {}
    Rectangle(::Vector2 size) : ::Rectangle{0, 0, size.x, size.y} {}
    Rectangle(::Vector4 rect) : ::Rectangle{rect.x, rect.y, rect.z, rect.w} {}

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Width, width)
    GETTERSETTER(float, Height, height)

    Rectangle& operator=(const ::Rectangle& rect) {
        set(rect);
        return *this;
    }

    ::Vector4 ToVector4() { return {x, y, width, height}; }

    operator ::Vector4() const { return {x, y, width, height}; }

    /**
     * 绘制一个颜色填充的矩形
     */
    void Draw(::Color color) const { ::DrawRectangleRec(*this, color); }

    void Draw(::Vector2 origin, float rotation, ::Color color) const {
        ::DrawRectanglePro(*this, origin, rotation, color);
    }

    /// 绘制垂直渐变矩形
    void DrawGradientV(::Color color1, ::Color color2) const {
        ::DrawRectangleGradientV(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height),
            color1,
            color2);
    }

    /// 绘制水平渐变矩形
    void DrawGradientH(::Color color1, ::Color color2) const {
        ::DrawRectangleGradientH(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height),
            color1,
            color2);
    }

    /// 绘制四角渐变矩形
    void DrawGradient(::Color topLeft, ::Color bottomLeft, ::Color topRight, ::Color bottomRight) const {
        ::DrawRectangleGradientEx(*this, topLeft, bottomLeft, topRight, bottomRight);
    }

    /// 绘制矩形边框
    void DrawLines(::Color color) const {
        ::DrawRectangleLines(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height),
            color);
    }

    /// 绘制矩形边框，指定线宽
    void DrawLines(::Color color, float lineThick) const { ::DrawRectangleLinesEx(*this, lineThick, color); }

    /// 绘制圆角矩形
    void DrawRounded(float roundness, int segments, ::Color color) const {
        ::DrawRectangleRounded(*this, roundness, segments, color);
    }

    /// 绘制圆角矩形边框
    void DrawRoundedLines(float roundness, int segments, ::Color color) const {
        ::DrawRectangleRoundedLines(*this, roundness, segments, color);
    }

    /// 绘制圆角矩形边框，指定线宽
    void DrawRoundedLines(float roundness, int segments, float lineThick, ::Color color) const {
        DrawRectangleRoundedLinesEx(*this, roundness, segments, lineThick, color);
    }

    /**
     * 检查两个矩形之间的碰撞
     */
    bool CheckCollision(::Rectangle rec2) const { return ::CheckCollisionRecs(*this, rec2); }

    /**
     * 获取两个矩形碰撞的矩形
     */
    ::Rectangle GetCollision(::Rectangle rec2) const { return ::GetCollisionRec(*this, rec2); }

    /**
     * 检查点是否在矩形内
     */
    bool CheckCollision(::Vector2 point) const { return ::CheckCollisionPointRec(point, *this); }

    /**
     * 检查圆形和矩形之间的碰撞
     */
    bool CheckCollision(::Vector2 center, float radius) const {
        return ::CheckCollisionCircleRec(center, radius, *this);
    }

    /// 获取矩形的尺寸
    Vector2 GetSize() const { return {width, height}; }

    /// 设置矩形的尺寸
    Rectangle& SetSize(float newWidth, float newHeight) {
        width = newWidth;
        height = newHeight;
        return *this;
    }

    /// 设置矩形的尺寸
    Rectangle& SetSize(const ::Vector2& size) { return SetSize(size.x, size.y); }

    /// 设置矩形的纹理
    Rectangle& SetShapesTexture(const ::Texture2D& texture) {
        ::SetShapesTexture(texture, *this);
        return *this;
    }

    /// 获取矩形的坐标
    Vector2 GetPosition() const { return {x, y}; }

    /// 设置矩形的坐标
    Rectangle& SetPosition(float newX, float newY) {
        x = newX;
        y = newY;
        return *this;
    }

    /// 设置矩形的坐标
    Rectangle& SetPosition(const ::Vector2& position) { return SetPosition(position.x, position.y); }
protected:
    void set(const ::Rectangle& rect) {
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
    }
};
} // namespace raylib

using RRectangle = raylib::Rectangle;

// #endif // RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_