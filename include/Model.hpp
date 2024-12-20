// #ifndef RAYLIB_CPP_INCLUDE_MODEL_HPP_
// #define RAYLIB_CPP_INCLUDE_MODEL_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
class Mesh;
/**
 * 模型类型
 */
class Model : public ::Model {
public:
    Model() {
        // 无操作
    }

    /*
     * 从另一个模型复制模型。
     */
    Model(const ::Model& model) : ::Model(model) { }

    /*
     * 从文件加载模型。
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    Model(const std::string& fileName) { Load(fileName); }

    /*
     * 从网格加载模型。
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    Model(const ::Mesh& mesh) { Load(mesh); }

    /**
     * 带有 Mesh() 构造函数的 Model 已被移除。
     *
     * 请使用 `raylib::MeshUnmanaged` 或 `::Mesh` 代替，因为 raylib 将接管数据的所有权。
     *
     * @see raylib::MeshUnmanaged
     */
    Model(const raylib::Mesh& mesh) = delete;

    ~Model() { Unload(); }

    Model(const Model&) = delete;

    Model(Model&& other) noexcept {
        set(other);

        other.meshCount = 0;
        other.materialCount = 0;
        other.meshes = nullptr;
        other.materials = nullptr;
        other.meshMaterial = nullptr;
        other.boneCount = 0;
        other.bones = nullptr;
        other.bindPose = nullptr;
    }

    GETTERSETTER(::Matrix, Transform, transform)
    GETTERSETTER(int, MeshCount, meshCount)
    GETTERSETTER(int, MaterialCount, materialCount)
    GETTERSETTER(::Mesh*, Meshes, meshes)
    GETTERSETTER(::Material*, Materials, materials)
    GETTERSETTER(int*, MeshMaterial, meshMaterial)
    GETTERSETTER(int, BoneCount, boneCount)
    GETTERSETTER(::BoneInfo*, Bones, bones)
    GETTERSETTER(::Transform*, BindPose, bindPose)

    Model& operator=(const ::Model& model) {
        set(model);
        return *this;
    }

    Model& operator=(const Model&) = delete;

    Model& operator=(Model&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

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
    void Unload() {
        if (meshes != nullptr || materials != nullptr) {
            ::UnloadModel(*this);
            meshes = nullptr;
            materials = nullptr;
        }
    }

    /**
     * 为网格设置材质
     */
    Model& SetMeshMaterial(int meshId, int materialId) {
        ::SetModelMeshMaterial(this, meshId, materialId);
        return *this;
    }

    /**
     * 更新模型动画姿态
     */
    Model& UpdateAnimation(const ::ModelAnimation& anim, int frame) {
        ::UpdateModelAnimation(*this, anim, frame);
        return *this;
    }

    /**
     * 更新模型动画骨骼
     */
    Model& UpdateAnimationBones(const ::ModelAnimation& anim, int frame) {
        ::UpdateModelAnimationBones(*this, anim, frame);
        return *this;
    }

    /**
     * 检查模型动画骨骼是否匹配
     */
    [[nodiscard]] bool IsModelAnimationValid(const ::ModelAnimation& anim) const { return ::IsModelAnimationValid(*this, anim); }

    /**
     * 绘制模型（如果设置了纹理）
     */
    void Draw(::Vector3 position, float scale = 1.0f, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawModel(*this, position, scale, tint);
    }

    /**
     * 使用扩展参数绘制模型
     */
    void Draw(
        ::Vector3 position,
        ::Vector3 rotationAxis,
        float rotationAngle = 0.0f,
        ::Vector3 scale = {1.0f, 1.0f, 1.0f},
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawModelEx(*this, position, rotationAxis, rotationAngle, scale, tint);
    }

    /**
     * 绘制模型的线框（如果设置了纹理）
     */
    void DrawWires(::Vector3 position, float scale = 1.0f, ::Color tint = {255, 255, 255, 255}) const {
        ::DrawModelWires(*this, position, scale, tint);
    }

    /**
     * 使用扩展参数绘制模型的线框
     */
    void DrawWires(
        ::Vector3 position,
        ::Vector3 rotationAxis,
        float rotationAngle = 0.0f,
        ::Vector3 scale = {1.0f, 1.0f, 1.0f},
        ::Color tint = {255, 255, 255, 255}) const {
        ::DrawModelWiresEx(*this, position, rotationAxis, rotationAngle, scale, tint);
    }

    /**
     * 将模型绘制为点
     */
    void DrawPoints(::Vector3 position, float scale = 1.0f, ::Color tint = {255, 255, 255, 255}) {
        ::DrawModelPoints(*this, position, scale, tint);
    }

    /**
     * 使用扩展参数将模型绘制为点
     */
    void DrawPoints(
        ::Vector3 position,
        ::Vector3 rotationAxis,
        float rotationAngle = 0.0f,
        ::Vector3 scale = {1.0f, 1.0f, 1.0f},
        ::Color tint = {255, 255, 255, 255}) {
        ::DrawModelPointsEx(*this, position, rotationAxis, rotationAngle, scale, tint);
    }

    /**
     * 计算模型的包围盒限制（考虑所有网格）
     */
    [[nodiscard]] BoundingBox GetBoundingBox() const { return ::GetModelBoundingBox(*this); }

    /**
     * 计算模型的包围盒限制（考虑所有网格）
     */
    explicit operator BoundingBox() const { return ::GetModelBoundingBox(*this); }

    /**
     * 确定模型是否包含数据
     */
    [[nodiscard]] bool IsValid() const { return ::IsModelValid(*this); }

    /**
     * 从给定文件加载模型
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    void Load(const std::string& fileName) {
        set(::LoadModel(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("Failed to load Model from " + fileName);
        }
    }

    /**
     * 从给定网格加载模型
     *
     * @throws raylib::RaylibException 如果加载模型失败，则抛出异常。
     */
    void Load(const ::Mesh& mesh) {
        set(::LoadModelFromMesh(mesh));
        if (!IsValid()) {
            throw RaylibException("Failed to load Model from Mesh");
        }
    }
protected:
    void set(const ::Model& model) {
        transform = model.transform;

        meshCount = model.meshCount;
        materialCount = model.materialCount;
        meshes = model.meshes;
        materials = model.materials;
        meshMaterial = model.meshMaterial;

        boneCount = model.boneCount;
        bones = model.bones;
        bindPose = model.bindPose;
    }
};

} // namespace raylib

using RModel = raylib::Model;

// #endif // RAYLIB_CPP_INCLUDE_MODEL_HPP_