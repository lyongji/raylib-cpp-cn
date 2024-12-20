// #ifndef RAYLIB_CPP_INCLUDE_IMAGE_HPP_
// #define RAYLIB_CPP_INCLUDE_IMAGE_HPP_
#pragma once

#include <string>

#include "./Color.hpp"
#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 图像类型，bpp 始终为 RGBA（32 位）
 *
 * 数据存储在 CPU 内存（RAM）中
 */
class Image : public ::Image {
public:
    Image(
        void* data = nullptr,
        int width = 0,
        int height = 0,
        int mipmaps = 1,
        int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        : ::Image{data, width, height, mipmaps, format} {
        // 无操作
    }

    Image(const ::Image& image) : ::Image(image) { }

    /**
     * 从给定文件加载图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see Load()
     */
    Image(const std::string& fileName) { Load(fileName); }

    /**
     * 从给定文件加载原始图像，带有提供的宽度、高度和格式。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see LoadRaw()
     */
    Image(const std::string& fileName, int width, int height, int format, int headerSize = 0) {
        Load(fileName, width, height, format, headerSize);
    }

    /**
     * 从给定文件加载动画图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see LoadAnim()
     */
    Image(const std::string& fileName, int* frames) { Load(fileName, frames); }

    /**
     * 从给定文件加载图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     */
    Image(const std::string& fileType, const unsigned char* fileData, int dataSize) {
        Load(fileType, fileData, dataSize);
    }

    /**
     * 从给定文件加载图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     */
    Image(const ::Texture2D& texture) { Load(texture); }

    Image(int width, int height, ::Color color = {255, 255, 255, 255}) { set(::GenImageColor(width, height, color)); }

    Image(const std::string& text, int fontSize, ::Color color = {255, 255, 255, 255}) {
        set(::ImageText(text.c_str(), fontSize, color));
    }

    Image(
        const ::Font& font,
        const std::string& text,
        float fontSize,
        float spacing,
        ::Color tint = {255, 255, 255, 255}) {
        set(::ImageTextEx(font, text.c_str(), fontSize, spacing, tint));
    }

    Image(const Image& other) { set(other.Copy()); }

    Image(Image&& other) noexcept {
        set(other);

        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;
    }

    static ::Image Text(const std::string& text, int fontSize, ::Color color = {255, 255, 255, 255}) {
        return ::ImageText(text.c_str(), fontSize, color);
    }

    static ::Image Text(
        const ::Font& font,
        const std::string& text,
        float fontSize,
        float spacing,
        ::Color tint = {255, 255, 255, 255}) {
        return ::ImageTextEx(font, text.c_str(), fontSize, spacing, tint);
    }

    /**
     * 从屏幕缓冲区获取像素数据并返回图像（截图）
     */
    static ::Image LoadFromScreen() { return ::LoadImageFromScreen(); }

    /**
     * 生成纯色图像
     */
    static ::Image Color(int width, int height, ::Color color = {255, 255, 255, 255}) {
        return ::GenImageColor(width, height, color);
    }

    /**
     * 生成线性渐变图像
     */
    static ::Image GradientLinear(int width, int height, int direction, ::Color start, ::Color end) {
        return ::GenImageGradientLinear(width, height, direction, start, end);
    }

    /**
     * 生成径向渐变图像
     */
    static ::Image GradientRadial(int width, int height, float density, ::Color inner, ::Color outer) {
        return ::GenImageGradientRadial(width, height, density, inner, outer);
    }

    /**
     * 生成棋盘图像
     */
    static ::Image Checked(
        int width,
        int height,
        int checksX,
        int checksY,
        ::Color col1 = {255, 255, 255, 255},
        ::Color col2 = {0, 0, 0, 255}) {
        return ::GenImageChecked(width, height, checksX, checksY, col1, col2);
    }

    /**
     * 生成白噪声图像
     */
    static ::Image WhiteNoise(int width, int height, float factor) {
        return ::GenImageWhiteNoise(width, height, factor);
    }

    /**
     * 生成细胞图像。tileSize 越大，单元格越大
     */
    static ::Image Cellular(int width, int height, int tileSize) { return ::GenImageCellular(width, height, tileSize); }

    /**
     * 获取剪贴板图像内容。
     */
    static ::Image GetClipboard() { return ::GetClipboardImage(); }

    ~Image() { Unload(); }

    Image& operator=(const ::Image& image) {
        set(image);
        return *this;
    }

    Image& operator=(const Image& other) {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other.Copy());

        return *this;
    }

    Image& operator=(Image&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.mipmaps = 0;
        other.format = 0;

        return *this;
    }

    /**
     * 从文件加载图像到 CPU 内存（RAM）
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see ::LoadImage()
     */
    void Load(const std::string& fileName) {
        set(::LoadImage(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * 从 RAW 文件数据加载图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see ::LoadImageRaw()
     */
    void Load(const std::string& fileName, int width, int height, int format, int headerSize) {
        set(::LoadImageRaw(fileName.c_str(), width, height, format, headerSize));
        if (!IsValid()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * 从文件加载图像序列（帧附加到 image.data）。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see ::LoadImageAnim()
     */
    void Load(const std::string& fileName, int* frames) {
        set(::LoadImageAnim(fileName.c_str(), frames));
        if (!IsValid()) {
            throw RaylibException("Failed to load Image from file: " + fileName);
        }
    }

    /**
     * 从内存缓冲区加载图像，fileType 指的是扩展名：例如 "png"。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see ::LoadImageFromMemory()
     */
    void Load(const std::string& fileType, const unsigned char* fileData, int dataSize) {
        set(::LoadImageFromMemory(fileType.c_str(), fileData, dataSize));
        if (!IsValid()) {
            throw RaylibException("Failed to load Image data with file type: " + fileType);
        }
    }

    /**
     * 从给定文件加载图像。
     *
     * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
     *
     * @see ::LoadImageFromTexture()
     */
    void Load(const ::Texture2D& texture) {
        set(::LoadImageFromTexture(texture));
        if (!IsValid()) {
            throw RaylibException("Failed to load Image from texture.");
        }
    }

    /**
     * 从 CPU 内存（RAM）卸载图像
     */
    void Unload() {
        if (data != nullptr) {
            ::UnloadImage(*this);
            data = nullptr;
        }
    }

    /**
     * 将图像数据导出到文件，成功返回 true
     *
     * @throws raylib::RaylibException 如果图像导出失败则抛出异常。
     */
    void Export(const std::string& fileName) const {
        if (!::ExportImage(*this, fileName.c_str())) {
            throw RaylibException(TextFormat("Failed to export Image to file: %s", fileName.c_str()));
        }
    }

    /**
     * 将图像导出到内存缓冲区
     */
    unsigned char* ExportToMemory(const char* fileType, int* fileSize) {
        return ::ExportImageToMemory(*this, fileType, fileSize);
    }

    /**
     * 将图像导出为代码文件，定义一个字节数组，成功返回 true
     *
     * @throws raylib::RaylibException 如果图像导出失败则抛出异常。
     */
    void ExportAsCode(const std::string& fileName) const {
        if (!::ExportImageAsCode(*this, fileName.c_str())) {
            throw RaylibException(TextFormat("Failed to export Image code to file: %s", fileName.c_str()));
        }
    }

    GETTER(void*, Data, data)
    GETTER(int, Width, width)
    GETTER(int, Height, height)
    GETTER(int, Mipmaps, mipmaps)
    GETTER(int, Format, format)

    /**
     * 设置图像画布的宽度。
     *
     * @see ResizeCanvas
     */
    void SetWidth(int width, int offsetX = 0, int offsetY = 0, ::Color fill = {255, 255, 255, 255}) {
        ResizeCanvas(width, height, offsetX, offsetY, fill);
    }

    /**
     * 设置图像画布的高度。
     *
     * @see ResizeCanvas
     */
    void SetHeight(int height, int offsetX = 0, int offsetY = 0, ::Color fill = {255, 255, 255, 255}) {
        ResizeCanvas(width, height, offsetX, offsetY, fill);
    }

    /**
     * 获取图像的宽度和高度。
     */
    [[nodiscard]] ::Vector2 GetSize() const { return {static_cast<float>(width), static_cast<float>(height)}; }

    /**
     * 创建图像的副本（用于变换）
     */
    [[nodiscard]] ::Image Copy() const { return ::ImageCopy(*this); }

    /**
     * 从另一个图像创建图像片段
     */
    [[nodiscard]] ::Image FromImage(::Rectangle rec) const { return ::ImageFromImage(*this, rec); }

    /**
     * 将图像数据转换为所需格式
     */
    Image& Format(int newFormat) {
        ::ImageFormat(this, newFormat);
        return *this;
    }

    /**
     * 将图像转换为 POT（2 的幂）
     */
    Image& ToPOT(::Color fillColor) {
        ::ImageToPOT(this, fillColor);
        return *this;
    }

    /**
     * 根据矩形裁剪图像
     */
    Image& Crop(::Rectangle crop) {
        ::ImageCrop(this, crop);
        return *this;
    }

    /**
     * 根据 alpha 值裁剪图像
     */
    Image& AlphaCrop(float threshold) {
        ::ImageAlphaCrop(this, threshold);
        return *this;
    }

    /**
     * 清除 alpha 通道为所需颜色
     */
    Image& AlphaClear(::Color color, float threshold) {
        ::ImageAlphaClear(this, color, threshold);
        return *this;
    }

    /**
     * 应用 alpha 蒙版到图像
     */
    Image& AlphaMask(const ::Image& alphaMask) {
        ::ImageAlphaMask(this, alphaMask);
        return *this;
    }

    /**
     * 预乘 alpha 通道
     */
    Image& AlphaPremultiply() {
        ::ImageAlphaPremultiply(this);
        return *this;
    }

    /**
     * 裁剪图像为新的给定宽度和高度。
     */
    Image& Crop(int newWidth, int newHeight) { return Crop(0, 0, newWidth, newHeight); }

    /**
     * 根据向量裁剪图像为新的给定宽度和高度。
     */
    Image& Crop(::Vector2 size) { return Crop(0, 0, static_cast<int>(size.x), static_cast<int>(size.y)); }

    /**
     * 根据矩形裁剪图像
     */
    Image& Crop(int offsetX, int offsetY, int newWidth, int newHeight) {
        ::Rectangle rect{
            static_cast<float>(offsetX),
            static_cast<float>(offsetY),
            static_cast<float>(newWidth),
            static_cast<float>(newHeight)};
        ::ImageCrop(this, rect);
        return *this;
    }

    /**
     * 调整图像大小为新尺寸
     */
    Image& Resize(int newWidth, int newHeight) {
        ::ImageResize(this, newWidth, newHeight);
        return *this;
    }

    /**
     * 使用最近邻算法调整图像大小为新尺寸
     */
    Image& ResizeNN(int newWidth, int newHeight) {
        ::ImageResizeNN(this, newWidth, newHeight);
        return *this;
    }

    /**
     * 调整画布大小并填充颜色
     */
    Image&
    ResizeCanvas(int newWidth, int newHeight, int offsetX = 0, int offsetY = 0, ::Color color = {255, 255, 255, 255}) {
        ::ImageResizeCanvas(this, newWidth, newHeight, offsetX, offsetY, color);
        return *this;
    }

    /**
     * 为提供的图像生成所有 mipmap 级别
     */
    Image& Mipmaps() {
        ::ImageMipmaps(this);
        return *this;
    }

    /**
     * 将图像数据抖动为 16bpp 或更低（Floyd-Steinberg 抖动）
     */
    Image& Dither(int rBpp, int gBpp, int bBpp, int aBpp) {
        ::ImageDither(this, rBpp, gBpp, bBpp, aBpp);
        return *this;
    }

    /**
     * 垂直翻转图像
     */
    Image& FlipVertical() {
        ::ImageFlipVertical(this);
        return *this;
    }

    /**
     * 水平翻转图像
     */
    Image& FlipHorizontal() {
        ::ImageFlipHorizontal(this);
        return *this;
    }

    /**
     * 按输入角度（-359 到 359）旋转图像
     */
    Image& Rotate(int degrees) {
        ::ImageRotate(this, degrees);
        return *this;
    }

    /**
     * 顺时针旋转图像 90 度
     */
    Image& RotateCW() {
        ::ImageRotateCW(this);
        return *this;
    }

    /**
     * 逆时针旋转图像 90 度
     */
    Image& RotateCCW() {
        ::ImageRotateCCW(this);
        return *this;
    }

    /**
     * 修改图像颜色：色调
     */
    Image& ColorTint(::Color color = {255, 255, 255, 255}) {
        ::ImageColorTint(this, color);
        return *this;
    }

    /**
     * 修改图像颜色：反转
     */
    Image& ColorInvert() {
        ::ImageColorInvert(this);
        return *this;
    }

    /**
     * 修改图像颜色：灰度
     */
    Image& ColorGrayscale() {
        ::ImageColorGrayscale(this);
        return *this;
    }

    /**
     * 修改图像颜色：对比度
     *
     * @param contrast 对比度值在 -100 到 100 之间
     */
    Image& ColorContrast(float contrast) {
        ::ImageColorContrast(this, contrast);
        return *this;
    }

    /**
     * 修改图像颜色：亮度
     *
     * @param brightness 亮度值在 -255 到 255 之间
     */
    Image& ColorBrightness(int brightness) {
        ::ImageColorBrightness(this, brightness);
        return *this;
    }

    /**
     * 修改图像颜色：替换颜色
     */
    Image& ColorReplace(::Color color, ::Color replace) {
        ::ImageColorReplace(this, color, replace);
        return *this;
    }

    /**
     * 获取图像 alpha 边框矩形
     *
     * @param threshold 阈值定义为百分比：0.0f -> 1.0f
     */
    [[nodiscard]] Rectangle GetAlphaBorder(float threshold) const { return ::GetImageAlphaBorder(*this, threshold); }

    /**
     * 获取图像在 (x, y) 位置的像素颜色
     */
    [[nodiscard]] raylib::Color GetColor(int x = 0, int y = 0) const { return ::GetImageColor(*this, x, y); }

    /**
     * 获取图像在向量位置的像素颜色
     */
    [[nodiscard]] raylib::Color GetColor(::Vector2 position) const {
        return ::GetImageColor(*this, static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * 用给定颜色清除图像背景
     */
    Image& ClearBackground(::Color color = {0, 0, 0, 255}) {
        ::ImageClearBackground(this, color);
        return *this;
    }

    /**
     * 在图像中绘制像素
     */
    void DrawPixel(int posX, int posY, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawPixel(this, posX, posY, color);
    }

    void DrawPixel(::Vector2 position, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawPixelV(this, position, color);
    }

    void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawLine(this, startPosX, startPosY, endPosX, endPosY, color);
    }

    void DrawLine(::Vector2 start, ::Vector2 end, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawLineV(this, start, end, color);
    }

    /**
     * 在图像中绘制带有厚度的线条
     */
    void DrawLine(::Vector2 start, ::Vector2 end, int thick, ::Color color = {255, 255, 255, 255}) {
        ImageDrawLineEx(this, start, end, thick, color);
    }

    void DrawCircle(int centerX, int centerY, int radius, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawCircle(this, centerX, centerY, radius, color);
    }

    void DrawCircle(::Vector2 center, int radius, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawCircleV(this, center, radius, color);
    }

    void DrawRectangle(int posX, int posY, int width, int height, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangle(this, posX, posY, width, height, color);
    }

    void DrawRectangle(Vector2 position, Vector2 size, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleV(this, position, size, color);
    }

    void DrawRectangle(::Rectangle rec, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleRec(this, rec, color);
    }

    void DrawRectangleLines(::Rectangle rec, int thick = 1, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawRectangleLines(this, rec, thick, color);
    }

    // TODO: 添加 ImageDrawTriangle()

    void Draw(const ::Image& src, ::Rectangle srcRec, ::Rectangle dstRec, ::Color tint = {255, 255, 255, 255}) {
        ::ImageDraw(this, src, srcRec, dstRec, tint);
    }

    void DrawText(const char* text, ::Vector2 position, int fontSize, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(this, text, static_cast<int>(position.x), static_cast<int>(position.y), fontSize, color);
    }

    void DrawText(const std::string& text, ::Vector2 position, int fontSize, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(
            this,
            text.c_str(),
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            fontSize,
            color);
    }

    void DrawText(const std::string& text, int x, int y, int fontSize, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(this, text.c_str(), x, y, fontSize, color);
    }

    void DrawText(const char* text, int x, int y, int fontSize, ::Color color = {255, 255, 255, 255}) {
        ::ImageDrawText(this, text, x, y, fontSize, color);
    }

    void DrawText(
        const ::Font& font,
        const std::string& text,
        ::Vector2 position,
        float fontSize,
        float spacing,
        ::Color tint = {255, 255, 255, 255}) {
        ::ImageDrawTextEx(this, font, text.c_str(), position, fontSize, spacing, tint);
    }

    void DrawText(
        const ::Font& font,
        const char* text,
        ::Vector2 position,
        float fontSize,
        float spacing,
        ::Color tint = {255, 255, 255, 255}) {
        ::ImageDrawTextEx(this, font, text, position, fontSize, spacing, tint);
    }

    /**
     * 从图像加载颜色数据为 Color 数组（RGBA - 32 位）
     */
    [[nodiscard]] ::Color* LoadColors() const { return ::LoadImageColors(*this); }

    /**
     * 从图像加载颜色调色板为 Color 数组（RGBA - 32 位）
     */
    ::Color* LoadPalette(int maxPaletteSize, int* colorsCount) const {
        return ::LoadImagePalette(*this, maxPaletteSize, colorsCount);
    }

    /**
     * 卸载使用 LoadImageColors() 加载的颜色数据
     */
    void UnloadColors(::Color* colors) const { ::UnloadImageColors(colors); }

    /**
     * 卸载使用 LoadImagePalette() 加载的颜色调色板
     */
    void UnloadPalette(::Color* colors) const { ::UnloadImagePalette(colors); }

    /**
     * 从图像数据加载纹理
     */
    [[nodiscard]] ::Texture2D LoadTexture() const { return ::LoadTextureFromImage(*this); }

    /**
     * 从图像数据加载纹理
     *
     * @see LoadTexture()
     */
    operator ::Texture2D() const { return LoadTexture(); }

    /**
     * 获取特定格式的像素数据大小（以字节为单位）
     */
    static int GetPixelDataSize(int width, int height, int format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32) {
        return ::GetPixelDataSize(width, height, format);
    }

    /**
     * 返回当前图像的像素数据大小
     *
     * @return 图像的像素数据大小
     */
    [[nodiscard]] int GetPixelDataSize() const { return ::GetPixelDataSize(width, height, format); }

    /**
     * 检索图像是否已加载
     *
     * @return 图像是否已加载
     */
    [[nodiscard]] bool IsValid() const { return ::IsImageValid(*this); }

    /**
     * 从另一个图像的选定通道创建图像（灰度）
     */
    ::Image Channel(int selectedChannel) { return ::ImageFromChannel(*this, selectedChannel); }

    /**
     * 对图像应用自定义平方卷积核
     */
    void KernelConvolution(const float* kernel, int kernelSize) { ::ImageKernelConvolution(this, kernel, kernelSize); }
protected:
    void set(const ::Image& image) {
        data = image.data;
        width = image.width;
        height = image.height;
        mipmaps = image.mipmaps;
        format = image.format;
    }
};
} // namespace raylib

using RImage = raylib::Image;

// #endif // RAYLIB_CPP_INCLUDE_IMAGE_HPP_