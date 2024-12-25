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
    颜色(unsigned int hex值) : ::Color(::GetColor(hex值)) {}

    颜色(void* 源指针, int 格式) : ::Color(::GetPixelColor(源指针, 格式)) {}

    /**
     * 返回颜色的十六进制值
     */
    [[nodiscard]] int 转整数() const { return ::ColorToInt(*this); }

    /**
     * 返回颜色的十六进制值
     */
    explicit operator int() const { return ::ColorToInt(*this); }

    [[nodiscard]] std::string 转文本() const { return TextFormat("颜色(%d, %d, %d, %d)", r, g, b, a); }

    explicit operator std::string() const { return 转文本(); }

    /**
     * 返回应用了 alpha 的颜色，alpha 的范围是 0.0f 到 1.0f
     */
    [[nodiscard]] 颜色 透明化(float 透明度) const { return ::Fade(*this, 透明度); }

    /**
     * 返回归一化的颜色，范围为 [0..1]
     */
    [[nodiscard]] Vector4 归一化() const { return ::ColorNormalize(*this); }

    /**
     * 从归一化的值 [0..1] 返回颜色
     */
    explicit 颜色(::Vector4 归一化) : Color(::ColorFromNormalized(归一化)) {}

    /**
     * 返回颜色的 HSV 值
     */
    [[nodiscard]] Vector3 转HSV() const { return ::ColorToHSV(*this); }


    GETTERSETTER(unsigned char, R, r)
    GETTERSETTER(unsigned char, G, g)
    GETTERSETTER(unsigned char, B, b)
    GETTERSETTER(unsigned char, A, a)

    颜色& operator=(const ::Color& 颜色) {
        设(颜色);
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

    bool 是相等(::Color 颜色) { return ::ColorIsEqual(*this, 颜色); }

    bool operator==(const ::Color& other) const { return ::ColorIsEqual(*this, other); }
    bool operator!=(const ::Color& other) const { return !::ColorIsEqual(*this, other); }

    /**
     * 获取颜色与另一个颜色相乘的结果
     */
    颜色 色调(::Color 色调) { return ::ColorTint(*this, 色调); }

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
    [[nodiscard]] 颜色 透明度(float 透明值) const { return ::ColorAlpha(*this, 透明值); }

    /// 返回颜色插值，参数为颜色color2和插值因子factor
    颜色 插值(::Color 颜色2, float 系数) { return ::ColorLerp(*this, 颜色2, 系数); }

    /**
     * 返回 src 颜色与 dst 颜色进行 alpha 混合后的结果，并应用色调颜色
     */
    [[nodiscard]] 颜色 透明混合(::Color 目标, ::Color 色调) const { return ::ColorAlphaBlend(目标, *this, 色调); }
    ///raylib默认色
    static 颜色 浅灰() { return LIGHTGRAY; }
    static 颜色 灰() { return GRAY; }
    static 颜色 深灰() { return DARKGRAY; }
    static 颜色 黄() { return YELLOW; }
    static 颜色 金() { return GOLD; }
    static 颜色 橙() { return ORANGE; }
    static 颜色 粉() { return PINK; }
    static 颜色 红() { return RED; }
    static 颜色 栗() { return MAROON; }
    static 颜色 绿() { return GREEN; }
    static 颜色 草绿() { return LIME; }
    static 颜色 深绿() { return DARKGREEN; }
    static 颜色 天蓝() { return SKYBLUE; }
    static 颜色 蓝() { return BLUE; }
    static 颜色 深蓝() { return DARKBLUE; }
    static 颜色 紫() { return PURPLE; }
    static 颜色 堇紫() { return VIOLET; }
    static 颜色 深紫() { return DARKPURPLE; }
    static 颜色 米黄() { return BEIGE; }
    static 颜色 褐() { return BROWN; }
    static 颜色 深褐() { return DARKBROWN; }
    static 颜色 白() { return WHITE; }
    static 颜色 黑() { return BLACK; }
    static 颜色 空() { return BLANK; }
    static 颜色 品红() { return MAGENTA; }
    static 颜色 白烟() { return RAYWHITE; }
    /// 增加中国传统颜色 https://colors.ichuantong.cn/
    /// 金银
    static 颜色 赤金() { return {242, 190, 69}; } /// HEX: #f2be45
    static 颜色 金色() { return {234, 205, 118}; } /// HEX: #eacd76
    static 颜色 银白() { return {233, 231, 239}; } /// HEX: #e9e7ef
    static 颜色 老银() { return {186, 202, 198}; } /// HEX: #bacac6
    static 颜色 乌金() { return {167, 142, 68}; } /// HEX: #a78e44
    static 颜色 铜绿() { return {84, 150, 136}; } /// HEX: #549688
    /// 黑
    static 颜色 玄色() { return {98, 42, 29}; } /// HEX: #622a1d
    static 颜色 玄青() { return {61, 59, 79}; } /// HEX: #3d3b4f
    static 颜色 乌色() { return {114, 94, 130}; } /// HEX: #725e82
    static 颜色 乌黑() { return {57, 47, 65}; } /// HEX: #392f41
    static 颜色 漆黑() { return {22, 24, 35}; } /// HEX: #161823
    static 颜色 墨色() { return {80, 97, 109}; } /// HEX: #50616d
    static 颜色 墨灰() { return {117, 138, 153}; } /// HEX: #758a99
    static 颜色 缁色() { return {73, 49, 49}; } /// HEX: #493131 zi色
    static 颜色 煤黑() { return {49, 37, 32}; } /// HEX: #312520
    static 颜色 黧() { return {93, 81, 60}; } /// HEX: #5d513c li色
    static 颜色 黎() { return {117, 102, 77}; } /// HEX: #75664d
    static 颜色 黝() { return {107, 104, 130}; } /// HEX: #6b6882
    static 颜色 黝黑() { return {107, 87, 87}; } /// HEX: #665757
    static 颜色 黯() { return {65, 85, 93}; } /// HEX: #41555d
    /// 灰白
    static 颜色 精白() { return {255, 255, 255}; } /// HEX: #ffffff
    static 颜色 象牙白() { return {255, 251, 240}; } /// HEX: #fffbf0
    static 颜色 雪白() { return {242, 253, 255}; } /// HEX: #f2fdff
    static 颜色 月白() { return {214, 236, 240}; } /// HEX: #d6ecf0
    static 颜色 缟() { return {242, 236, 222}; } /// HEX: #f2ecde
    static 颜色 素() { return {224, 240, 233}; } /// HEX: #e0f0e9
    static 颜色 茶白() { return {243, 249, 241}; } /// HEX: #f3f9f1
    static 颜色 霜色() { return {233, 241, 246}; } /// HEX: #e9f1f6
    static 颜色 花白() { return {194, 204, 208}; } /// HEX: #c2ccd0
    static 颜色 鱼肚白() { return {252, 239, 232}; } /// HEX: #fcefe8
    static 颜色 荧白() { return {227, 249, 253}; } /// HEX: #e3f9fd
    static 颜色 灰色() { return {128, 128, 128}; } /// HEX: #808080
    static 颜色 牙色() { return {238, 222, 176}; } /// HEX: #eedeb0
    static 颜色 铅白() { return {240, 240, 244}; } /// HEX: #f0f0f4
    ///水
    static 颜色 水色() { return {136, 173, 166}; } /// HEX: #88ada6
    static 颜色 水红() { return {243, 211, 231}; } /// HEX: #f3d3e7
    static 颜色 水绿() { return {212, 242, 231}; } /// HEX: #d4f2e7
    static 颜色 水蓝() { return {210, 240, 244}; } /// HEX: #d2f0f4
    static 颜色 淡青() { return {211, 224, 243}; } /// HEX: #d3e0f3
    static 颜色 湖蓝() { return {48, 223, 243}; } /// HEX: #30dff3
    static 颜色 湖绿() { return {37, 248, 203}; } /// HEX: #25f8cb
    /// 苍
    static 颜色 苍色() { return {117, 135, 138}; } /// HEX: #75878a
    static 颜色 苍翠() { return {81, 154, 115}; } /// HEX: #519a73
    static 颜色 苍黄() { return {162, 155, 124}; } /// HEX: #a29b7c
    static 颜色 苍青() { return {115, 151, 171}; } /// HEX: #7397ab
    static 颜色 苍黑() { return {57, 82, 96}; } /// HEX: #395260
    static 颜色 苍白() { return {209, 217, 224}; } /// HEX: #d1d9e0
    /// 蓝
    static 颜色 蓝色() { return {68, 206, 246}; } /// HEX: #44cef6
    static 颜色 靛青() { return {23, 124, 176}; } /// HEX: #177cb0
    static 颜色 靛蓝() { return {6, 82, 121}; } /// HEX: #065279
protected:
    void 设(const ::Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

} // namespace raylib

using R颜色 = raylib::颜色;

// #endif // RAYLIB_CPP_INCLUDE_COLOR_HPP_