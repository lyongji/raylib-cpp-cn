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
class TextureUnmanaged : public ::Texture {
public:
    /**
     * 默认纹理构造函数。
     */
    TextureUnmanaged() : ::Texture{0, 0, 0, 0, 0} {
        // 无操作。
    }

    /**
     * 手动移动/创建纹理结构。
     */
    TextureUnmanaged(
        unsigned int id,
        int width,
        int height,
        int mipmaps = 1,
        int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        : ::Texture{id, width, height, mipmaps, format} {
        // 无操作。
    }

    /**
     * 基于给定的 Texture 结构数据创建纹理对象。
     */
    TextureUnmanaged(const ::Texture& texture)
        : ::Texture{texture.id, texture.width, texture.height, texture.mipmaps, texture.format} {
        // 无操作。
    }

    /**
     * 从给定的 Image 创建纹理。
     *
     * @throws raylib::RaylibException 如果从给定的图像创建纹理失败，则抛出异常。
     */
    TextureUnmanaged(const ::Image& image) { Load(image); }

    /**
     * 从图像加载立方体贴图，支持多种图像立方体贴图布局。
     *
     * @throws raylib::RaylibException 如果从给定的立方体贴图创建纹理失败，则抛出异常。
     *
     * @see LoadTextureCubemap()
     */
    TextureUnmanaged(const ::Image& image, int layout) { Load(image, layout); }

    /**
     * 从文件加载纹理到 GPU 内存（VRAM）。
     *
     * @throws raylib::RaylibException 如果从给定的文件创建纹理失败，则抛出异常。
     */
    TextureUnmanaged(const std::string& fileName) { Load(fileName); }

    TextureUnmanaged(::Texture&& other) : ::Texture{other.id, other.width, other.height, other.mipmaps, other.format} {
        // 无操作。
    }

    GETTER(unsigned int, Id, id)
    GETTER(int, Width, width)
    GETTER(int, Height, height)
    GETTER(int, Mipmaps, mipmaps)
    GETTER(int, Format, format)

    TextureUnmanaged& operator=(const ::Texture& texture) {
        set(texture);
        return *this;
    }

    /**
     * 检索纹理的宽度和高度。
     */
    Vector2 GetSize() const { return {static_cast<float>(width), static_cast<float>(height)}; }

    /**
     * 从图像数据加载纹理。
     */
    void Load(const ::Image& image) {
        set(::LoadTextureFromImage(image));
        if (!IsValid()) {
            throw RaylibException("从图像加载纹理失败");
        }
    }

    /**
     * 从图像加载立方体贴图，支持多种图像立方体贴图布局。
     */
    void Load(const ::Image& image, int layoutType) {
        set(::LoadTextureCubemap(image, layoutType));
        if (!IsValid()) {
            throw RaylibException("从立方体贴图加载纹理失败");
        }
    }

    /**
     * 从文件加载纹理到 GPU 内存（VRAM）。
     */
    void Load(const std::string& fileName) {
        set(::LoadTexture(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("从文件加载纹理失败: " + fileName);
        }
    }

    /**
     * 从 GPU 内存（VRAM）卸载纹理。
     */
    void Unload() {
        // 防止调用 UnloadTexture() 两次。
        if (id != 0) {
            ::UnloadTexture(*this);
            id = 0;
        }
    }

    /**
     * 使用新数据更新 GPU 纹理。
     */
    TextureUnmanaged& Update(const void* pixels) {
        ::UpdateTexture(*this, pixels);
        return *this;
    }

    /**
     * 使用新数据更新 GPU 纹理矩形。
     */
    TextureUnmanaged& Update(::Rectangle rec, const void* pixels) {
        UpdateTextureRec(*this, rec, pixels);
        return *this;
    }

    /**
     * 从 GPU 纹理获取像素数据并返回 Image。
     */
    ::Image GetData() const { return ::LoadImageFromTexture(*this); }

    /**
     * 从 GPU 纹理获取像素数据并返回 Image。
     */
    operator 图像() { return GetData(); }

    /**
     * 为纹理生成 GPU 多级渐远纹理。
     */
    TextureUnmanaged& GenMipmaps() {
        ::GenTextureMipmaps(this);
        return *this;
    }

    /**
     * 设置纹理缩放过滤模式。
     */
    TextureUnmanaged& SetFilter(int filterMode) {
        ::SetTextureFilter(*this, filterMode);
        return *this;
    }

    /**
     * 设置纹理包裹模式。
     */
    TextureUnmanaged& SetWrap(int wrapMode) {
        ::SetTextureWrap(*this, wrapMode);
        return *this;
    }

    /**
     * 绘制 Texture2D。
     *
     * @see ::DrawTexture()
     */
    void Draw(int posX = 0, int posY = 0, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTexture(*this, posX, posY, tint);
    }

    /**
     * 使用 Vector2 定义的位置绘制 Texture2D。
     *
     * @see ::DrawTextureV()
     */
    void Draw(::Vector2 position, ::Color tint = {255, 255, 255, 255}) const { ::DrawTextureV(*this, position, tint); }

    /**
     * 使用扩展参数绘制 Texture2D。
     *
     * @see ::DrawTextureEx()
     */
    void Draw(::Vector2 position, float rotation, float scale = 1.0f, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureEx(*this, position, rotation, scale, tint);
    }

    /**
     * 绘制由矩形定义的纹理的一部分。
     *
     * @see ::DrawTextureRec()
     */
    void Draw(::Rectangle sourceRec, ::Vector2 position = {0, 0}, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureRec(*this, sourceRec, position, tint);
    }

    /**
     * 使用“pro”参数绘制由矩形定义的纹理的一部分。
     *
     * @see ::DrawTexturePro()
     */
    void Draw(
        ::Rectangle sourceRec,
        ::Rectangle destRec,
        ::Vector2 origin = {0, 0},
        float rotation = 0,
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
    }

    /**
     * 绘制一个可以很好地拉伸或收缩的纹理（或其一部分）。
     *
     * @see ::DrawTextureNPatch()
     */
    void Draw(
        ::NPatchInfo nPatchInfo,
        ::Rectangle destRec,
        ::Vector2 origin = {0, 0},
        float rotation = 0,
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawTextureNPatch(*this, nPatchInfo, destRec, origin, rotation, tint);
    }

    /**
     * 绘制公告板纹理。
     *
     * @see ::DrawBillboard()
     */
    void
    DrawBillboard(const ::Camera& camera, ::Vector3 position, float size, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawBillboard(camera, *this, position, size, tint);
    }

    /**
     * 绘制由源定义的公告板纹理。
     *
     * @see ::DrawBillboardRec()
     */
    void DrawBillboard(
        const ::Camera& camera,
        ::Rectangle source,
        ::Vector3 position,
        ::Vector2 size,
        ::Color tint = {255, 255, 255, 255}) const {
        DrawBillboardRec(camera, *this, source, position, size, tint);
    }

    /**
     * 绘制由源和旋转定义的公告板纹理。
     *
     * @see ::DrawBillboardPro()
     */
    void DrawBillboard(
        const ::Camera& camera,
        ::Rectangle source,
        Vector3 position,
        ::Vector3 up,
        Vector2 size,
        Vector2 origin,
        float rotation = 0.0f,
        ::Color tint = {255, 255, 255, 255}) const {
        DrawBillboardPro(camera, *this, source, position, up, size, origin, rotation, tint);
    }

    /**
     * 为材质映射类型（MAP_DIFFUSE, MAP_SPECULAR...）设置纹理。
     */
    TextureUnmanaged& SetMaterial(::Material* material, int mapType = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture(material, mapType, *this);
        return *this;
    }

    TextureUnmanaged& SetMaterial(const ::Material& material, int mapType = MATERIAL_MAP_NORMAL) {
        ::SetMaterialTexture((::Material*)(&material), mapType, *this);
        return *this;
    }

    /**
     * 设置用于形状绘制的纹理和矩形。
     */
    TextureUnmanaged& SetShapes(const ::Rectangle& source) {
        ::SetShapesTexture(*this, source);
        return *this;
    }

    /**
     * 为着色器设置纹理统一值（sampler2d）。
     */
    TextureUnmanaged& SetShaderValue(const ::Shader& shader, int locIndex) {
        ::SetShaderValueTexture(shader, locIndex, *this);
        return *this;
    }

    /**
     * 确定纹理是否已加载并准备好。
     *
     * @return 根据纹理是否有数据返回 true 或 false。
     */
    bool IsValid() const { return IsTextureValid(*this); }
protected:
    void set(const ::Texture& texture) {
        id = texture.id;
        width = texture.width;
        height = texture.height;
        mipmaps = texture.mipmaps;
        format = texture.format;
    }
};

// 创建 TextureUnmanaged 的别名。
using Texture2DUnmanaged = TextureUnmanaged;
using TextureCubemapUnmanaged = TextureUnmanaged;

} // namespace raylib

using RTextureUnmanaged = raylib::TextureUnmanaged;
using RTexture2DUnmanaged = raylib::Texture2DUnmanaged;
using RTextureCubemapUnmanaged = raylib::TextureCubemapUnmanaged;

// #endif // RAYLIB_CPP_INCLUDE_TEXTUREUNMANAGED_HPP_