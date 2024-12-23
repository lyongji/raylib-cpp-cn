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
    音效(const 音效&) = delete;
    音效& operator=(const 音效&) = delete;

    音效() {
        stream = {nullptr, nullptr, 0, 0, 0};
        frameCount = 0;
    }

    音效(::AudioStream 音频流, unsigned int 帧数) : ::Sound{音频流, 帧数} {
        // 无操作。
    }

    音效(音效&& other) noexcept {
        设(other);

        other.stream = {nullptr, nullptr, 0, 0, 0};
        other.frameCount = 0;
    }

    /**
     * 从给定的文件加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    音效(const std::string& 文件名) { 加载(文件名); }

    /**
     * 从给定的 Wave 加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    音效(const ::Wave& 波) { 加载(波); }

    ~音效() { 卸载(); }

    GETTER(unsigned int, 帧数, frameCount)
    GETTER(::AudioStream, 音频流, stream)

    音效& operator=(音效&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);
        other.frameCount = 0;
        other.stream = {nullptr, nullptr, 0, 0, 0};

        return *this;
    }

    /**
     * 使用新数据更新声音缓冲区
     */
    音效& 更新(const void* 数据, int 采样数) {
        ::UpdateSound(*this, 数据, 采样数);
        return *this;
    }

    /**
     * 使用新数据更新声音缓冲区，假设样本数相同。
     */
    音效& 更新(const void* 数据) {
        ::UpdateSound(*this, 数据, static_cast<int>(frameCount));
        return *this;
    }

    /**
     * 卸载声音
     */
    void 卸载() {
        // 防止多次调用 UnloadSound()。
        if (frameCount != 0) {
            ::UnloadSound(*this);
            frameCount = 0;
        }
    }

    /**
     * 播放声音
     */
    音效& 播放() {
        ::PlaySound(*this);
        return *this;
    }

    /**
     * 停止播放声音
     */
    音效& 停止() {
        ::StopSound(*this);
        return *this;
    }

    /**
     * 暂停声音
     */
    音效& 暂停() {
        ::PauseSound(*this);
        return *this;
    }

    /**
     * 恢复暂停的声音
     */
    音效& 恢复() {
        ::ResumeSound(*this);
        return *this;
    }

    /**
     * 检查声音是否正在播放
     */
    [[nodiscard]] bool 是播放中() const { return ::IsSoundPlaying(*this); }

    /**
     * 设置声音的音量（1.0 是最大音量）
     */
    音效& 设音量(float 音量) {
        ::SetSoundVolume(*this, 音量);
        return *this;
    }

    /**
     * 设置声音的音调（1.0 是基准音调）
     */
    音效& 设音调(float 音调) {
        ::SetSoundPitch(*this, 音调);
        return *this;
    }

    /**
     * 设置声音的声相（0.5 是中心）
     */
    音效& 设声相(float 声相 = 0.5f) {
        ::SetSoundPan(*this, 声相);
        return *this;
    }

    /**
     * 从给定的文件加载声音。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    void 加载(const std::string& 文件名) {
        设(::LoadSound(文件名.c_str()));
        if (!是有效()) {
            throw Raylib异常("从文件加载声音失败");
        }
    }

    /**
     * 将给定的 Wave 对象加载到声音中。
     *
     * @throws raylib::RaylibException 如果声音加载失败，抛出异常。
     */
    void 加载(const ::Wave& wave) {
        设(::LoadSoundFromWave(wave));
        if (!是有效()) {
            throw Raylib异常("加载 Wave 失败");
        }
    }

    /**
     * 检索声音缓冲区是否已加载。
     *
     * @return 根据声音缓冲区是否已加载返回 true 或 false。
     */
    [[nodiscard]] bool 是有效() const { return ::IsSoundValid(*this); }
protected:
    void 设(const ::Sound& 音效) {
        frameCount = 音效.frameCount;
        stream = 音效.stream;
    }
};
} // namespace raylib

using R音效 = raylib::音效;

// #endif // RAYLIB_CPP_INCLUDE_SOUND_HPP_