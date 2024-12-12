// #ifndef RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
// #define RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
#pragma once

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 音频流管理函数
 */
class 音频流 : public ::AudioStream {
public:
    音频流(const ::AudioStream& 音乐) { 设(音乐); }

    音频流(
        rAudioBuffer* 缓存 = nullptr,
        rAudioProcessor* 处理器 = nullptr,
        unsigned int 采样频率 = 0,
        unsigned int 采样大小 = 0,
        unsigned int 声道数 = 0)
        : ::AudioStream{缓存, 处理器, 采样频率, 采样大小, 声道数} {
        // 无操作
    }

    /**
     * 初始化音频流（用于流式传输原始音频 PCM 数据）
     *
     * @throws raylib::RaylibException 如果音频流加载失败，则抛出异常。
     */
    音频流(unsigned int 采样频率, unsigned int 采样大小, unsigned int 声道数 = 2) { 加载(采样频率, 采样大小, 声道数); }

    音频流(const 音频流&) = delete;

    音频流(音频流&& other) {
        设(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
    }

    ~音频流() { 卸载(); }

    GETTER(rAudioBuffer*, 缓存, buffer)
    GETTER(rAudioProcessor*, 处理器, processor)
    GETTER(unsigned int, 采样频率, sampleRate)
    GETTER(unsigned int, 采样大小, sampleSize)
    GETTER(unsigned int, 声道数, channels)

    音频流& operator=(const ::AudioStream& stream) {
        设(stream);
        return *this;
    }

    音频流& operator=(const 音频流&) = delete;

    音频流& operator=(音频流&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;

        return *this;
    }

    /**
     * 使用数据更新音频流缓冲区
     */
    音频流& 更新(const void* 数据, int 采样数) {
        ::UpdateAudioStream(*this, 数据, 采样数);
        return *this;
    }

    /**
     * 卸载音频流并释放内存
     */
    void 卸载() {
        if (是有效()) {
            ::UnloadAudioStream(*this);
        }
    }

    /**
     * 检查是否有任何音频流缓冲区需要重新填充
     */
    bool 是已处理的() const { return ::IsAudioStreamProcessed(*this); }

    /**
     * 播放音频流
     */
    音频流& 播放() {
        ::PlayAudioStream(*this);
        return *this;
    }

    /**
     * 暂停音频流
     */
    音频流& 暂停() {
        ::PauseAudioStream(*this);
        return *this;
    }

    /**
     * 恢复音频流
     */
    音频流& 恢复() {
        ::ResumeAudioStream(*this);
        return *this;
    }

    /**
     * 检查音频流是否正在播放
     */
    bool 是播放中() const { return ::IsAudioStreamPlaying(*this); }

    /**
     * 停止音频流
     */
    音频流& 停止() {
        ::StopAudioStream(*this);
        return *this;
    }

    /**
     * 设置音频流的音量（1.0 为最大音量）
     */
    音频流& 设音量(float 音量 = 1.0f) {
        ::SetAudioStreamVolume(*this, 音量);
        return *this;
    }

    /**
     * 设置音频流的音调（1.0 为基础音调）
     */
    音频流& 设音高(float 音高) {
        ::SetAudioStreamPitch(*this, 音高);
        return *this;
    }

    /**
     * 设置音频流的声道平衡（0.5 为中心）左声道<=>右声道
     */
    音频流& 设声像(float 声像 = 0.5f) {
        ::SetAudioStreamPan(*this, 声像);
        return *this;
    }

    /**
     * 设置新音频流的默认缓冲区大小
     */
    static void 设缓存大小为默认(int size) { ::SetAudioStreamBufferSizeDefault(size); }

    /**
     * 音频线程回调以请求新数据
     */
    void 设回调(::AudioCallback 回调) { ::SetAudioStreamCallback(*this, 回调); }

    /**
     * 将音频流处理器附加到流
     */
    void 绑定处理器(::AudioCallback 处理器) { ::AttachAudioStreamProcessor(*this, 处理器); }

    /**
     * 从流中分离音频流处理器
     */
    void 解绑处理器(::AudioCallback 处理器) { ::DetachAudioStreamProcessor(*this, 处理器); }

    /**
     * 检索音频流是否准备就绪
     */
    bool 是有效() const { return ::IsAudioStreamValid(*this); }

    /**
     * 加载音频流（用于流式传输原始音频 PCM 数据）
     *
     * @throws raylib::RaylibException 如果音频流加载失败，则抛出异常。
     */
    void 加载(unsigned int 采样频率, unsigned int 采样大小, unsigned int 声道数 = 2) {
        卸载();
        设(::LoadAudioStream(采样频率, 采样大小, 声道数));
        if (!是有效()) {
            throw RaylibException("音频流加载失败");
        }
    }
protected:
    void 设(const ::AudioStream& stream) {
        buffer = stream.buffer;
        processor = stream.processor;
        sampleRate = stream.sampleRate;
        sampleSize = stream.sampleSize;
        channels = stream.channels;
    }
};
} // namespace raylib

using R音频流 = raylib::音频流;

// #endif // RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
