// #ifndef RAYLIB_CPP_INCLUDE_MATERIAL_HPP_
// #define RAYLIB_CPP_INCLUDE_MATERIAL_HPP_
#pragma once

#include <string>
#include <vector>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 材质类型（通用）
 */
class Material : public ::Material {
public:
    Material(const ::Material& material) { set(material); }

    /**
     * 加载默认材质（支持：漫反射、镜面反射、法线贴图）
     */
    Material() { set(LoadMaterialDefault()); }

    Material(const Material&) = delete;

    Material(Material&& other) {
        set(other);

        other.maps = nullptr;
        other.shader = {};
        other.params[0] = 0.0f;
        other.params[1] = 0.0f;
        other.params[2] = 0.0f;
        other.params[3] = 0.0f;
    }

    ~Material() { Unload(); }

    /**
     * 从模型文件加载材质
     */
    static std::vector<Material> Load(const std::string& fileName) {
        int count = 0;
        // TODO(RobLoach): Material::Load() 可能会导致材质数组泄漏。
        ::Material* materials = ::LoadMaterials(fileName.c_str(), &count);
        return std::vector<Material>(materials, materials + count);
    }

    GETTERSETTER(::Shader, Shader, shader)
    GETTERSETTER(::MaterialMap*, Maps, maps)
    // TODO(RobLoach): 解决材质参数为 float[4] 的问题。
    // GETTERSETTER(float[4], Params, params)

    Material& operator=(const ::Material& material) {
        set(material);
        return *this;
    }

    Material& operator=(const Material&) = delete;

    Material& operator=(Material&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.maps = nullptr;
        other.shader = {};

        return *this;
    }

    /**
     * 从内存中卸载材质
     */
    void Unload() {
        if (maps != nullptr) {
            ::UnloadMaterial(*this);
            maps = nullptr;
        }
    }

    /**
     * 为材质的贴图类型设置纹理（MAP_DIFFUSE, MAP_SPECULAR...）
     */
    Material& SetTexture(int mapType, const ::Texture2D& texture) {
        ::SetMaterialTexture(this, mapType, texture);
        return *this;
    }

    /**
     * 使用材质和变换矩阵绘制3D网格
     */
    void DrawMesh(const ::Mesh& mesh, ::Matrix transform) const { ::DrawMesh(mesh, *this, transform); }

    /**
     * 使用材质和不同的变换矩阵绘制多个网格实例
     */
    void DrawMesh(const ::Mesh& mesh, ::Matrix* transforms, int instances) const {
        ::DrawMeshInstanced(mesh, *this, transforms, instances);
    }

    /**
     * 检查材质是否准备就绪
     */
    bool IsValid() const { return ::IsMaterialValid(*this); }
protected:
    void set(const ::Material& material) {
        shader = material.shader;
        maps = material.maps;
        params[0] = material.params[0];
        params[1] = material.params[1];
        params[2] = material.params[2];
        params[3] = material.params[3];
    }
};
} // namespace raylib

using RMaterial = raylib::Material;

// #endif // RAYLIB_CPP_INCLUDE_MATERIAL_HPP_