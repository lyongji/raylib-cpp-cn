// #ifndef RAYLIB_CPP_INCLUDE_TEXT_HPP_
// #define RAYLIB_CPP_INCLUDE_TEXT_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 文本函数。
 */
class 文本 {
public:
    /**
     * 内部文本。
     */
    std::string 全文;

    /**
     * 文本的大小。
     */
    float 字体大小;

    /**
     * 文本的颜色。
     */
    ::Color 颜色;

    /**
     * 用于文本的内部 raylib 字体。
     */
    ::Font 字体;

    /**
     * 文本的字符间距。
     */
    float 间距;

    /**
     * 初始化一个新的 Text 对象。
     *
     * @param text 初始化的文本。
     * @param fontSize 文本的大小。
     * @param color 字体的颜色。
     * @param font 初始化的字体。
     * @param spacing 文本的间距。
     */
    文本(
        const std::string& 正文 = "",
        float 字体大小 = 10,
        const ::Color& 颜色 = WHITE,
        const ::Font& 字体 = ::GetFontDefault(),
        float 间距 = 0)
        : 全文(正文)
        , 字体大小(字体大小)
        , 颜色(颜色)
        , 字体(字体)
        , 间距(间距) {
        // 无操作。
    }

    /**
     * 使用自定义字体初始化一个新的 Text 对象。
     *
     * @param font 初始化的字体。
     * @param text 初始化的文本。
     * @param fontSize 文本的大小。
     * @param spacing 文本的间距。
     * @param color 字体的颜色。
     */
    文本(
        const ::Font& 字体,
        const std::string& 正文 = "",
        float 字体大小 = 10,
        float 间距 = 0,
        const ::Color& 颜色 = WHITE)
        : 全文(正文)
        , 字体大小(字体大小)
        , 颜色(颜色)
        , 字体(字体)
        , 间距(间距) {
        // 无操作。
    }

    GETTERSETTER(const std::string&, 全文, 全文)
    GETTERSETTER(float, 字体大小, 字体大小)
    GETTERSETTER(::Font, 字体, 字体)
    GETTERSETTER(::Color, 颜色, 颜色)
    GETTERSETTER(float, 间距, 间距)

    /**
     * 使用类中的值绘制文本。
     */
    void 绘制(const ::Vector2& 位置) const { ::DrawTextEx(字体, 全文.c_str(), 位置, 字体大小, 间距, 颜色); }

    /**
     * 使用类中的值绘制文本。
     */
    void 绘制(int 位置X, int 位置Y) const {
        ::DrawTextEx(字体, 全文.c_str(), {static_cast<float>(位置X), static_cast<float>(位置Y)}, 字体大小, 间距, 颜色);
    }

    /**
     * 使用 Font 和高级参数（旋转）绘制文本。
     *
     * @see DrawTextPro()
     */
    void 绘制(const ::Vector2& 位置, float 旋转, const ::Vector2& 原点 = {0, 0}) const {
        ::DrawTextPro(字体, 全文.c_str(), 位置, 原点, 旋转, 字体大小, 间距, 颜色);
    }

    /**
     * 测量默认字体字符串的宽度。
     */
    [[nodiscard]] int 测量() const { return ::MeasureText(全文.c_str(), static_cast<int>(字体大小)); }

    /**
     * 测量 Font 字符串的大小。
     */
    [[nodiscard]] Vector2 测量扩展() const { return ::MeasureTextEx(字体, 全文.c_str(), 字体大小, 间距); }

    文本& operator=(const 文本& other) {
        if (this == &other) {
            return *this;
        }

        全文 = other.全文;
        字体大小 = other.字体大小;
        颜色 = other.颜色;
        字体 = other.字体;
        间距 = other.间距;

        return *this;
    }

    /**
     * 使用字体和颜色绘制文本。
     *
     * @see ::DrawText
     */
    static void
    绘制(const std::string& 正文, const int 位置X, const int 位置Y, const int 字体大小, const ::Color& 颜色) {
        ::DrawText(正文.c_str(), 位置X, 位置Y, 字体大小, 颜色);
    }

    /**
     * 使用字体和颜色绘制文本，位置定义为 Vector2。
     *
     * @see ::DrawText
     */
    static void 绘制(const std::string& 正文, const ::Vector2& 位置, const int 字体大小, const ::Color& 颜色) {
        ::DrawText(正文.c_str(), static_cast<int>(位置.x), static_cast<int>(位置.y), 字体大小, 颜色);
    }

    /**
     * 使用字体、颜色、位置、字体大小和间距绘制文本。
     *
     * @see ::DrawTextEx
     */
    static void 绘制(
        const ::Font& 字体,
        const std::string& 正文,
        const ::Vector2& 位置,
        const float 字体大小,
        const float 间距,
        const ::Color& 颜色) {
        ::DrawTextEx(字体, 正文.c_str(), 位置, 字体大小, 间距, 颜色);
    }

    /**
     * 使用字体、颜色、位置、原点、字体大小和间距绘制文本。
     *
     * @see ::DrawTextPro
     */
    static void 绘制(
        const ::Font& 字体,
        const std::string& 正文,
        const ::Vector2& 位置,
        const ::Vector2& 原点,
        const float 旋转,
        const float 字体大小,
        const float 间距,
        const ::Color& 颜色) {
        ::DrawTextPro(字体, 正文.c_str(), 位置, 原点, 旋转, 字体大小, 间距, 颜色);
    }
};
} // namespace raylib

using R文本 = raylib::文本;

// #endif // RAYLIB_CPP_INCLUDE_TEXT_HPP_