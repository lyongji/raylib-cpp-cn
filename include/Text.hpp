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
class Text {
public:
    /**
     * 内部文本。
     */
    std::string text;

    /**
     * 文本的大小。
     */
    float fontSize;

    /**
     * 文本的颜色。
     */
    ::Color color;

    /**
     * 用于文本的内部 raylib 字体。
     */
    ::Font font;

    /**
     * 文本的字符间距。
     */
    float spacing;

    /**
     * 初始化一个新的 Text 对象。
     *
     * @param text 初始化的文本。
     * @param fontSize 文本的大小。
     * @param color 字体的颜色。
     * @param font 初始化的字体。
     * @param spacing 文本的间距。
     */
    Text(
        const std::string& text = "",
        float fontSize = 10,
        const ::Color& color = WHITE,
        const ::Font& font = ::GetFontDefault(),
        float spacing = 0)
        : text(text)
        , fontSize(fontSize)
        , color(color)
        , font(font)
        , spacing(spacing) {
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
    Text(
        const ::Font& font,
        const std::string& text = "",
        float fontSize = 10,
        float spacing = 0,
        const ::Color& color = WHITE)
        : text(text)
        , fontSize(fontSize)
        , color(color)
        , font(font)
        , spacing(spacing) {
        // 无操作。
    }

    GETTERSETTER(const std::string&, Text, text)
    GETTERSETTER(float, FontSize, fontSize)
    GETTERSETTER(::Font, Font, font)
    GETTERSETTER(::Color, Color, color)
    GETTERSETTER(float, Spacing, spacing)

    /**
     * 使用类中的值绘制文本。
     */
    void Draw(const ::Vector2& position) const { ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color); }

    /**
     * 使用类中的值绘制文本。
     */
    void Draw(int posX, int posY) const {
        ::DrawTextEx(
            font,
            text.c_str(),
            {static_cast<float>(posX), static_cast<float>(posY)},
            fontSize,
            spacing,
            color);
    }

    /**
     * 使用 Font 和高级参数（旋转）绘制文本。
     *
     * @see DrawTextPro()
     */
    void Draw(const ::Vector2& position, float rotation, const ::Vector2& origin = {0, 0}) const {
        ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, color);
    }

    /**
     * 测量默认字体字符串的宽度。
     */
    [[nodiscard]] int Measure() const { return ::MeasureText(text.c_str(), static_cast<int>(fontSize)); }

    /**
     * 测量 Font 字符串的大小。
     */
    [[nodiscard]] Vector2 MeasureEx() const { return ::MeasureTextEx(font, text.c_str(), fontSize, spacing); }

    Text& operator=(const Text& other) {
        if (this == &other) {
            return *this;
        }

        text = other.text;
        fontSize = other.fontSize;
        color = other.color;
        font = other.font;
        spacing = other.spacing;

        return *this;
    }

    /**
     * 使用字体和颜色绘制文本。
     *
     * @see ::DrawText
     */
    static void
    Draw(const std::string& text, const int posX, const int posY, const int fontSize, const ::Color& color) {
        ::DrawText(text.c_str(), posX, posY, fontSize, color);
    }

    /**
     * 使用字体和颜色绘制文本，位置定义为 Vector2。
     *
     * @see ::DrawText
     */
    static void Draw(const std::string& text, const ::Vector2& pos, const int fontSize, const ::Color& color) {
        ::DrawText(text.c_str(), static_cast<int>(pos.x), static_cast<int>(pos.y), fontSize, color);
    }

    /**
     * 使用字体、颜色、位置、字体大小和间距绘制文本。
     *
     * @see ::DrawTextEx
     */
    static void Draw(
        const ::Font& font,
        const std::string& text,
        const ::Vector2& position,
        const float fontSize,
        const float spacing,
        const ::Color& color) {
        ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
    }

    /**
     * 使用字体、颜色、位置、原点、字体大小和间距绘制文本。
     *
     * @see ::DrawTextPro
     */
    static void Draw(
        const ::Font& font,
        const std::string& text,
        const ::Vector2& position,
        const ::Vector2& origin,
        const float rotation,
        const float fontSize,
        const float spacing,
        const ::Color& color) {
        ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, color);
    }
};
} // namespace raylib

using RText = raylib::Text;

// #endif // RAYLIB_CPP_INCLUDE_TEXT_HPP_