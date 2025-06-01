// #ifndef RAYLIB_CPP_INCLUDE_SOUND_HPP_
// #define RAYLIB_CPP_INCLUDE_SOUND_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Wave/Sound 管理函数
 *
 * @code
 * raylib::Sound boom("boom.wav");
 * boom.Play();
 * @endcode
 */
class 音效 : public ::Sound {
public:
  音效(const 音效 &) = delete;
  音效 &operator=(const 音效 &) = delete;

  音效() {
    stream = {nullptr, nullptr, 0, 0, 0};
    frameCount = 0;
  }

  音效(::AudioStream 音频流, unsigned int 帧数) : ::Sound{音频流, 帧数} {}

  音效(音效 &&other) noexcept {
    设(other);

    other.stream = {nullptr, nullptr, 0, 0, 0};
    other.frameCount = 0;
  }

  音效(const std::string &文件路径) { 加载音效(文件路径); }

  音效(const ::Wave &波形) { 加载音效(波形); }

  ~音效() { 卸载音效(); }

  GETTER(unsigned int, 包含的帧数, frameCount)
  GETTER(::AudioStream, 音频流, stream)

  音效 &operator=(音效 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载音效();
    设(other);
    other.frameCount = 0;
    other.stream = {nullptr, nullptr, 0, 0, 0};

    return *this;
  }

  /**
   * 使用新数据更新声音缓冲区
   */
  音效 &更新缓存(const void *数据, int 采样数) {
    ::UpdateSound(*this, 数据, 采样数);
    return *this;
  }

  /**
   * 使用新数据更新声音缓冲区，假设样本数相同。
   */
  音效 &更新缓存(const void *数据) {
    ::UpdateSound(*this, 数据, static_cast<int>(frameCount));
    return *this;
  }

  void 卸载音效() {
    // 防止多次调用 UnloadSound()。
    if (frameCount != 0) {
      ::UnloadSound(*this);
      frameCount = 0;
    }
  }

  音效 &开始播放() {
    ::PlaySound(*this);
    return *this;
  }

  音效 &停止播放() {
    ::StopSound(*this);
    return *this;
  }

  音效 &暂停播放() {
    ::PauseSound(*this);
    return *this;
  }

  音效 &恢复播放() {
    ::ResumeSound(*this);
    return *this;
  }

  [[nodiscard]] bool 检查是否正播放() const { return ::IsSoundPlaying(*this); }

  /**
   * 设置声音的音量（1.0 是最大音量）
   */
  音效 &设音量(float 音量) {
    ::SetSoundVolume(*this, 音量);
    return *this;
  }

  /**
   * 设置声音的音调（1.0 是基准音调）
   */
  音效 &设音调(float 音调) {
    ::SetSoundPitch(*this, 音调);
    return *this;
  }

  /**
   * 设置声音的声相（0.5 是中心）
   */
  音效 &设声相(float 声相 = 0.5f) {
    ::SetSoundPan(*this, 声相);
    return *this;
  }

  void 加载音效(const std::string &文件路径) {
    设(::LoadSound(文件路径.c_str()));
    if (!检查可用性()) {
      throw Raylib异常("从文件加载声音失败");
    }
  }

  void 加载音效(const ::Wave &波形) {
    设(::LoadSoundFromWave(波形));
    if (!检查可用性()) {
      throw Raylib异常("加载波形失败");
    }
  }

  /**
   * 检索声音缓冲区是否已加载。
   *
   * @return 根据声音缓冲区是否已加载返回 true 或 false。
   */
  [[nodiscard]] bool 检查可用性() const { return ::IsSoundValid(*this); }

protected:
  void 设(const ::Sound &音效) {
    frameCount = 音效.frameCount;
    stream = 音效.stream;
  }
};
} // namespace raylib

using R音效 = raylib::音效;

// #endif // RAYLIB_CPP_INCLUDE_SOUND_HPP_