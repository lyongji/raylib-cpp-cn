// #ifndef RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_
// #define RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_
#pragma once

#include <string>
#include <vector>

#include "./Mesh.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 模型动画
 */
class 模型动画 : public ::ModelAnimation {
public:
  模型动画(const ::ModelAnimation &模型) { 设(模型); }

  模型动画(const 模型动画 &) = delete;

  模型动画(模型动画 &&other) noexcept {
    设(other);

    other.boneCount = 0;
    other.frameCount = 0;
    other.bones = nullptr;
    other.framePoses = nullptr;
  }

  ~模型动画() { 卸载动画数据(); }

  static std::vector<模型动画> 加载动画(const std::string &文件路径) {
    int 动画数量 = 0;
    ::ModelAnimation *模型动画数组 =
        ::LoadModelAnimations(文件路径.c_str(), &动画数量);
    std::vector<模型动画> 动画列表(模型动画数组, 模型动画数组 + 动画数量);

    RL_FREE(模型动画数组);

    return 动画列表;
  }

  GETTERSETTER(int, 包含的骨骼数量, boneCount)
  GETTERSETTER(::BoneInfo *, 骨骼信息数组, bones)
  GETTERSETTER(int, 包含的帧数, frameCount)
  GETTERSETTER(::Transform **, 帧姿势数组, framePoses)

  模型动画 &operator=(const ::ModelAnimation &模型) {
    设(模型);
    return *this;
  }

  模型动画 &operator=(const 模型动画 &) = delete;

  模型动画 &operator=(模型动画 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载动画数据();
    设(other);

    other.boneCount = 0;
    other.frameCount = 0;
    other.bones = nullptr;
    other.framePoses = nullptr;

    return *this;
  }

  void 卸载动画数据() { ::UnloadModelAnimation(*this); }

  模型动画 &更新动画(const ::Model &模型, int 帧索引) {
    ::UpdateModelAnimation(模型, *this, 帧索引);
    return *this;
  }

  /**
   * 更新模型动画网格骨骼矩阵（GPU蒙皮）
   */
  模型动画 &更新骨骼矩阵(const ::Model &模型, int 帧索引) {
    ::UpdateModelAnimationBones(模型, *this, 帧索引);
    return *this;
  }

  /**
   * 检查模型动画骨骼是否匹配
   */
  [[nodiscard]] bool 检查可用性(const ::Model &模型) const {
    return ::IsModelAnimationValid(模型, *this);
  }

protected:
  void 设(const ::ModelAnimation &模型) {
    boneCount = 模型.boneCount;
    frameCount = 模型.frameCount;
    bones = 模型.bones;
    framePoses = 模型.framePoses;

    // 复制名称。TextCopy() 使用空终止符，这里忽略。
    for (int i = 0; i < 32; i++) {
      name[i] = 模型.name[i];
    }
  }
};
} // namespace raylib

using R模型动画 = raylib::模型动画;

// #endif // RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_