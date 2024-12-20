// #ifndef RAYLIB_CPP_INCLUDE_FONT_HPP_
// #define RAYLIB_CPP_INCLUDE_FONT_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./TextureUnmanaged.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 字体类型，包含纹理和字符集数组数据
 */
class Font : public ::Font {
public:
    Font(
        int baseSize,
        int glyphCount,
        int glyphPadding,
        ::Texture2D texture,
        ::Rectangle* recs = nullptr,
        ::GlyphInfo* glyphs = nullptr)
        : ::Font{baseSize, glyphCount, glyphPadding, texture, recs, glyphs} {
        // 无操作
    }

    /**
     * 获取默认字体
     */
    Font() : ::Font(::GetFontDefault()) { }

    Font(const ::Font& font) : ::Font(font) { }

    /**
     * 从指定文件加载字体
     *
     * @param fileName 要加载的字体文件名
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     */
    Font(const std::string& fileName) { Load(fileName); }

    /**
     * 从指定文件加载字体，并带有生成参数
     *
     * @param fileName 要加载的字体文件名
     * @param fontSize 字体的期望大小
     * @param fontChars 字体字符数组
     * @param charCount 字符数量
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     *
     * @see ::LoadFontEx
     */
    Font(const std::string& fileName, int fontSize, int* fontChars = 0, int charCount = 0) {
        Load(fileName, fontSize, fontChars, charCount);
    }

    /**
     * 从指定图像加载字体，并带有颜色键
     *
     * @param image 要加载字体的图像
     * @param key 颜色键
     * @param firstChar 第一个字符
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     *
     * @see ::LoadFontFromImage()
     */
    Font(const ::Image& image, ::Color key, int firstChar) { Load(image, key, firstChar); }

    /**
     * 从内存加载字体，基于给定的文件类型和文件数据
     *
     * @param fileType 文件类型
     * @param fileData 文件数据
     * @param dataSize 数据大小
     * @param fontSize 字体大小
     * @param fontChars 字体字符数组
     * @param charsCount 字符数量
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     *
     * @see ::LoadFontFromMemory()
     */
    Font(
        const std::string& fileType,
        const unsigned char* fileData,
        int dataSize,
        int fontSize,
        int* fontChars,
        int charsCount) {
        Load(fileType, fileData, dataSize, fontSize, fontChars, charsCount);
    }

    Font(const Font&) = delete;

    Font(Font&& other) noexcept {
        set(other);

        other.baseSize = 0;
        other.glyphCount = 0;
        other.glyphPadding = 0;
        other.texture = {};
        other.recs = nullptr;
        other.glyphs = nullptr;
    }

    ~Font() { Unload(); }

    void Unload() {
        // 防止多次调用 UnloadFont()
        if (baseSize != 0) {
            UnloadFont(*this);
            baseSize = 0;
        }
    }

    GETTER(int, BaseSize, baseSize)
    GETTER(int, GlyphCount, glyphCount)
    GETTER(int, GlyphPadding, glyphPadding)
    GETTER(::Rectangle*, Recs, recs)
    GETTER(::GlyphInfo*, Glyphs, glyphs)

    /**
     * 获取包含字形的纹理图集
     */
    TextureUnmanaged GetTexture() { return texture; }

    /**
     * 设置包含字形的纹理图集
     */
    void SetTexture(const ::Texture& newTexture) { texture = newTexture; }

    Font& operator=(const ::Font& font) {
        Unload();
        set(font);
        return *this;
    }

    Font& operator=(const Font&) = delete;

    Font& operator=(Font&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.baseSize = 0;
        other.glyphCount = 0;
        other.glyphPadding = 0;
        other.texture = {};
        other.recs = nullptr;
        other.glyphs = nullptr;

        return *this;
    }

    /**
     * 从指定文件加载字体
     *
     * @param fileName 要加载的字体文件名
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     *
     * @see ::LoadFont()
     */
    void Load(const std::string& fileName) {
        set(::LoadFont(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("Failed to load Font with from file: " + fileName);
        }
    }

    /**
     * 从指定文件加载字体，并带有生成参数
     *
     * @param fileName 要加载的字体文件名
     * @param fontSize 字体的期望大小
     * @param fontChars 字体字符数组
     * @param charCount 字符数量
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     *
     * @see ::LoadFontEx()
     */
    void Load(const std::string& fileName, int fontSize, int* fontChars, int charCount) {
        set(::LoadFontEx(fileName.c_str(), fontSize, fontChars, charCount));
        if (!IsValid()) {
            throw RaylibException("Failed to load Font with from file with font size: " + fileName);
        }
    }

    void Load(const ::Image& image, ::Color key, int firstChar) {
        set(::LoadFontFromImage(image, key, firstChar));
        if (!IsValid()) {
            throw RaylibException("Failed to load Font with from image");
        }
    }

    void Load(
        const std::string& fileType,
        const unsigned char* fileData,
        int dataSize,
        int fontSize,
        int* fontChars,
        int charsCount) {
        set(::LoadFontFromMemory(fileType.c_str(), fileData, dataSize, fontSize, fontChars, charsCount));
        if (!IsValid()) {
            throw RaylibException("Failed to load Font " + fileType + " with from file data");
        }
    }

    /**
     * 返回字体是否准备好使用
     */
    [[nodiscard]] bool IsValid() const { return ::IsFontValid(*this); }

    /**
     * 使用字体和附加参数绘制文本
     */
    void DrawText(const char* text, ::Vector2 position, float fontSize, float spacing, ::Color tint = WHITE) const {
        ::DrawTextEx(*this, text, position, fontSize, spacing, tint);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void
    DrawText(const std::string& text, ::Vector2 position, float fontSize, float spacing, ::Color tint = WHITE) const {
        ::DrawTextEx(*this, text.c_str(), position, fontSize, spacing, tint);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void DrawText(const char* text, int posX, int posY, float fontSize, float spacing, ::Color tint = WHITE) const {
        ::DrawTextEx(*this, text, {static_cast<float>(posX), static_cast<float>(posY)}, fontSize, spacing, tint);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void
    DrawText(const std::string& text, int posX, int posY, float fontSize, float spacing, ::Color tint = WHITE) const {
        ::DrawTextEx(
            *this,
            text.c_str(),
            {static_cast<float>(posX), static_cast<float>(posY)},
            fontSize,
            spacing,
            tint);
    }

    void DrawText(
        const char* text,
        ::Vector2 position,
        ::Vector2 origin,
        float rotation,
        float fontSize,
        float spacing,
        ::Color tint = WHITE) const {
        ::DrawTextPro(*this, text, position, origin, rotation, fontSize, spacing, tint);
    }

    void DrawText(
        const std::string& text,
        ::Vector2 position,
        ::Vector2 origin,
        float rotation,
        float fontSize,
        float spacing,
        ::Color tint = WHITE) const {
        ::DrawTextPro(*this, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
    }

    /**
     * 绘制单个字符（码点）
     */
    void DrawText(int codepoint, ::Vector2 position, float fontSize, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTextCodepoint(*this, codepoint, position, fontSize, tint);
    }

    /**
     * 绘制多个字符（码点）
     */
    void DrawText(
        const int* codepoints,
        int count,
        ::Vector2 position,
        float fontSize,
        float spacing,
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTextCodepoints(*this, codepoints, count, position, fontSize, spacing, tint);
    }

    /**
     * 测量字符串大小（用于字体）
     */
    [[nodiscard]] Vector2 MeasureText(const char* text, float fontSize, float spacing) const {
        return ::MeasureTextEx(*this, text, fontSize, spacing);
    }

    /**
     * 测量字符串大小（用于字体）
     */
    [[nodiscard]] Vector2 MeasureText(const std::string& text, float fontSize, float spacing) const {
        return ::MeasureTextEx(*this, text.c_str(), fontSize, spacing);
    }

    /**
     * 获取字体中 Unicode 字符的索引位置
     */
    [[nodiscard]] int GetGlyphIndex(int character) const { return ::GetGlyphIndex(*this, character); }

    /**
     * 从文本创建图像（自定义精灵字体）
     */
    [[nodiscard]] ::Image ImageText(const char* text, float fontSize, float spacing, ::Color tint) const {
        return ::ImageTextEx(*this, text, fontSize, spacing, tint);
    }

    /**
     * 从文本创建图像（自定义精灵字体）
     */
    [[nodiscard]] ::Image ImageText(const std::string& text, float fontSize, float spacing, ::Color tint) const {
        return ::ImageTextEx(*this, text.c_str(), fontSize, spacing, tint);
    }
protected:
    void set(const ::Font& font) {
        baseSize = font.baseSize;
        glyphCount = font.glyphCount;
        glyphPadding = font.glyphPadding;
        texture = font.texture;
        recs = font.recs;
        glyphs = font.glyphs;
    }
};
} // namespace raylib

using RFont = raylib::Font;

// #endif // RAYLIB_CPP_INCLUDE_FONT_HPP_