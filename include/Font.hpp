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
class 字体 : public ::Font {
public:
    字体(
        int 基本大小,
        int 字符数量,
        int 字符间距,
        ::Texture2D 纹理,
        ::Rectangle* 矩形区域 = nullptr,
        ::GlyphInfo* 字形信息 = nullptr)
        : ::Font{基本大小, 字符数量, 字符间距, 纹理, 矩形区域, 字形信息} {
        // 无操作
    }

    /**
     * 获取默认字体
     */
    字体() { 设(::GetFontDefault()); }

    字体(const ::Font& 字体) { 设(字体); }

    /**
     * 从指定文件加载字体
     *
     * @param fileName 要加载的字体文件名
     *
     * @throws raylib::RaylibException 如果字体初始化失败则抛出异常
     */
    字体(const std::string& 文件名) { 加载(文件名); }

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
    字体(const std::string& 文件名, int 字体大小, int* 字体字符组 = 0, int 字符数量 = 0) {
        加载(文件名, 字体大小, 字体字符组, 字符数量);
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
    字体(const ::Image& 图像, ::Color 色键, int 首字符) { 加载(图像, 色键, 首字符); }

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
    字体(
        const std::string& 文件类型,
        const unsigned char* 文件数据,
        int 数据大小,
        int 字体大小,
        int* 字体字符组,
        int 字符数量) {
        加载(文件类型, 文件数据, 数据大小, 字体大小, 字体字符组, 字符数量);
    }

    字体(const 字体&) = delete;

    字体(字体&& other) {
        设(other);

        other.baseSize = 0;
        other.glyphCount = 0;
        other.glyphPadding = 0;
        other.texture = {};
        other.recs = nullptr;
        other.glyphs = nullptr;
    }

    ~字体() { 卸载(); }

    void 卸载() {
        // 防止多次调用 UnloadFont()
        if (baseSize != 0) {
            UnloadFont(*this);
            baseSize = 0;
        }
    }

    GETTER(int, 基本大小, baseSize)
    GETTER(int, 字符数量, glyphCount)
    GETTER(int, 字符间距, glyphPadding)
    GETTER(::Rectangle*, 矩形区域, recs)
    GETTER(::GlyphInfo*, 字形信息, glyphs)

    /**
     * 获取包含字形的纹理图集
     */
    TextureUnmanaged 取纹理() { return texture; }

    /**
     * 设置包含字形的纹理图集
     */
    void 设纹理(const ::Texture& 新纹理) { texture = 新纹理; }

    字体& operator=(const ::Font& 字体) {
        卸载();
        设(字体);
        return *this;
    }

    字体& operator=(const 字体&) = delete;

    字体& operator=(字体&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

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
    void 加载(const std::string& 文件名) {
        设(::LoadFont(文件名.c_str()));
        if (!是就绪()) {
            throw Raylib异常("无法从文件加载字体：" + 文件名);
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
    void 加载(const std::string& 文件名, int 字体大小, int* 字体字符组, int 字符数量) {
        设(::LoadFontEx(文件名.c_str(), 字体大小, 字体字符组, 字符数量));
        if (!是就绪()) {
            throw Raylib异常("Failed to load Font with from file with font size: " + 文件名);
        }
    }

    void 加载(const ::Image& 图像, ::Color 颜色键, int 首字符) {
        设(::LoadFontFromImage(图像, 颜色键, 首字符));
        if (!是就绪()) {
            throw Raylib异常("无法从图像加载字体");
        }
    }

    void 加载(
        const std::string& 文件类型,
        const unsigned char* 文件数据,
        int 数据大小,
        int 字体大小,
        int* 字体字符组,
        int 字符数量) {
        设(::LoadFontFromMemory(文件类型.c_str(), 文件数据, 数据大小, 字体大小, 字体字符组, 字符数量));
        if (!是就绪()) {
            throw Raylib异常("无法使用文件数据加载:" + 文件类型 + " 字体");
        }
    }

    /**
     * 返回字体是否准备好使用
     */
    bool 是就绪() const { return ::IsFontValid(*this); }

    /**
     * 使用字体和附加参数绘制文本
     */
    void 绘制文本(const char* 文本, ::Vector2 位置, float 字体大小, float 间距, ::Color 色调 = WHITE) const {
        ::DrawTextEx(*this, 文本, 位置, 字体大小, 间距, 色调);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void 绘制文本(const std::string& 文本, ::Vector2 位置, float 字体大小, float 间距, ::Color 色调 = WHITE) const {
        ::DrawTextEx(*this, 文本.c_str(), 位置, 字体大小, 间距, 色调);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void 绘制文本(const char* 文本, int 位置X, int 位置Y, float 字体大小, float 间距, ::Color 色调 = WHITE) const {
        ::DrawTextEx(*this, 文本, {static_cast<float>(位置X), static_cast<float>(位置Y)}, 字体大小, 间距, 色调);
    }

    /**
     * 使用字体和附加参数绘制文本
     */
    void
    绘制文本(const std::string& 文本, int 位置X, int 位置Y, float 字体大小, float 间距, ::Color 色调 = WHITE) const {
        ::DrawTextEx(*this, 文本.c_str(), {static_cast<float>(位置X), static_cast<float>(位置Y)}, 字体大小, 间距, 色调);
    }

    void 绘制文本(
        const char* 文本,
        ::Vector2 位置,
        ::Vector2 原点,
        float 旋转,
        float 字体大小,
        float 间距,
        ::Color 色调 = WHITE) const {
        ::DrawTextPro(*this, 文本, 位置, 原点, 旋转, 字体大小, 间距, 色调);
    }

    void 绘制文本(
        const std::string& 文本,
        ::Vector2 位置,
        ::Vector2 原点,
        float 旋转,
        float 字体大小,
        float 间距,
        ::Color 色调 = WHITE) const {
        ::DrawTextPro(*this, 文本.c_str(), 位置, 原点, 旋转, 字体大小, 间距, 色调);
    }

    /**
     * 绘制单个字符（码点）字符编码术语中，码位或称编码位置，即英文的code point或code position
     */
    void 绘制文本(int 码位, ::Vector2 位置, float 字体大小, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTextCodepoint(*this, 码位, 位置, 字体大小, 色调);
    }

    /**
     * 绘制多个字符（码点）
     */
    void
    绘制文本(const int* 码位, int 数目, ::Vector2 位置, float 字体大小, float 间距, ::Color 色调 = {255, 255, 255, 255})
        const {
        ::DrawTextCodepoints(*this, 码位, 数目, 位置, 字体大小, 间距, 色调);
    }

    /**
     * 测量字符串大小（用于字体）
     */
    Vector2 测量文本(const char* 文本, float 字体大小, float 间距) const {
        return ::MeasureTextEx(*this, 文本, 字体大小, 间距);
    }

    /**
     * 测量字符串大小（用于字体）
     */
    Vector2 测量文本(const std::string& 文本, float 字体大小, float 间距) const {
        return ::MeasureTextEx(*this, 文本.c_str(), 字体大小, 间距);
    }

    /**
     * 获取字体中 Unicode 字符的索引位置
     */
    int 取字符索引(int 字符) const { return ::GetGlyphIndex(*this, 字符); }

    /**
     * 从文本创建图像（自定义精灵字体）
     */
    ::Image 从文本生图(const char* 文本, float 字体大小, float 间距, ::Color 色调) const {
        return ::ImageTextEx(*this, 文本, 字体大小, 间距, 色调);
    }

    /**
     * 从文本创建图像（自定义精灵字体）
     */
    ::Image 从文本生图(const std::string& 文本, float 字体大小, float 间距, ::Color 色调) const {
        return ::ImageTextEx(*this, 文本.c_str(), 字体大小, 间距, 色调);
    }
protected:
    void 设(const ::Font& font) {
        baseSize = font.baseSize;
        glyphCount = font.glyphCount;
        glyphPadding = font.glyphPadding;
        texture = font.texture;
        recs = font.recs;
        glyphs = font.glyphs;
    }
};
} // namespace raylib

using R字体 = raylib::字体;

// #endif // RAYLIB_CPP_INCLUDE_FONT_HPP_