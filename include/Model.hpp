// #ifndef RAYLIB_CPP_INCLUDE_MODEL_HPP_
// #define RAYLIB_CPP_INCLUDE_MODEL_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
class 网格;
/**
 * 模型类型
 */
class 模型 : public ::Model {
public:
    模型() = default;

    /*
     * 从另一个模型复制模型。
     */
    模型(const ::Model& 模型) : ::Model(模型) {}

    /*
     * 从文件加载模型。
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    模型(const std::string& 文件名) { 加载(文件名); }

    /*
     * 从网格加载模型。
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    模型(const ::Mesh& 网格) { 加载(网格); }

    /**
     * 带有 Mesh() 构造函数的 Model 已被移除。
     *
     * 请使用 `raylib::MeshUnmanaged` 或 `::Mesh` 代替，因为 raylib 将接管数据的所有权。
     *
     * @see raylib::MeshUnmanaged
     */
    模型(const raylib::网格& 网格) = delete;

    ~模型() { 卸载(); }

    模型(const 模型&) = delete;

    模型(模型&& other) noexcept {
        设(other);

        other.meshCount = 0;
        other.materialCount = 0;
        other.meshes = nullptr;
        other.materials = nullptr;
        other.meshMaterial = nullptr;
        other.boneCount = 0;
        other.bones = nullptr;
        other.bindPose = nullptr;
    }

    GETTERSETTER(::Matrix, 变换, transform)
    GETTERSETTER(int, 网格数量, meshCount)
    GETTERSETTER(int, 材质数量, materialCount)
    GETTERSETTER(::Mesh*, 网格, meshes)
    GETTERSETTER(::Material*, 材质, materials)
    GETTERSETTER(int*, 网格材质, meshMaterial)
    GETTERSETTER(int, 骨骼数量, boneCount)
    GETTERSETTER(::BoneInfo*, 骨骼, bones)
    GETTERSETTER(::Transform*, 绑定姿势, bindPose)

    模型& operator=(const ::Model& 模型) {
        设(模型);
        return *this;
    }

    模型& operator=(const 模型&) = delete;

    模型& operator=(模型&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.meshCount = 0;
        other.materialCount = 0;
        other.meshes = nullptr;
        other.materials = nullptr;
        other.meshMaterial = nullptr;
        other.boneCount = 0;
        other.bones = nullptr;
        other.bindPose = nullptr;

        return *this;
    }

    /**
     * 从内存中卸载模型（包括网格）（RAM 和/或 VRAM）
     */
    void 卸载() {
        if (meshes != nullptr || materials != nullptr) {
            ::UnloadModel(*this);
            meshes = nullptr;
            materials = nullptr;
        }
    }

    /**
     * 为网格设置材质
     */
    模型& 设网格材质(int 网格ID, int 材质) {
        ::SetModelMeshMaterial(this, 网格ID, 材质);
        return *this;
    }

    /**
     * 更新模型动画姿态
     */
    模型& 更新动画(const ::ModelAnimation& 动画, int 帧) {
        ::UpdateModelAnimation(*this, 动画, 帧);
        return *this;
    }

    /**
     * 更新模型动画骨骼
     */
    模型& 更新动画骨骼(const ::ModelAnimation& 动画, int 帧) {
        ::UpdateModelAnimationBones(*this, 动画, 帧);
        return *this;
    }

    /**
     * 检查模型动画骨骼是否匹配
     */
    [[nodiscard]] bool 是有效的模型动画(const ::ModelAnimation& 动画) const {
        return ::IsModelAnimationValid(*this, 动画);
    }

    /**
     * 绘制模型（如果设置了纹理）
     */
    void 绘制(::Vector3 位置, float 缩放 = 1.0f, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawModel(*this, 位置, 缩放, 色调);
    }

    /**
     * 使用扩展参数绘制模型
     */
    void 绘制(
        ::Vector3 位置,
        ::Vector3 旋转轴,
        float 旋转角度 = 0.0f,
        ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
        ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawModelEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
    }

    /**
     * 绘制模型的线框（如果设置了纹理）
     */
    void 绘制线框(::Vector3 位置, float 缩放 = 1.0f, ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawModelWires(*this, 位置, 缩放, 色调);
    }

    /**
     * 使用扩展参数绘制模型的线框
     */
    void 绘制线框(
        ::Vector3 位置,
        ::Vector3 旋转轴,
        float 旋转角度 = 0.0f,
        ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
        ::Color 色调 = {255, 255, 255, 255}) const {
        ::DrawModelWiresEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
    }

    /**
     * 将模型绘制为点
     */
    void 绘制顶点(::Vector3 位置, float 缩放 = 1.0f, ::Color 色调 = {255, 255, 255, 255}) {
        ::DrawModelPoints(*this, 位置, 缩放, 色调);
    }

    /**
     * 使用扩展参数将模型绘制为点
     */
    void 绘制顶点(
        ::Vector3 位置,
        ::Vector3 旋转轴,
        float 旋转角度 = 0.0f,
        ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
        ::Color 色调 = {255, 255, 255, 255}) {
        ::DrawModelPointsEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
    }

    /**
     * 计算模型的包围盒限制（考虑所有网格）
     */
    [[nodiscard]] BoundingBox 取包围盒() const { return ::GetModelBoundingBox(*this); }

    /**
     * 计算模型的包围盒限制（考虑所有网格）
     */
    explicit operator BoundingBox() const { return ::GetModelBoundingBox(*this); }

    /**
     * 确定模型是否包含数据
     */
    [[nodiscard]] bool 是有效() const { return ::IsModelValid(*this); }

    /**
     * 从给定文件加载模型
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    void 加载(const std::string& 文件名) {
        设(::LoadModel(文件名.c_str()));
        if (!是有效()) {
            throw Raylib异常("加载模型失败:" + 文件名);
        }
    }

    /**
     * 从给定网格加载模型
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    void 加载(const ::Mesh& 网格) {
        设(::LoadModelFromMesh(网格));
        if (!是有效()) {
            throw Raylib异常("未能从网格加载模型");
        }
    }
protected:
    void 设(const ::Model& 模型) {
        transform = 模型.transform;

        meshCount = 模型.meshCount;
        materialCount = 模型.materialCount;
        meshes = 模型.meshes;
        materials = 模型.materials;
        meshMaterial = 模型.meshMaterial;

        boneCount = 模型.boneCount;
        bones = 模型.bones;
        bindPose = 模型.bindPose;
    }
};

} // namespace raylib

using R模型 = raylib::模型;

// #endif // RAYLIB_CPP_INCLUDE_MODEL_HPP_