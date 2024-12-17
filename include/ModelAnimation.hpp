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
    模型动画(const ::ModelAnimation& 模型) { 设(模型); }

    模型动画(const 模型动画&) = delete;

    模型动画(模型动画&& other) {
        设(other);

        other.boneCount = 0;
        other.frameCount = 0;
        other.bones = nullptr;
        other.framePoses = nullptr;
    }

    ~模型动画() { 卸载(); }

    /**
     * 从文件加载模型动画
     */
    static std::vector<模型动画> 加载(const std::string& 文件名) {
        int count = 0;
        ::ModelAnimation* 模型动画组 = ::LoadModelAnimations(文件名.c_str(), &count);
        std::vector<模型动画> 动画向量(模型动画组, 模型动画组 + count);

        RL_FREE(模型动画组);

        return 动画向量;
    }

    GETTERSETTER(int, 骨骼数量, boneCount)
    GETTERSETTER(::BoneInfo*, 骨骼, bones)
    GETTERSETTER(int, 帧数, frameCount)
    GETTERSETTER(::Transform**, 帧姿势, framePoses)

    模型动画& operator=(const ::ModelAnimation& 模型) {
        设(模型);
        return *this;
    }

    模型动画& operator=(const 模型动画&) = delete;

    模型动画& operator=(模型动画&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.boneCount = 0;
        other.frameCount = 0;
        other.bones = nullptr;
        other.framePoses = nullptr;

        return *this;
    }

    /**
     * 卸载动画数据
     */
    void 卸载() { ::UnloadModelAnimation(*this); }

    /**
     * 更新模型动画姿态
     */
    模型动画& 更新(const ::Model& 模型, int 帧) {
        ::UpdateModelAnimation(模型, *this, 帧);
        return *this;
    }

    /**
     * 更新模型动画网格骨骼矩阵（GPU蒙皮）
     */
    模型动画& 更新骨骼(const ::Model& 模型, int 帧) {
        ::UpdateModelAnimationBones(模型, *this, 帧);
        return *this;
    }

    /**
     * 检查模型动画骨骼是否匹配
     */
    bool 是有效(const ::Model& 模型) const { return ::IsModelAnimationValid(模型, *this); }
protected:
    void 设(const ::ModelAnimation& model) {
        boneCount = model.boneCount;
        frameCount = model.frameCount;
        bones = model.bones;
        framePoses = model.framePoses;

        // 复制名称。TextCopy() 使用空终止符，这里忽略。
        for (int i = 0; i < 32; i++) {
            name[i] = model.name[i];
        }
    }
};
} // namespace raylib

using R模型动画 = raylib::模型动画;

// #endif // RAYLIB_CPP_INCLUDE_MODELANIMATION_HPP_