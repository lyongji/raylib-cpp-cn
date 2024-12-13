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
class 颜色 : public ::Color {
public:
    颜色(const ::Color& 颜色) : ::Color{颜色.r, 颜色.g, 颜色.b, 颜色.a} {}

    颜色(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : ::Color{red, green, blue, alpha} {};

    /**
     * 黑色。
     */
    颜色() : ::Color{0, 0, 0, 255} {};

    /**
     * 从 HSV 值返回一个颜色
     */
    颜色(::Vector3 hsv) { 设(::ColorFromHSV(hsv.x, hsv.y, hsv.z)); }

    /**
     * 从 HSV 值返回一个颜色
     */
    static ::Color 从HSV生成(float 色调, float 饱和度, float 明度) { return ::ColorFromHSV(色调, 饱和度, 明度); }

    /**
     * 从十六进制值获取颜色结构
     */
    颜色(unsigned int hexValue) { 设(::GetColor(hexValue)); }

    颜色(void* srcPtr, int format) { 设(::GetPixelColor(srcPtr, format)); }

    /**
     * 返回颜色的十六进制值
     */
    int 转整数() const { return ::ColorToInt(*this); }

    /**
     * 返回颜色的十六进制值
     */
    operator int() const { return ::ColorToInt(*this); }

    std::string 转文本() const { return TextFormat("颜色(%d, %d, %d, %d)", r, g, b, a); }

    operator std::string() const { return 转文本(); }

    /**
     * 返回应用了 alpha 的颜色，alpha 的范围是 0.0f 到 1.0f
     */
    颜色 透明化(float 透明度) const { return ::Fade(*this, 透明度); }

    /**
     * 返回归一化的颜色，范围为 [0..1]
     */
    Vector4 归一化() const { return ::ColorNormalize(*this); }

    /**
     * 从归一化的值 [0..1] 返回颜色
     */
    颜色(::Vector4 normalized) { 设(::ColorFromNormalized(normalized)); }

    /**
     * 返回颜色的 HSV 值
     */
    Vector3 转HSV() const { return ::ColorToHSV(*this); }

    GETTERSETTER(unsigned char, R, r)
    GETTERSETTER(unsigned char, G, g)
    GETTERSETTER(unsigned char, B, b)
    GETTERSETTER(unsigned char, A, a)

    颜色& operator=(const ::Color& color) {
        设(color);
        return *this;
    }

    /**
     * 设置背景颜色（帧缓冲区清除颜色）
     */
    颜色& 清除背景() {
        ::ClearBackground(*this);
        return *this;
    }

    void 绘制像素(int x, int y) const { ::DrawPixel(x, y, *this); }

    /**
     * 绘制一个像素
     */
    void 绘制像素(::Vector2 位置) const { ::DrawPixelV(位置, *this); }

    /**
     * 绘制一条线
     */
    void 绘制线段(int 起点X, int 起点Y, int 终点X, int 终点Y) const { ::DrawLine(起点X, 起点Y, 终点X, 终点Y, *this); }

    /**
     * 使用向量点绘制一条线
     */
    void 绘制线段(::Vector2 起点, ::Vector2 终点) const { ::DrawLineV(起点, 终点, *this); }

    /**
     * 使用向量点绘制一条线，并指定线宽
     */
    void 绘制线段(::Vector2 起点, ::Vector2 终点, float 粗细) const { ::DrawLineEx(起点, 终点, 粗细, *this); }

    void 绘制贝塞尔线条(::Vector2 起点, ::Vector2 终点, float 粗细 = 1.0f) const {
        ::DrawLineBezier(起点, 终点, 粗细, *this);
    }

    void 绘制连续线段(::Vector2* 顶点表, int 点数) const { ::DrawLineStrip(顶点表, 点数, *this); }

    void 绘制文本(const char* 文本, int 位置X = 0, int 位置Y = 0, int 字体大小 = 10.0f) const {
        ::DrawText(文本, 位置X, 位置Y, 字体大小, *this);
    }

    void 绘制文本(const std::string& 文本, int 位置X = 0, int 位置Y = 0, int 字体大小 = 10.0f) const {
        ::DrawText(文本.c_str(), 位置X, 位置Y, 字体大小, *this);
    }

    void 绘制文本(const ::Font& 字体, const char* 文本, ::Vector2 位置, float 字体大小, float 字间距) const {
        ::DrawTextEx(字体, 文本, 位置, 字体大小, 字间距, *this);
    }

    void 绘制文本(const ::Font& 字体, const std::string& 文本, ::Vector2 位置, float 字体大小, float 字间距) const {
        ::DrawTextEx(字体, 文本.c_str(), 位置, 字体大小, 字间距, *this);
    }

    void 绘制文本(
        const ::Font& 字体,
        const char* 文本,
        ::Vector2 位置,
        ::Vector2 原点,
        float 旋转,
        float 字体大小,
        float 字间距) const {
        ::DrawTextPro(字体, 文本, 位置, 原点, 旋转, 字体大小, 字间距, *this);
    }

    void 绘制文本(
        const ::Font& 字体,
        const std::string& 文本,
        ::Vector2 位置,
        ::Vector2 原点,
        float 旋转,
        float 字体大小,
        float 字间距) const {
        ::DrawTextPro(字体, 文本.c_str(), 位置, 原点, 旋转, 字体大小, 字间距, *this);
    }

    void 绘制矩形(int 位置X, int 位置Y, int 宽, int 高) const { ::DrawRectangle(位置X, 位置Y, 宽, 高, *this); }

    void 绘制矩形(::Vector2 位置, ::Vector2 尺寸) const { ::DrawRectangleV(位置, 尺寸, *this); }

    void 绘制矩形(::Rectangle 矩形) const { ::DrawRectangleRec(矩形, *this); }

    void 绘制矩形(::Rectangle 矩形, ::Vector2 原点, float 旋转) const { ::DrawRectanglePro(矩形, 原点, 旋转, *this); }

    void 绘制矩形边框(int 位置X, int 位置Y, int 宽, int 高) const { ::DrawRectangleLines(位置X, 位置Y, 宽, 高, *this); }

    void 绘制矩形边框(::Rectangle 矩形, float 线宽) const { ::DrawRectangleLinesEx(矩形, 线宽, *this); }

    bool 是否相等(::Color 颜色) { return ::ColorIsEqual(*this, 颜色); }

    bool operator==(const ::Color& other) const { return ::ColorIsEqual(*this, other); }
    bool operator!=(const ::Color& other) const { return !::ColorIsEqual(*this, other); }

    /**
     * 获取颜色与另一个颜色相乘的结果
     */
    颜色 Tint(::Color tint) { return ::ColorTint(*this, tint); }

    /**
     * 获取颜色亮度调整后的结果，亮度因子范围为 -1.0f 到 1.0f
     */
    颜色 明度(float 明度值) { return ::ColorBrightness(*this, 明度值); }

    /**
     * 获取颜色对比度调整后的结果，对比度值范围为 -1.0f 到 1.0f
     */
    颜色 对比度(float 对比值) { return ::ColorContrast(*this, 对比值); }

    /**
     * 返回应用了 alpha 的颜色，alpha 的范围是 0.0f 到 1.0f
     */
    颜色 透明度(float 透明值) const { return ::ColorAlpha(*this, 透明值); }

    /// 返回颜色插值，参数为颜色color2和插值因子factor
    颜色 Lerp(::Color color2, float factor) { return ::ColorLerp(*this, color2, factor); }

    /**
     * 返回 src 颜色与 dst 颜色进行 alpha 混合后的结果，并应用 tint 颜色
     */
    颜色 AlphaBlend(::Color dst, ::Color tint) const { return ::ColorAlphaBlend(dst, *this, tint); }

    static 颜色 LightGray() { return LIGHTGRAY; }
    static 颜色 Gray() { return GRAY; }
    static 颜色 DarkGray() { return DARKGRAY; }
    static 颜色 Yellow() { return YELLOW; }
    static 颜色 Gold() { return GOLD; }
    static 颜色 Orange() { return ORANGE; }
    static 颜色 Pink() { return PINK; }
    static 颜色 Red() { return RED; }
    static 颜色 Maroon() { return MAROON; }
    static 颜色 Green() { return GREEN; }
    static 颜色 Lime() { return LIME; }
    static 颜色 DarkGreen() { return DARKGREEN; }
    static 颜色 SkyBlue() { return SKYBLUE; }
    static 颜色 Blue() { return BLUE; }
    static 颜色 DarkBlue() { return DARKBLUE; }
    static 颜色 Purple() { return PURPLE; }
    static 颜色 Violet() { return VIOLET; }
    static 颜色 DarkPurple() { return DARKPURPLE; }
    static 颜色 Beige() { return BEIGE; }
    static 颜色 Brown() { return BROWN; }
    static 颜色 DarkBrown() { return DARKBROWN; }
    static 颜色 White() { return WHITE; }
    static 颜色 Black() { return BLACK; }
    static 颜色 Blank() { return BLANK; }
    static 颜色 Magenta() { return MAGENTA; }
    static 颜色 RayWhite() { return RAYWHITE; }
protected:
    void 设(const ::Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

} // namespace raylib

using RColor = raylib::颜色;

// #endif // RAYLIB_CPP_INCLUDE_COLOR_HPP_