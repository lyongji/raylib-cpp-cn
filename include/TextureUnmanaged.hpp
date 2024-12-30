// #ifndef RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_
// #define RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_
#pragma once

#include <string>

#include "./Image.hpp"
#include "./Material.hpp"
#include "./RaylibException.hpp"
#include "./Vector2.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 一个不由 C++ RAII 管理的纹理。
 *
 * 如果需要，请确保调用 Unload()，否则请使用 raylib::Texture。
 *
 * @see raylib::Texture
 */
class 非托管纹理 : public ::Texture {
public:
    /**
     * 默认纹理构造函数。
     */
    非托管纹理() : ::Texture{0, 0, 0, 0, 0} {
        // 无操作。
    }

    /**
     * 手动移动/创建纹理结构。
     */
    非托管纹理(unsigned int id, int 宽, int 高, int 多级纹理 = 1, int 格式 = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        : ::Texture{id, 宽, 高, 多级纹理, 格式} {
        // 无操作。
    }

    /**
     * 基于给定的 Texture 结构数据创建纹理对象。
     */
    非托管纹理(const ::Texture& 纹理) : ::Texture{纹理.id, 纹理.width, 纹理.height, 纹理.mipmaps, 纹理.format} {
        // 无操作。
    }

    /**
     * 从给定的 Image 创建纹理。
     *
     * @throws raylib::RaylibException 如果从给定的图像创建纹理失败，则抛出异常。
     */
    非托管纹理(const ::Image& 图像) { 加载(图像); }

    /**
     * 从图像加载立方体贴图，支持多种图像立方体贴图布局。
     *
     * @throws raylib::RaylibException 如果从给定的立方体贴图创建纹理失败，则抛出异常。
     *
     * @see LoadTextureCubemap()
     */
    非托管纹理(const ::Image& 图像, int 布局类型) { 加载(图像, 布局类型); }

    /**
     * 从文件加载纹理到 GPU 内存（VRAM）。
     *
     * @throws raylib::RaylibException 如果从给定的文件创建纹理失败，则抛出异常。
     */
    非托管纹理(const std::string& 文件名) { 加载(文件名); }

    非托管纹理(::Texture&& other) : ::Texture{other.id, other.width, other.height, other.mipmaps, other.format} {
        // 无操作。
    }

    GETTER(unsigned int, Id, id)
    GETTER(int, 宽, width)
    GETTER(int, 高, height)
    GETTER(int, 多级纹理, mipmaps)
    GETTER(int, 格式, format)

    非托管纹理& operator=(const ::Texture& 纹理) {
        设(纹理);
        return *this;
    }

    /**
     * 检索纹理的宽度和高度。
     */
    [[nodiscard]] Vector2 取尺寸() const { return {static_cast<float>(width), static_cast<float>(height)}; }

    /**
     * 从图像数据加载纹理。
     */
    void 加载(const ::Image& 图像) {
        设(::LoadTextureFromImage(图像));
        if (!是有效()) {
            throw Raylib异常("从图像加载纹理失败");
        }
    }

    /**
     * 从图像加载立方体贴图，支持多种图像立方体贴图布局。
     */
    void 加载(const ::Image& 图像, int 布局类型) {
        设(::LoadTextureCubemap(图像, 布局类型));
        if (!是有效()) {
            throw Raylib异常("从立方体贴图加载纹理失败");
        }
    }

    /**
     * 从文件加载纹理到 GPU 内存（VRAM）。
     */
    void 加载(const std::string& 文件名) {
        设(::LoadTexture(文件名.c_str()));
        if (!是有效()) {
            throw Raylib异常("从文件加载纹理失败: " + 文件名);
        }
    }

    /**
     * 从 GPU 内存（VRAM）卸载纹理。
     */
    void 卸载() {
        // 防止调用 UnloadTexture() 两次。
        if (id != 0) {
            ::UnloadTexture(*this);
            id = 0;
        }
    }

    /**
     * 使用新数据更新 GPU 纹理。
     */
    非托管纹理& 更新(const void* 像素) {
        ::UpdateTexture(*this, 像素);
        return *this;
    }

    /**
     * 使用新数据更新 GPU 纹理矩形。
     */
    非托管纹理& 更新(::Rectangle 矩形, const void* 像素) {
        UpdateTextureRec(*this, 矩形, 像素);
        return *this;
    }

    /**
     * 从 GPU 纹理获取像素数据并返回 Image。
     */
    [[nodiscard]] ::Image 取数据() const { return ::LoadImageFromTexture(*this); }

    /**
     * 从 GPU 纹理获取像素数据并返回 Image。
     */
    operator 图像() { return 取数据(); }

    /**
     * 为纹理生成 GPU 多级渐远纹理。
     */
    非托管纹理& 生成多级渐进纹理() {
        ::GenTextureMipmaps(this);
        return *this;
    }

    /**
     * 设置纹理缩放过滤模式。
     */
    非托管纹理& 设纹理过滤(int 过滤器模式) {
        ::SetTextureFilter(*this, 过滤器模式);
        return *this;
    }

    /**
     * 设置纹理包裹模式。
     */
    非托管纹理& 设纹理环绕(int 环绕模式) {
        ::SetTextureWrap(*this, 环绕模式);
        return *this;
    }

    /**
     * 绘制 Texture2D。
     *
     * @see ::DrawTexture()
     */
    void 绘制(int 位置X = 0, int 位置Y = 0, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTexture(*this, 位置X, 位置Y, 色调);
    }

    /**
     * 使用 Vector2 定义的位置绘制 Texture2D。
     *
     * @see ::DrawTextureV()
     */
    void 绘制(::Vector2 位置, ::Color 色调 = {255, 255, 255, 255}) const { ::DrawTextureV(*this, 位置, 色调); }

    /**
     * 使用扩展参数绘制 Texture2D。
     *
     * @see ::DrawTextureEx()
     */
    void 绘制(::Vector2 位置, float 旋转, float 缩放 = 1.0f, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTextureEx(*this, 位置, 旋转, 缩放, 色调);
    }

    /**
     * 绘制由矩形定义的纹理的一部分。
     *
     * @see ::DrawTextureRec()
     */
    void 绘制(::Rectangle 源矩形, ::Vector2 位置 = {0, 0}, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTextureRec(*this, 源矩形, 位置, 色调);
    }

    /**
     * 使用“pro”参数绘制由矩形定义的纹理的一部分。
     *
     * @see ::DrawTexturePro()
     */
    void 绘制(
        ::Rectangle 源矩形,
        ::Rectangle 目标区域,
        ::Vector2 原点 = {0, 0},
        float 旋转 = 0,
        ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTexturePro(*this, 源矩形, 目标区域, 原点, 旋转, 色调);
    }

    /**
     * 绘制一个可以很好地拉伸或收缩的纹理（或其一部分）。
     *
     * @see ::DrawTextureNPatch()
     */
    void 绘制(
        ::NPatchInfo 九宫格布局,
        ::Rectangle 目标区域,
        ::Vector2 原点 = {0, 0},
        float 旋转 = 0,
        ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawTextureNPatch(*this, 九宫格布局, 目标区域, 原点, 旋转, 色调);
    }

    /**
     * 绘制公告板纹理。
     *
     * @see ::DrawBillboard()
     */
    void 绘制公告板(const ::Camera& 相机, ::Vector3 位置, float 缩放, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawBillboard(相机, *this, 位置, 缩放, 色调);
    }

    /**
     * 绘制由源定义的公告板纹理。
     *
     * @see ::DrawBillboardRec()
     */
    void 绘制公告板(
        const ::Camera& 相机,
        ::Rectangle 源区域,
        ::Vector3 位置,
        ::Vector2 尺寸,
        ::Color 色调 = {255, 255, 255, 255}) const {
        DrawBillboardRec(相机, *this, 源区域, 位置, 尺寸, 色调);
    }

    /**
     * 绘制由源和旋转定义的公告板纹理。
     *
     * @see ::DrawBillboardPro()
     */
    void 绘制公告板(
        const ::Camera& 相机,
        ::Rectangle 源区域,
        Vector3 位置,
        ::Vector3 上方向,
        Vector2 尺寸,
        Vector2 原点,
        float 旋转 = 0.0f,
        ::Color 色调 = {255, 255, 255, 255}) const {
        DrawBillboardPro(相机, *this, 源区域, 位置, 上方向, 尺寸, 原点, 旋转, 色调);
    }

    /**
     * 为材质映射类型（MAP_DIFFUSE, MAP_SPECULAR...）设置纹理。
     */
    非托管纹理& 设材质(::Material* 材质, int 映射类型 = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture(材质, 映射类型, *this);
        return *this;
    }

    非托管纹理& 设材质(const ::Material& 材质, int 映射类型 = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture((::Material*)(&材质), 映射类型, *this);
        return *this;
    }

    /**
     * 设置用于形状绘制的纹理和矩形。
     */
    非托管纹理& 设形状(const ::Rectangle& 源区域) {
        ::SetShapesTexture(*this, 源区域);
        return *this;
    }

    /**
     * 为着色器设置纹理统一值（sampler2d）。
     */
    非托管纹理& 设着色器值(const ::Shader& 着色器, int 位置索引) {
        ::SetShaderValueTexture(着色器, 位置索引, *this);
        return *this;
    }

    /**
     * 确定纹理是否已加载并准备好。
     *
     * @return 根据纹理是否有数据返回 true 或 false。
     */
    [[nodiscard]] bool 是有效() const { return IsTextureValid(*this); }
protected:
    void 设(const ::Texture& 纹理) {
        id = 纹理.id;
        width = 纹理.width;
        height = 纹理.height;
        mipmaps = 纹理.mipmaps;
        format = 纹理.format;
    }
};

// 创建 TextureUnmanaged 的别名。
using 非托管纹理2D = 非托管纹理;
using 非托管立方体贴图 = 非托管纹理;

} // namespace raylib

using R非托管纹理 = raylib::非托管纹理;
using R非托管纹理2D = raylib::非托管纹理2D;
using R非托管立方体贴图 = raylib::非托管立方体贴图;

// #endif // RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_