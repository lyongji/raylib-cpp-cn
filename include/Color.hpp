// #ifndef RAYLIB_CPP_INCLUDE_COLOR_HPP_
// #define RAYLIB_CPP_INCLUDE_COLOR_HPP_
#pragma once

#include <string>

#include "./Vector4.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 颜色类型，RGBA（32位）
 */
class Color : public ::Color {
public:
    Color(const ::Color& color) : ::Color{color.r, color.g, color.b, color.a} {}

    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : ::Color{red, green, blue, alpha} {};

    /**
     * 黑色。
     */
    Color() : ::Color{0, 0, 0, 255} {};

    /**
     * 从 HSV 值返回一个颜色
     */
    Color(::Vector3 hsv) { set(::ColorFromHSV(hsv.x, hsv.y, hsv.z)); }

    /**
     * 从 HSV 值返回一个颜色
     */
    static ::Color FromHSV(float hue, float saturation, float value) { return ::ColorFromHSV(hue, saturation, value); }

    /**
     * 从十六进制值获取颜色结构
     */
    explicit Color(unsigned int hexValue) : ::Color(::GetColor(hexValue)) { }

    Color(void* srcPtr, int format) : ::Color(::GetPixelColor(srcPtr, format)) { }

    /**
     * 返回颜色的十六进制值
     */
    [[nodiscard]] int ToInt() const { return ::ColorToInt(*this); }

    /**
     * 返回颜色的十六进制值
     */
    explicit operator int() const { return ::ColorToInt(*this); }

    [[nodiscard]] std::string ToString() const { return TextFormat("Color(%d, %d, %d, %d)", r, g, b, a); }

    explicit operator std::string() const { return ToString(); }

    /**
     * 返回应用了 alpha 的颜色，alpha 的范围是 0.0f 到 1.0f
     */
    [[nodiscard]] Color Fade(float alpha) const { return ::Fade(*this, alpha); }

    /**
     * 返回归一化的颜色，范围为 [0..1]
     */
    [[nodiscard]] Vector4 Normalize() const { return ::ColorNormalize(*this); }

    /**
     * 从归一化的值 [0..1] 返回颜色
     */
    explicit Color(::Vector4 normalized) : Color(::ColorFromNormalized(normalized)) { }

    /**
     * 返回颜色的 HSV 值
     */
    [[nodiscard]] Vector3 ToHSV() const { return ::ColorToHSV(*this); }

    GETTERSETTER(unsigned char, R, r)
    GETTERSETTER(unsigned char, G, g)
    GETTERSETTER(unsigned char, B, b)
    GETTERSETTER(unsigned char, A, a)

    Color& operator=(const ::Color& color) {
        set(color);
        return *this;
    }

    /**
     * 设置背景颜色（帧缓冲区清除颜色）
     */
    Color& ClearBackground() {
        ::ClearBackground(*this);
        return *this;
    }

    void DrawPixel(int x, int y) const { ::DrawPixel(x, y, *this); }

    /**
     * 绘制一个像素
     */
    void DrawPixel(::Vector2 pos) const { ::DrawPixelV(pos, *this); }

    /**
     * 绘制一条线
     */
    void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY) const {
        ::DrawLine(startPosX, startPosY, endPosX, endPosY, *this);
    }

    /**
     * 使用向量点绘制一条线
     */
    void DrawLine(::Vector2 startPos, ::Vector2 endPos) const { ::DrawLineV(startPos, endPos, *this); }

    /**
     * 使用向量点绘制一条线，并指定线宽
     */
    void DrawLine(::Vector2 startPos, ::Vector2 endPos, float thick) const {
        ::DrawLineEx(startPos, endPos, thick, *this);
    }

    void DrawLineBezier(::Vector2 startPos, ::Vector2 endPos, float thick = 1.0f) const {
        ::DrawLineBezier(startPos, endPos, thick, *this);
    }

    void DrawLineStrip(::Vector2* points, int numPoints) const { ::DrawLineStrip(points, numPoints, *this); }

    void DrawText(const char* text, int posX = 0, int posY = 0, int fontSize = 10.0f) const {
        ::DrawText(text, posX, posY, fontSize, *this);
    }

    void DrawText(const std::string& text, int posX = 0, int posY = 0, int fontSize = 10.0f) const {
        ::DrawText(text.c_str(), posX, posY, fontSize, *this);
    }

    void DrawText(const ::Font& font, const char* text, ::Vector2 position, float fontSize, float spacing) const {
        ::DrawTextEx(font, text, position, fontSize, spacing, *this);
    }

    void
    DrawText(const ::Font& font, const std::string& text, ::Vector2 position, float fontSize, float spacing) const {
        ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, *this);
    }

    void DrawText(
        const ::Font& font,
        const char* text,
        ::Vector2 position,
        ::Vector2 origin,
        float rotation,
        float fontSize,
        float spacing) const {
        ::DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, *this);
    }

    void DrawText(
        const ::Font& font,
        const std::string& text,
        ::Vector2 position,
        ::Vector2 origin,
        float rotation,
        float fontSize,
        float spacing) const {
        ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, *this);
    }

    void DrawRectangle(int posX, int posY, int width, int height) const {
        ::DrawRectangle(posX, posY, width, height, *this);
    }

    void DrawRectangle(::Vector2 position, ::Vector2 size) const { ::DrawRectangleV(position, size, *this); }

    void DrawRectangle(::Rectangle rec) const { ::DrawRectangleRec(rec, *this); }

    void DrawRectangle(::Rectangle rec, ::Vector2 origin, float rotation) const {
        ::DrawRectanglePro(rec, origin, rotation, *this);
    }

    void DrawRectangleLines(int posX, int posY, int width, int height) const {
        ::DrawRectangleLines(posX, posY, width, height, *this);
    }

    void DrawRectangleLines(::Rectangle rec, float lineThick) const { ::DrawRectangleLinesEx(rec, lineThick, *this); }

    bool IsEqual(::Color color) { return ::ColorIsEqual(*this, color); }

    bool operator==(const ::Color& other) const { return ::ColorIsEqual(*this, other); }
    bool operator!=(const ::Color& other) const { return !::ColorIsEqual(*this, other); }

    /**
     * 获取颜色与另一个颜色相乘的结果
     */
    Color Tint(::Color tint) { return ::ColorTint(*this, tint); }

    /**
     * 获取颜色亮度调整后的结果，亮度因子范围为 -1.0f 到 1.0f
     */
    Color Brightness(float factor) { return ::ColorBrightness(*this, factor); }

    /**
     * 获取颜色对比度调整后的结果，对比度值范围为 -1.0f 到 1.0f
     */
    Color Contrast(float contrast) { return ::ColorContrast(*this, contrast); }

    /**
     * 返回应用了 alpha 的颜色，alpha 的范围是 0.0f 到 1.0f
     */
    [[nodiscard]] Color Alpha(float alpha) const { return ::ColorAlpha(*this, alpha); }

    Color Lerp(::Color color2, float factor) { return ::ColorLerp(*this, color2, factor); }

    /**
     * 返回 src 颜色与 dst 颜色进行 alpha 混合后的结果，并应用 tint 颜色
     */
    [[nodiscard]] Color AlphaBlend(::Color dst, ::Color tint) const { return ::ColorAlphaBlend(dst, *this, tint); }

    static Color LightGray() { return LIGHTGRAY; }
    static Color Gray() { return GRAY; }
    static Color DarkGray() { return DARKGRAY; }
    static Color Yellow() { return YELLOW; }
    static Color Gold() { return GOLD; }
    static Color Orange() { return ORANGE; }
    static Color Pink() { return PINK; }
    static Color Red() { return RED; }
    static Color Maroon() { return MAROON; }
    static Color Green() { return GREEN; }
    static Color Lime() { return LIME; }
    static Color DarkGreen() { return DARKGREEN; }
    static Color SkyBlue() { return SKYBLUE; }
    static Color Blue() { return BLUE; }
    static Color DarkBlue() { return DARKBLUE; }
    static Color Purple() { return PURPLE; }
    static Color Violet() { return VIOLET; }
    static Color DarkPurple() { return DARKPURPLE; }
    static Color Beige() { return BEIGE; }
    static Color Brown() { return BROWN; }
    static Color DarkBrown() { return DARKBROWN; }
    static Color White() { return WHITE; }
    static Color Black() { return BLACK; }
    static Color Blank() { return BLANK; }
    static Color Magenta() { return MAGENTA; }
    static Color RayWhite() { return RAYWHITE; }
protected:
    void set(const ::Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

} // namespace raylib

using RColor = raylib::Color;

// #endif // RAYLIB_CPP_INCLUDE_COLOR_HPP_