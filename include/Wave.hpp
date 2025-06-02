// #ifndef RAYLIB_CPP_INCLUDE_WAVE_HPP_
// #define RAYLIB_CPP_INCLUDE_WAVE_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * Wave 类型，定义音频波形数据
 */
class 波形 : public ::Wave {
public:
  波形(const ::Wave &波形数据) : ::Wave(波形数据) {}

  波形(unsigned int 帧数 = 0, unsigned int 采样率 = 0,
       unsigned int 采样大小 = 0, unsigned int 声道数 = 0, void *数据 = nullptr)
      : ::Wave{.frameCount = 帧数,
               .sampleRate = 采样率,
               .sampleSize = 采样大小,
               .channels = 声道数,
               .data = 数据} {}

  波形(const std::string &文件路径) { 加载(文件路径); }

  /**
   * 从内存缓冲区加载波形数据，fileType 指文件扩展名，例如 "wav"
   *
   * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
   */
  波形(const std::string &文件类型, const unsigned char *文件数据,
       int 数据大小) {
    加载(文件类型, 文件数据, 数据大小);
  }

  波形(const 波形 &other) { 设(other.创建副本()); }

  波形(波形 &&other) noexcept {
    设(other);

    other.frameCount = 0;
    other.sampleRate = 0;
    other.sampleSize = 0;
    other.channels = 0;
    other.data = nullptr;
  }

  /**
   * 卸载波形数据
   */
  ~波形() { 卸载波形(); }

  GETTER(unsigned int, 帧数, frameCount)
  GETTER(unsigned int, 采样率, sampleRate)
  GETTER(unsigned int, 采样大小, sampleSize)
  GETTER(unsigned int, 声道个数, channels)
  GETTER(void *, 数据, data)

  波形 &operator=(const ::Wave &波形) {
    设(波形);
    return *this;
  }

  波形 &operator=(const 波形 &other) {
    if (this == &other) {
      return *this;
    }

    卸载波形();
    设(other.创建副本());

    return *this;
  }

  波形 &operator=(波形 &&other) noexcept {
    if (this != &other) {
      return *this;
    }

    卸载波形();
    设(other);

    other.frameCount = 0;
    other.sampleRate = 0;
    other.sampleSize = 0;
    other.channels = 0;
    other.data = nullptr;

    return *this;
  }

  [[nodiscard]] ::Wave 创建副本() const { return ::WaveCopy(*this); }

  /**
   * 裁剪波形数据到定义的样本范围
   */
  波形 &裁剪波形数据(int 初始采样, int 最终采样) {
    ::WaveCrop(this, 初始采样, 最终采样);
    return *this;
  }

  /**
   * 将波形数据转换为所需格式
   */
  波形 &转换格式(int 采样率, int 采样大小, int 声道数 = 2) {
    ::WaveFormat(this, 采样率, 采样大小, 声道数);
    return *this;
  }

  /**
   * 从波形加载样本数据为浮点数数组
   */
  float *加载样本数据() { return ::LoadWaveSamples(*this); }

  /**
   * 卸载通过 LoadWaveSamples() 加载的样本数据
   */
  static void 卸载样本数据(float *采样数据) { ::UnloadWaveSamples(采样数据); }

  /**
   * 将波形数据导出到文件，成功返回 true
   */
  bool 导出到文件(const std::string &文件路径) {
    // TODO(RobLoach): 错误时抛出异常
    return ::ExportWave(*this, 文件路径.c_str());
  }

  /**
   * 将波形样本数据导出为代码 (.h)，成功返回 true
   */
  bool 导出到代码文件(const std::string &文件路径) {
    // TODO(RobLoach): 错误时抛出异常
    return ::ExportWaveAsCode(*this, 文件路径.c_str());
  }

  /**
   * 卸载波形数据
   */
  void 卸载波形() {
    // 防止多次调用 UnloadWave()
    if (data != nullptr) {
      ::UnloadWave(*this);
      data = nullptr;
    }
  }

  /**
   * 从波形数据加载声音
   */
  ::Sound 转为音效() { return ::LoadSoundFromWave(*this); }

  /**
   * 从波形数据加载声音
   */
  operator ::Sound() { return 转为音效(); }

  /**
   * 从文件加载波形数据
   *
   * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
   */
  void 加载(const std::string &文件路径) {
    设(::LoadWave(文件路径.c_str()));
    if (!检查可用性()) {
      throw Raylib异常("无法从文件中加载: " + 文件路径);
    }
  }

  /**
   * 从内存缓冲区加载波形数据，fileType 指文件扩展名，例如 "wav"
   *
   * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
   */
  void 加载(const std::string &文件类型, const unsigned char *文件数据,
            int 文件大小) {
    设(::LoadWaveFromMemory(文件类型.c_str(), 文件数据, 文件大小));
    if (!检查可用性()) {
      throw Raylib异常("无法从文件数据加载波形，文件类型为:" + 文件类型);
    }
  }

  /**
   * 检索波形数据是否已加载
   *
   * @return 波形数据是否已加载的布尔值
   */
  [[nodiscard]] bool 检查可用性() const { return ::IsWaveValid(*this); }

protected:
  void 设(const ::Wave &wave) {
    frameCount = wave.frameCount;
    sampleRate = wave.sampleRate;
    sampleSize = wave.sampleSize;
    channels = wave.channels;
    data = wave.data;
  }
};

} // namespace raylib

using RWave = raylib::波形;
using R波形 = raylib::波形;

// #endif // RAYLIB_CPP_INCLUDE_WAVE_HPP_