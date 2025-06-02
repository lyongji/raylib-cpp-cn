// #ifndef RAYLIB_CPP_INCLUDE_MUSIC_HPP_
// #define RAYLIB_CPP_INCLUDE_MUSIC_HPP_
#pragma once

#include <format>
#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 音乐流类型（从内存中流式传输音频文件）
 */
class 音乐流 : public ::Music {
public:
  音乐流(::AudioStream 音频流 = {nullptr, nullptr, 0, 0, 0},
         unsigned int 帧数 = 0, bool 在循环播放 = false, int 环境类型 = 0,
         void *环境数据 = nullptr)
      : ::Music{.stream = 音频流,
                .frameCount = 帧数,
                .looping = 在循环播放,
                .ctxType = 环境类型,
                .ctxData = 环境数据} {}

  音乐流(const ::Music &音乐) : ::Music(音乐) {}

  音乐流(const std::string &文件路径) { 加载音乐(文件路径); }

  /**
   * 从内存加载音乐流
   *
   * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
   */
  音乐流(const std::string &文件类型, unsigned char *数据, int 数据大小) {
    加载音乐(文件类型, 数据, 数据大小);
  }

  音乐流(const 音乐流 &) = delete;

  音乐流(音乐流 &&other) noexcept {
    设(other);

    other.stream = {};
    other.frameCount = 0;
    other.looping = false;
    other.ctxType = 0;
    other.ctxData = nullptr;
  }

  /**
   * 卸载音乐流
   */
  ~音乐流() { 卸载音乐流(); }

  GETTER(::AudioStream, 音频流数据, stream)
  GETTER(unsigned int, 包含的帧数, frameCount)
  GETTERSETTER(bool, 在循环播放, looping)
  GETTER(int, 环境类型, ctxType)
  GETTER(void *, 环境数据, ctxData)

  音乐流 &operator=(const ::Music &音乐) {
    设(音乐);
    return *this;
  }

  音乐流 &operator=(const 音乐流 &) = delete;

  音乐流 &operator=(音乐流 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载音乐流();
    设(other);

    other.ctxType = 0;
    other.ctxData = nullptr;
    other.looping = false;
    other.frameCount = 0;
    other.stream = {};

    return *this;
  }

  void 卸载音乐流() { ::UnloadMusicStream(*this); }
  音乐流 &开始播放() {
    ::PlayMusicStream(*this);
    return *this;
  }

  /**
   * 更新音乐流的缓冲区
   */
  音乐流 &更新缓存() {
    ::UpdateMusicStream(*this);
    return *this;
  }

  音乐流 &停止播放() {
    ::StopMusicStream(*this);
    return *this;
  }

  音乐流 &暂停播放() {
    ::PauseMusicStream(*this);
    return *this;
  }

  音乐流 &恢复播放() {
    ::ResumeMusicStream(*this);
    return *this;
  }

  /**
   * 将音乐定位到指定位置（以秒为单位）
   */
  音乐流 &跳转到指定秒数(float 位置) {
    SeekMusicStream(*this, 位置);
    return *this;
  }

  [[nodiscard]] bool 检查是否正播放() const {
    return ::IsMusicStreamPlaying(*this);
  }

  音乐流 &设音量(float 音量) {
    ::SetMusicVolume(*this, 音量);
    return *this;
  }

  音乐流 &设音调(float 音调值) {
    ::SetMusicPitch(*this, 音调值);
    return *this;
  }

  /**
   * 设置音乐的声相（0.5 为中心）声道平衡 左声道<=>右声道
   */
  音乐流 &设声相(float 声相 = 0.5F) {
    ::SetMusicPan(*this, 声相);
    return *this;
  }

  /**
   * 获取音乐的总时长（以秒为单位）
   */
  [[nodiscard]] float 取总时常() const { return ::GetMusicTimeLength(*this); }

  /**
   * 获取当前播放的音乐时间（以秒为单位）
   */
  [[nodiscard]] float 取当前播放时间点() const {
    return ::GetMusicTimePlayed(*this);
  }

  void 加载音乐(const std::string &文件路径) {
    设(::LoadMusicStream(文件路径.c_str()));
    if (!检查可用性()) {
      throw Raylib异常(std::format("未能从文件 %s 加载音乐", 文件路径));
    }
  }

  /**
   * 从内存加载音乐流
   *
   * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
   */
  void 加载音乐(const std::string &文件类型, unsigned char *数据,
                int 数据大小) {
    设(::LoadMusicStreamFromMemory(文件类型.c_str(), 数据, 数据大小));
    if (!检查可用性()) {
      throw Raylib异常(std::format("未能从 %s 文件数据加载音乐", 文件类型));
    }
  }

  /**
   * 检查音乐是否已加载
   *
   * @return 如果音乐已加载，则返回 true，否则返回 false。
   */
  bool 检查可用性() const { return ::IsMusicValid(*this); }

protected:
  void 设(const ::Music &音乐) {
    stream = 音乐.stream;
    frameCount = 音乐.frameCount;
    looping = 音乐.looping;
    ctxType = 音乐.ctxType;
    ctxData = 音乐.ctxData;
  }
};
} // namespace raylib

using R音乐流 = raylib::音乐流;

// #endif // RAYLIB_CPP_INCLUDE_MUSIC_HPP_