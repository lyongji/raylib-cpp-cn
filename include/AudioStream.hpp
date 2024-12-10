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
class AudioStream : public ::AudioStream {
public:
    AudioStream(const ::AudioStream& music) { set(music); }

    AudioStream(
        rAudioBuffer* buffer = nullptr,
        rAudioProcessor* processor = nullptr,
        unsigned int sampleRate = 0,
        unsigned int sampleSize = 0,
        unsigned int channels = 0)
        : ::AudioStream{buffer, processor, sampleRate, sampleSize, channels} {
        // 无操作
    }

    /**
     * 初始化音频流（用于流式传输原始音频 PCM 数据）
     *
     * @throws raylib::RaylibException 如果音频流加载失败，则抛出异常。
     */
    AudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels = 2) {
        Load(sampleRate, sampleSize, channels);
    }

    AudioStream(const AudioStream&) = delete;

    AudioStream(AudioStream&& other) {
        set(other);

        other.buffer = nullptr;
        other.processor = nullptr;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
    }

    ~AudioStream() { Unload(); }

    GETTER(rAudioBuffer*, Buffer, buffer)
    GETTER(rAudioProcessor*, Processor, processor)
    GETTER(unsigned int, SampleRate, sampleRate)
    GETTER(unsigned int, SampleSize, sampleSize)
    GETTER(unsigned int, Channels, channels)

    AudioStream& operator=(const ::AudioStream& stream) {
        set(stream);
        return *this;
    }

    AudioStream& operator=(const AudioStream&) = delete;

    AudioStream& operator=(AudioStream&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

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
    AudioStream& Update(const void* data, int samplesCount) {
        ::UpdateAudioStream(*this, data, samplesCount);
        return *this;
    }

    /**
     * 卸载音频流并释放内存
     */
    void Unload() {
        if (IsValid()) {
            ::UnloadAudioStream(*this);
        }
    }

    /**
     * 检查是否有任何音频流缓冲区需要重新填充
     */
    bool IsProcessed() const { return ::IsAudioStreamProcessed(*this); }

    /**
     * 播放音频流
     */
    AudioStream& Play() {
        ::PlayAudioStream(*this);
        return *this;
    }

    /**
     * 暂停音频流
     */
    AudioStream& Pause() {
        ::PauseAudioStream(*this);
        return *this;
    }

    /**
     * 恢复音频流
     */
    AudioStream& Resume() {
        ::ResumeAudioStream(*this);
        return *this;
    }

    /**
     * 检查音频流是否正在播放
     */
    bool IsPlaying() const { return ::IsAudioStreamPlaying(*this); }

    /**
     * 停止音频流
     */
    AudioStream& Stop() {
        ::StopAudioStream(*this);
        return *this;
    }

    /**
     * 设置音频流的音量（1.0 为最大音量）
     */
    AudioStream& SetVolume(float volume = 1.0f) {
        ::SetAudioStreamVolume(*this, volume);
        return *this;
    }

    /**
     * 设置音频流的音调（1.0 为基础音调）
     */
    AudioStream& SetPitch(float pitch) {
        ::SetAudioStreamPitch(*this, pitch);
        return *this;
    }

    /**
     * 设置音频流的声道（0.5 为中心）
     */
    AudioStream& SetPan(float pan = 0.5f) {
        ::SetAudioStreamPan(*this, pan);
        return *this;
    }

    /**
     * 设置新音频流的默认缓冲区大小
     */
    static void SetBufferSizeDefault(int size) { ::SetAudioStreamBufferSizeDefault(size); }

    /**
     * 音频线程回调以请求新数据
     */
    void SetCallback(::AudioCallback callback) { ::SetAudioStreamCallback(*this, callback); }

    /**
     * 将音频流处理器附加到流
     */
    void AttachProcessor(::AudioCallback processor) { ::AttachAudioStreamProcessor(*this, processor); }

    /**
     * 从流中分离音频流处理器
     */
    void DetachProcessor(::AudioCallback processor) { ::DetachAudioStreamProcessor(*this, processor); }

    /**
     * 检索音频流是否准备就绪
     */
    bool IsValid() const { return ::IsAudioStreamValid(*this); }

    /**
     * 加载音频流（用于流式传输原始音频 PCM 数据）
     *
     * @throws raylib::RaylibException 如果音频流加载失败，则抛出异常。
     */
    void Load(unsigned int SampleRate, unsigned int SampleSize, unsigned int Channels = 2) {
        Unload();
        set(::LoadAudioStream(SampleRate, SampleSize, Channels));
        if (!IsValid()) {
            throw RaylibException("音频流加载失败");
        }
    }
protected:
    void set(const ::AudioStream& stream) {
        buffer = stream.buffer;
        processor = stream.processor;
        sampleRate = stream.sampleRate;
        sampleSize = stream.sampleSize;
        channels = stream.channels;
    }
};
} // namespace raylib

using RAudioStream = raylib::AudioStream;

// #endif // RAYLIB_CPP_INCLUDE_AUDIOSTREAM_HPP_
