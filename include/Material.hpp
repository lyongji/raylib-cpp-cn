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
class 材质 : public ::Material {
public:
    材质(const ::Material& 材质) { 设(材质); }

    /**
     * 加载默认材质（支持：漫反射、镜面反射、法线贴图）
     */
    材质() { 设(LoadMaterialDefault()); }

    材质(const 材质&) = delete;

    材质(材质&& other) {
        设(other);

        other.maps = nullptr;
        other.shader = {};
        other.params[0] = 0.0f;
        other.params[1] = 0.0f;
        other.params[2] = 0.0f;
        other.params[3] = 0.0f;
    }

    ~材质() { 卸载(); }

    /**
     * 从模型文件加载材质
     */
    static std::vector<材质> 加载(const std::string& 文件名) {
        int count = 0;
        // TODO(RobLoach): Material::Load() 可能会导致材质数组泄漏。
        ::Material* materials = ::LoadMaterials(文件名.c_str(), &count);
        return std::vector<材质>(materials, materials + count);
    }

    GETTERSETTER(::Shader, 着色器, shader)
    GETTERSETTER(::MaterialMap*, 材质贴图, maps)
    // TODO(RobLoach): 解决材质参数为 float[4] 的问题。
    // GETTERSETTER(float[4], Params, params)

    材质& operator=(const ::Material& 材质) {
        设(材质);
        return *this;
    }

    材质& operator=(const 材质&) = delete;

    材质& operator=(材质&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.maps = nullptr;
        other.shader = {};

        return *this;
    }

    /**
     * 从内存中卸载材质
     */
    void 卸载() {
        if (maps != nullptr) {
            ::UnloadMaterial(*this);
            maps = nullptr;
        }
    }

    /**
     * 为材质的贴图类型设置纹理（MAP_DIFFUSE, MAP_SPECULAR...）
     */
    材质& 设纹理(int 贴图类型, const ::Texture2D& 纹理) {
        ::SetMaterialTexture(this, 贴图类型, 纹理);
        return *this;
    }

    /**
     * 使用材质和变换矩阵绘制3D网格
     */
    void 绘制网格(const ::Mesh& 网格, ::Matrix 变换矩阵) const { ::DrawMesh(网格, *this, 变换矩阵); }

    /**
     * 使用材质和不同的变换矩阵绘制多个网格实例
     */
    void 绘制网格(const ::Mesh& 网格, ::Matrix* 变换矩阵, int 实例) const {
        ::DrawMeshInstanced(网格, *this, 变换矩阵, 实例);
    }

    /**
     * 检查材质是否准备就绪
     */
    bool 是就绪() const { return ::IsMaterialValid(*this); }
protected:
    void 设(const ::Material& material) {
        shader = material.shader;
        maps = material.maps;
        params[0] = material.params[0];
        params[1] = material.params[1];
        params[2] = material.params[2];
        params[3] = material.params[3];
    }
};
} // namespace raylib

using R材质 = raylib::材质;

// #endif // RAYLIB_CPP_INCLUDE_MATERIAL_HPP_