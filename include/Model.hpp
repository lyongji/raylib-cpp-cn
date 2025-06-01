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

  模型(const ::Model &模型) : ::Model(模型) {}

  模型(const std::string &文件路径) { 加载模型(文件路径); }

  模型(const ::Mesh &网格) { 加载模型(网格); }

  /**
   * 带有 Mesh() 构造函数的 Model 已被移除。
   *
   * 请使用 `raylib::MeshUnmanaged` 或 `::Mesh` 代替，因为 raylib
   * 将接管数据的所有权。
   *
   * @see raylib::MeshUnmanaged
   */
  模型(const raylib::网格 &网格) = delete;

  ~模型() { 卸载模型(); }

  模型(const 模型 &) = delete;

  模型(模型 &&other) noexcept {
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
  // 模型、网格、材质和动画数据
  GETTERSETTER(::Matrix, 局部变换, transform) // 局部变换矩阵
  GETTERSETTER(int, 包含的网格数量, meshCount)
  GETTERSETTER(int, 包含的材质数量, materialCount)
  GETTERSETTER(::Mesh *, 网格数组, meshes)
  GETTERSETTER(::Material *, 材质数组, materials)
  GETTERSETTER(int *, 网格对应网格材质号, meshMaterial)
  // 动画数据
  GETTERSETTER(int, 包含的骨骼数量, boneCount)
  GETTERSETTER(::BoneInfo *, 骨骼信息数组, bones) // 骨骼信息（skeleton）
  GETTERSETTER(::Transform *, 绑定姿势, bindPose) // 骨骼基础变换（pose）

  模型 &operator=(const ::Model &模型) {
    设(模型);
    return *this;
  }

  模型 &operator=(const 模型 &) = delete;

  模型 &operator=(模型 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载模型();
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
  void 卸载模型() {
    if (meshes != nullptr || materials != nullptr) {
      ::UnloadModel(*this);
      meshes = nullptr;
      materials = nullptr;
    }
  }

  模型 &设网格材质(int 网格ID, int 材质ID) {
    ::SetModelMeshMaterial(this, 网格ID, 材质ID);
    return *this;
  }

  /**
   * 更新模型动画姿态
   */
  模型 &更新动画(const ::ModelAnimation &动画, int 帧索引) {
    ::UpdateModelAnimation(*this, 动画, 帧索引);
    return *this;
  }

  /**
   * 更新模型动画骨骼
   */
  模型 &更新动画骨骼(const ::ModelAnimation &动画, int 帧索引) {
    ::UpdateModelAnimationBones(*this, 动画, 帧索引);
    return *this;
  }

  [[nodiscard]] bool
  检查动画与骨骼是否匹配(const ::ModelAnimation &动画) const {
    return ::IsModelAnimationValid(*this, 动画);
  }

  /**
   * 绘制模型（如果设置了纹理）
   */
  void 绘制模型(::Vector3 位置, float 缩放 = 1.0f,
                ::Color 色调 = {255, 255, 255, 255}) const {
    ::DrawModel(*this, 位置, 缩放, 色调);
  }

  void 绘制模型(::Vector3 位置, ::Vector3 旋转轴, float 旋转角度 = 0.0f,
                ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
                ::Color 色调 = {255, 255, 255, 255}) const {
    ::DrawModelEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
  }

  /**
   * 绘制模型的线框（如果设置了纹理）
   */
  void 绘制线框(::Vector3 位置, float 缩放 = 1.0f,
                ::Color 色调 = {255, 255, 255, 255}) const {
    ::DrawModelWires(*this, 位置, 缩放, 色调);
  }

  void 绘制线框(::Vector3 位置, ::Vector3 旋转轴, float 旋转角度 = 0.0f,
                ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
                ::Color 色调 = {255, 255, 255, 255}) const {
    ::DrawModelWiresEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
  }

  void 绘制顶点(::Vector3 位置, float 缩放 = 1.0f,
                ::Color 色调 = {255, 255, 255, 255}) {
    ::DrawModelPoints(*this, 位置, 缩放, 色调);
  }

  void 绘制顶点(::Vector3 位置, ::Vector3 旋转轴, float 旋转角度 = 0.0f,
                ::Vector3 缩放 = {1.0f, 1.0f, 1.0f},
                ::Color 色调 = {255, 255, 255, 255}) {
    ::DrawModelPointsEx(*this, 位置, 旋转轴, 旋转角度, 缩放, 色调);
  }

  /**
   * 计算模型的包围盒限制（考虑所有网格）
   */
  [[nodiscard]] BoundingBox 取包围盒() const {
    return ::GetModelBoundingBox(*this);
  }

  /**
   * 计算模型的包围盒限制（考虑所有网格）
   */
  explicit operator BoundingBox() const { return ::GetModelBoundingBox(*this); }

  /**
   * 确定模型是否包含数据
   */
  [[nodiscard]] bool 检查可用性() const { return ::IsModelValid(*this); }

  void 加载模型(const std::string &文件路径) {
    设(::LoadModel(文件路径.c_str()));
    if (!检查可用性()) {
      throw Raylib异常("加载模型失败:" + 文件路径);
    }
  }

  void 加载模型(const ::Mesh &网格) {
    设(::LoadModelFromMesh(网格));
    if (!检查可用性()) {
      throw Raylib异常("未能从网格加载模型");
    }
  }

protected:
  void 设(const ::Model &模型) {
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