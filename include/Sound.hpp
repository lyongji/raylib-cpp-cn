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
class Sound : public ::Sound {
public:
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    Sound() {
        stream = {nullptr, nullptr, 0, 0, 0};
        frameCount = 0;
    }

    Sound(::AudioStream stream, unsigned int frameCount) : ::Sound{stream, frameCount} {
        // 无操作。
    }

    Sound(Sound&& other) {
        set(other);

        other.stream = {nullptr, nullptr, 0, 0, 0};
        other.frameCount = 0;
    }

    /**
     * 从给定的文件加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    Sound(const std::string& fileName) { Load(fileName); }

    /**
     * 从给定的 Wave 加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    Sound(const ::Wave& wave) { Load(wave); }

    ~Sound() { Unload(); }

    GETTER(unsigned int, FrameCount, frameCount)
    GETTER(::AudioStream, Stream, stream)

    Sound& operator=(Sound&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);
        other.frameCount = 0;
        other.stream = {nullptr, nullptr, 0, 0, 0};

        return *this;
    }

    /**
     * 使用新数据更新声音缓冲区
     */
    Sound& Update(const void* data, int samplesCount) {
        ::UpdateSound(*this, data, samplesCount);
        return *this;
    }

    /**
     * 使用新数据更新声音缓冲区，假设样本数相同。
     */
    Sound& Update(const void* data) {
        ::UpdateSound(*this, data, static_cast<int>(frameCount));
        return *this;
    }

    /**
     * 卸载声音
     */
    void Unload() {
        // 防止多次调用 UnloadSound()。
        if (frameCount != 0) {
            ::UnloadSound(*this);
            frameCount = 0;
        }
    }

    /**
     * 播放声音
     */
    Sound& Play() {
        ::PlaySound(*this);
        return *this;
    }

    /**
     * 停止播放声音
     */
    Sound& Stop() {
        ::StopSound(*this);
        return *this;
    }

    /**
     * 暂停声音
     */
    Sound& Pause() {
        ::PauseSound(*this);
        return *this;
    }

    /**
     * 恢复暂停的声音
     */
    Sound& Resume() {
        ::ResumeSound(*this);
        return *this;
    }

    /**
     * 检查声音是否正在播放
     */
    bool IsPlaying() const { return ::IsSoundPlaying(*this); }

    /**
     * 设置声音的音量（1.0 是最大音量）
     */
    Sound& SetVolume(float volume) {
        ::SetSoundVolume(*this, volume);
        return *this;
    }

    /**
     * 设置声音的音调（1.0 是基准音调）
     */
    Sound& SetPitch(float pitch) {
        ::SetSoundPitch(*this, pitch);
        return *this;
    }

    /**
     * 设置声音的声相（0.5 是中心）
     */
    Sound& SetPan(float pan = 0.5f) {
        ::SetSoundPan(*this, pan);
        return *this;
    }

    /**
     * 从给定的文件加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    void Load(const std::string& fileName) {
        set(::LoadSound(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("从文件加载声音失败");
        }
    }

    /**
     * 将给定的 Wave 对象加载到声音中。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    void Load(const ::Wave& wave) {
        set(::LoadSoundFromWave(wave));
        if (!IsValid()) {
            throw RaylibException("加载 Wave 失败");
        }
    }

    /**
     * 检索声音缓冲区是否已加载。
     *
     * @return 根据声音缓冲区是否已加载返回 true 或 false。
     */
    bool IsValid() const { return ::IsSoundValid(*this); }
protected:
    void set(const ::Sound& sound) {
        frameCount = sound.frameCount;
        stream = sound.stream;
    }
};
} // namespace raylib

using RSound = raylib::Sound;

// #endif // RAYLIB_CPP_INCLUDE_SOUND_HPP_