// #ifndef RAYLIB_CPP_INCLUDE_IMAGE_HPP_
// #define RAYLIB_CPP_INCLUDE_IMAGE_HPP_
#pragma once

#include <format>
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
class 图像 : public ::Image {
public:
  图像(void *数据 = nullptr, int 宽 = 0, int 高 = 0, int 多级纹理 = 1,
       int 格式 = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
      : ::Image{.data = 数据,
                .width = 宽,
                .height = 高,
                .mipmaps = 多级纹理,
                .format = 格式} {
    // 无操作
  }

  图像(const ::Image &图像) : ::Image(图像) {}

  /**
   * 从给定文件加载图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see Load()
   */
  图像(const std::string &文件路径) { 加载(文件路径); }

  /**
   * 从给定文件加载原始图像，带有提供的宽度、高度和格式。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see LoadRaw()
   */
  图像(const std::string &文件路径, int 宽, int 高, int 格式,
       int 文件头大小 = 0) {
    加载(文件路径, 宽, 高, 格式, 文件头大小);
  }

  /**
   * 从给定文件加载动画图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see LoadAnim()
   */
  图像(const std::string &文件路径, int *帧数) { 加载(文件路径, 帧数); }

  /**
   * 从给定文件加载图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   */
  图像(const std::string &文件类型, const unsigned char *文件数据,
       int 数据大小) {
    加载(文件类型, 文件数据, 数据大小);
  }

  /**
   * 从给定文件加载图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   */
  图像(const ::Texture2D &纹理) { 加载(纹理); }

  图像(int 宽, int 高, ::Color 颜色 = {255, 255, 255, 255}) {
    设(::GenImageColor(宽, 高, 颜色));
  }

  图像(const std::string &文本, int 字符大小,
       ::Color 颜色 = {255, 255, 255, 255}) {
    设(::ImageText(文本.c_str(), 字符大小, 颜色));
  }

  图像(const ::Font &字体, const std::string &文本, float 字符大小, float 间距,
       ::Color 色调 = {255, 255, 255, 255}) {
    设(::ImageTextEx(字体, 文本.c_str(), 字符大小, 间距, 色调));
  }

  图像(const 图像 &other) { 设(other.创建副本()); }

  图像(图像 &&other) noexcept {
    设(other);

    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    other.mipmaps = 0;
    other.format = 0;
  }

  static ::Image 文本(const std::string &文本, int 字符大小,
                      ::Color 颜色 = {255, 255, 255, 255}) {
    return ::ImageText(文本.c_str(), 字符大小, 颜色);
  }

  static ::Image 文本(const ::Font &字体, const std::string &文本,
                      float 字符大小, float 间距,
                      ::Color 色调 = {255, 255, 255, 255}) {
    return ::ImageTextEx(字体, 文本.c_str(), 字符大小, 间距, 色调);
  }

  /**
   * 从屏幕缓冲区获取像素数据并返回图像（截图）
   */
  static ::Image 加载屏幕图像() { return ::LoadImageFromScreen(); }

  /**
   * 生成纯色图像
   */
  static ::Image 生成纯色图(int 宽, int 高,
                            ::Color 颜色 = {255, 255, 255, 255}) {
    return ::GenImageColor(宽, 高, 颜色);
  }

  /**
   * 生成线性渐变图像
   */
  static ::Image 生成线性渐变图(int 宽, int 高, int 方向, ::Color 起,
                                ::Color 止) {
    return ::GenImageGradientLinear(宽, 高, 方向, 起, 止);
  }

  /**
   * 生成径向渐变图像
   */
  static ::Image 生成径向渐变图(int 宽, int 高, float 密度, ::Color 内,
                                ::Color 外) {
    return ::GenImageGradientRadial(宽, 高, 密度, 内, 外);
  }

  /**
   * 生成棋盘图像
   */
  static ::Image 生成棋盘格图(int 宽, int 高, int 横格数, int 纵格数,
                              ::Color col1 = {255, 255, 255, 255},
                              ::Color col2 = {0, 0, 0, 255}) {
    return ::GenImageChecked(宽, 高, 横格数, 纵格数, col1, col2);
  }

  /**
   * 生成白噪声图像
   */
  static ::Image 生成白噪声图(int 宽, int 高, float 系数) {
    return ::GenImageWhiteNoise(宽, 高, 系数);
  }

  /**
   * 生成细胞图像。tileSize 越大，单元格越大
   */
  static ::Image 生成细胞噪声图(int 宽, int 高, int 细胞大小) {
    return ::GenImageCellular(宽, 高, 细胞大小);
  }

  /**
   * 获取剪贴板图像内容。
   */
  static ::Image 取剪贴板图() { return ::GetClipboardImage(); }

  ~图像() { 卸载(); }

  图像 &operator=(const ::Image &image) {
    设(image);
    return *this;
  }

  图像 &operator=(const 图像 &other) {
    if (this == &other) {
      return *this;
    }

    卸载();
    设(other.创建副本());

    return *this;
  }

  图像 &operator=(图像 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载();
    设(other);

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
  void 加载(const std::string &文件路径) {
    设(::LoadImage(文件路径.c_str()));
    if (!检查可用性()) {
      throw Raylib异常("从文件中加载图像失败： " + 文件路径);
    }
  }

  /**
   * 从 RAW 文件数据加载图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see ::LoadImageRaw()
   */
  void 加载(const std::string &文件路径, int 宽, int 高, int 格式,
            int 文件头大小) {
    设(::LoadImageRaw(文件路径.c_str(), 宽, 高, 格式, 文件头大小));
    if (!检查可用性()) {
      throw Raylib异常("从文件中加载图像失败： " + 文件路径);
    }
  }

  /**
   * 从文件加载图像序列（帧附加到 image.data）。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see ::LoadImageAnim()
   */
  void 加载(const std::string &文件路径, int *帧数) {
    设(::LoadImageAnim(文件路径.c_str(), 帧数));
    if (!检查可用性()) {
      throw Raylib异常("从文件中加载图像失败： " + 文件路径);
    }
  }

  /**
   * 从内存缓冲区加载图像，fileType 指的是扩展名：例如 "png"。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see ::LoadImageFromMemory()
   */
  void 加载(const std::string &文件名, const unsigned char *文件数据,
            int 数据大小) {
    设(::LoadImageFromMemory(文件名.c_str(), 文件数据, 数据大小));
    if (!检查可用性()) {
      throw Raylib异常("加载文件类型的图像数据失败： " + 文件名);
    }
  }

  /**
   * 从给定文件加载图像。
   *
   * @throws raylib::RaylibException 如果图像加载失败则抛出异常。
   *
   * @see ::LoadImageFromTexture()
   */
  void 加载(const ::Texture2D &纹理) {
    设(::LoadImageFromTexture(纹理));
    if (!检查可用性()) {
      throw Raylib异常("从纹理加载图像失败。");
    }
  }

  /**
   * 从 CPU 内存（RAM）卸载图像
   */
  void 卸载() {
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
  void 导出到文件(const std::string &文件路径) const {
    if (!::ExportImage(*this, 文件路径.c_str())) {
      throw Raylib异常(std::format("导出图像到文件: %s 失败。", 文件路径));
    }
  }

  /**
   * 将图像导出到内存缓冲区
   */
  unsigned char *导出到内存(const char *文件类型, int *文件大小) {
    return ::ExportImageToMemory(*this, 文件类型, 文件大小);
  }

  /**
   * 将图像导出为代码文件，定义一个字节数组，成功返回 true
   *
   * @throws raylib::RaylibException 如果图像导出失败则抛出异常。
   */
  void 导出到代码文件(const std::string &文件路径) const {
    if (!::ExportImageAsCode(*this, 文件路径.c_str())) {
      throw Raylib异常(std::format("未能将图像代码导出到文件：%s", 文件路径));
    }
  }

  GETTER(void *, 数据, data)
  GETTER(int, 宽, width)
  GETTER(int, 高, height)
  GETTER(int, 多级纹理值, mipmaps)
  GETTER(int, 格式, format)

  void 设宽度(int 宽, int 偏移X = 0, int 偏移Y = 0,
              ::Color 填充色 = {255, 255, 255, 255}) {
    调整画布尺寸并填色(宽, height, 偏移X, 偏移Y, 填充色);
  }

  void 设高度(int 高, int 偏移X = 0, int 偏移Y = 0,
              ::Color 填充色 = {255, 255, 255, 255}) {
    调整画布尺寸并填色(width, 高, 偏移X, 偏移Y, 填充色);
  }

  [[nodiscard]] ::Vector2 取宽高值() const {
    return {static_cast<float>(width), static_cast<float>(height)};
  }

  /**
   * 创建图像的副本（用于变换）
   */
  [[nodiscard]] ::Image 创建副本() const { return ::ImageCopy(*this); }

  [[nodiscard]] ::Image 提取图像片段(::Rectangle 矩形) const {
    return ::ImageFromImage(*this, 矩形);
  }

  图像 &转格式(int 新格式) {
    ::ImageFormat(this, 新格式);
    return *this;
  }

  /**
   * 将图像转换为 POT（2 的幂）
   */
  图像 &转为二次方图像(::Color 填充色) {
    ::ImageToPOT(this, 填充色);
    return *this;
  }

  图像 &根据矩形裁剪(::Rectangle 矩形) {
    ::ImageCrop(this, 矩形);
    return *this;
  }

  图像 &根据透明度裁剪(float 阈值) {
    ::ImageAlphaCrop(this, 阈值);
    return *this;
  }

  图像 &清除透明颜色为(::Color 颜色, float 阈值) {
    ::ImageAlphaClear(this, 颜色, 阈值);
    return *this;
  }

  图像 &应用透明蒙版(const ::Image &透明蒙版) {
    ::ImageAlphaMask(this, 透明蒙版);
    return *this;
  }

  /**
   * RGB预乘 alpha 通道；使得带透明度图片纹理可以正常的进行线性插值
   */
  图像 &透明通道预乘() {
    ::ImageAlphaPremultiply(this);
    return *this;
  }

  /**
   * 裁剪图像为新的给定宽度和高度。
   */
  图像 &裁剪(int 新宽, int 新高) { return 裁剪(0, 0, 新宽, 新高); }

  /**
   * 根据向量裁剪图像为新的给定宽度和高度。
   */
  图像 &裁剪(::Vector2 尺寸) {
    return 裁剪(0, 0, static_cast<int>(尺寸.x), static_cast<int>(尺寸.y));
  }

  /**
   * 根据矩形裁剪图像
   */
  图像 &裁剪(int 偏移X, int 偏移Y, int 新宽, int 新高) {
    ::Rectangle rect{static_cast<float>(偏移X), static_cast<float>(偏移Y),
                     static_cast<float>(新宽), static_cast<float>(新高)};
    ::ImageCrop(this, rect);
    return *this;
  }

  /**
   * 调整图像大小为新尺寸
   */
  图像 &调整尺寸(int 新宽, int 新高) {
    ::ImageResize(this, 新宽, 新高);
    return *this;
  }

  /**
   * 使用最近邻算法调整图像大小为新尺寸
   */
  图像 &使用最近邻法调整尺寸(int 新宽, int 新高) {
    ::ImageResizeNN(this, 新宽, 新高);
    return *this;
  }

  图像 &调整画布尺寸并填色(int 新宽, int 新高, int 偏移X = 0, int 偏移Y = 0,
                           ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageResizeCanvas(this, 新宽, 新高, 偏移X, 偏移Y, 颜色);
    return *this;
  }

  /**
   * 为提供的图像生成所有 mipmap 级别
   */
  图像 &生成所有多级纹理() {
    ::ImageMipmaps(this);
    return *this;
  }

  /**
   * 将图像数据抖动为 16bpp 或更低（Floyd-Steinberg 抖动）
   */
  图像 &图像抖动(int 红位深, int 绿位深, int 蓝位深, int 透位深) {
    ::ImageDither(this, 红位深, 绿位深, 蓝位深, 透位深);
    return *this;
  }

  图像 &垂直翻转() {
    ::ImageFlipVertical(this);
    return *this;
  }

  图像 &水平翻转() {
    ::ImageFlipHorizontal(this);
    return *this;
  }

  /**
   * 按输入角度（-359 到 359）旋转图像
   */
  图像 &旋转(int 角度) {
    ::ImageRotate(this, 角度);
    return *this;
  }

  图像 &顺时针旋转90度() {
    ::ImageRotateCW(this);
    return *this;
  }

  图像 &逆时针旋转90度() {
    ::ImageRotateCCW(this);
    return *this;
  }

  图像 &调整色调(::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageColorTint(this, 颜色);
    return *this;
  }

  图像 &反转颜色() {
    ::ImageColorInvert(this);
    return *this;
  }

  图像 &转为灰度() {
    ::ImageColorGrayscale(this);
    return *this;
  }

  图像 &调整对比度(float 对比度) {
    ::ImageColorContrast(this, 对比度);
    return *this;
  }

  图像 &调整亮度(int 亮度) {
    ::ImageColorBrightness(this, 亮度);
    return *this;
  }

  图像 &替换颜色(::Color 颜色, ::Color 替换为) {
    ::ImageColorReplace(this, 颜色, 替换为);
    return *this;
  }

  /**
   * 获取图像 alpha 边框矩形
   *
   * @param threshold 阈值定义为百分比：0.0f -> 1.0f
   */
  [[nodiscard]] Rectangle 取透明边框(float 阈值) const {
    return ::GetImageAlphaBorder(*this, 阈值);
  }

  [[nodiscard]] R颜色 取指定位置颜色(int x = 0, int y = 0) const {
    return ::GetImageColor(*this, x, y);
  }

  [[nodiscard]] R颜色 取指定位置颜色(::Vector2 位置) const {
    return ::GetImageColor(*this, static_cast<int>(位置.x),
                           static_cast<int>(位置.y));
  }

  /**
   * 用给定颜色清除图像背景
   */
  图像 &清除背景(::Color 颜色 = {0, 0, 0, 255}) {
    ::ImageClearBackground(this, 颜色);
    return *this;
  }

  /**
   * 在图像中绘制像素
   */
  void 绘制像素点(int 位置X, int 位置Y, ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawPixel(this, 位置X, 位置Y, 颜色);
  }

  void 绘制像素点(::Vector2 位置, ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawPixelV(this, 位置, 颜色);
  }

  void 绘制线段(int 起点X, int 起点Y, int 终点X, int 终点Y,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawLine(this, 起点X, 起点Y, 终点X, 终点Y, 颜色);
  }

  void 绘制线段(::Vector2 起点, ::Vector2 终点,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawLineV(this, 起点, 终点, 颜色);
  }

  /**
   * 在图像中绘制带有厚度的线条
   */
  void 绘制线段(::Vector2 起点, ::Vector2 终点, int 粗细,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ImageDrawLineEx(this, 起点, 终点, 粗细, 颜色);
  }

  void 绘制圆形(int 圆心X, int 圆心Y, int 半径,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawCircle(this, 圆心X, 圆心Y, 半径, 颜色);
  }

  void 绘制圆形(::Vector2 圆心, int 半径, ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawCircleV(this, 圆心, 半径, 颜色);
  }

  void 绘制矩形(int 位置X, int 位置Y, int 宽, int 高,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawRectangle(this, 位置X, 位置Y, 宽, 高, 颜色);
  }

  void 绘制矩形(Vector2 位置, Vector2 宽高,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawRectangleV(this, 位置, 宽高, 颜色);
  }

  void 绘制矩形(::Rectangle 矩形, ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawRectangleRec(this, 矩形, 颜色);
  }

  void 绘制矩形边框(::Rectangle 矩形, int 粗细 = 1,
                    ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawRectangleLines(this, 矩形, 粗细, 颜色);
  }

  // TODO: 添加 ImageDrawTriangle()

  void 绘制(const ::Image &源图, ::Rectangle 源区域, ::Rectangle 目标区域,
            ::Color 色调 = {255, 255, 255, 255}) {
    ::ImageDraw(this, 源图, 源区域, 目标区域, 色调);
  }

  void 绘制文本(const char *文本, ::Vector2 位置, int 字体大小,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawText(this, 文本, static_cast<int>(位置.x),
                    static_cast<int>(位置.y), 字体大小, 颜色);
  }

  void 绘制文本(const std::string &文本, ::Vector2 位置, int 字体大小,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawText(this, 文本.c_str(), static_cast<int>(位置.x),
                    static_cast<int>(位置.y), 字体大小, 颜色);
  }

  void 绘制文本(const std::string &文本, int 位置X, int 位置Y, int 字体大小,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawText(this, 文本.c_str(), 位置X, 位置Y, 字体大小, 颜色);
  }

  void 绘制文本(const char *文本, int 位置X, int 位置Y, int 字体大小,
                ::Color 颜色 = {255, 255, 255, 255}) {
    ::ImageDrawText(this, 文本, 位置X, 位置Y, 字体大小, 颜色);
  }

  void 绘制文本(const ::Font &字体, const std::string &文本, ::Vector2 位置,
                float 字体大小, float 间距,
                ::Color 色调 = {255, 255, 255, 255}) {
    ::ImageDrawTextEx(this, 字体, 文本.c_str(), 位置, 字体大小, 间距, 色调);
  }

  void 绘制文本(const ::Font &字体, const char *文本, ::Vector2 位置,
                float 字体大小, float 间距,
                ::Color 色调 = {255, 255, 255, 255}) {
    ::ImageDrawTextEx(this, 字体, 文本, 位置, 字体大小, 间距, 色调);
  }

  /**
   * 从图像加载颜色数据为 Color 数组（RGBA - 32 位）
   */
  [[nodiscard]] ::Color *加载颜色数组() const {
    return ::LoadImageColors(*this);
  }

  /**
   * 从图像加载颜色调色板为 Color 数组（RGBA - 32 位）
   */
  ::Color *加载调色板(int 最大调色板尺寸, int *颜色数量) const {
    return ::LoadImagePalette(*this, 最大调色板尺寸, 颜色数量);
  }

  /**
   * 卸载使用 LoadImageColors() 加载的颜色数据
   */
  void 卸载颜色数组(::Color *颜色) const { ::UnloadImageColors(颜色); }

  /**
   * 卸载使用 LoadImagePalette() 加载的颜色调色板
   */
  void 卸载调色板(::Color *颜色) const { ::UnloadImagePalette(颜色); }

  /**
   * 从图像数据加载纹理
   */
  [[nodiscard]] ::Texture2D 加载纹理() const {
    return ::LoadTextureFromImage(*this);
  }

  operator ::Texture2D() const { return 加载纹理(); }

  /**
   * 获取特定格式的像素数据大小（以字节为单位）
   */
  static int 取像素数据大小(int 宽, int 高,
                            int 格式 = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32) {
    return ::GetPixelDataSize(宽, 高, 格式);
  }

  [[nodiscard]] int 取当前像素数据大小() const {
    return ::GetPixelDataSize(width, height, format);
  }

  [[nodiscard]] bool 检查可用性() const { return ::IsImageValid(*this); }

  /**
   * 从另一个图像的选定通道创建图像（灰度）
   */
  ::Image 提取通道(int 选定通道) { return ::ImageFromChannel(*this, 选定通道); }

  /**
   * 对图像应用自定义平方卷积核
   */
  void 卷积处理(const float *卷积核, int 卷积核大小) {
    ::ImageKernelConvolution(this, 卷积核, 卷积核大小);
  }

protected:
  void 设(const ::Image &image) {
    data = image.data;
    width = image.width;
    height = image.height;
    mipmaps = image.mipmaps;
    format = image.format;
  }
};
} // namespace raylib

using R图像 = raylib::图像;

// #endif // RAYLIB_CPP_INCLUDE_IMAGE_HPP_