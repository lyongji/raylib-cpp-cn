// #ifndef RAYLIB_CPP_INCLUDE_MUSIC_HPP_
// #define RAYLIB_CPP_INCLUDE_MUSIC_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 音乐流类型（从内存中流式传输音频文件）
 */
class Music : public ::Music {
public:
    Music(
        ::AudioStream stream = {nullptr, nullptr, 0, 0, 0},
        unsigned int frameCount = 0,
        bool looping = false,
        int ctxType = 0,
        void* ctxData = nullptr)
        : ::Music{stream, frameCount, looping, ctxType, ctxData} {}

    Music(const ::Music& music) : ::Music(music) { }

    /**
     * 从文件加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    Music(const std::string& fileName) { Load(fileName); }

    /**
     * 从内存加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    Music(const std::string& fileType, unsigned char* data, int dataSize) { Load(fileType, data, dataSize); }

    Music(const Music&) = delete;

    Music(Music&& other) noexcept {
        set(other);

        other.stream = {};
        other.frameCount = 0;
        other.looping = false;
        other.ctxType = 0;
        other.ctxData = nullptr;
    }

    /**
     * 卸载音乐流
     */
    ~Music() { Unload(); }

    GETTER(::AudioStream, Stream, stream)
    GETTER(unsigned int, FrameCount, frameCount)
    GETTERSETTER(bool, Looping, looping)
    GETTER(int, CtxType, ctxType)
    GETTER(void*, CtxData, ctxData)

    Music& operator=(const ::Music& music) {
        set(music);
        return *this;
    }

    Music& operator=(const Music&) = delete;

    Music& operator=(Music&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.ctxType = 0;
        other.ctxData = nullptr;
        other.looping = false;
        other.frameCount = 0;
        other.stream = {};

        return *this;
    }

    /**
     * 卸载音乐流
     */
    void Unload() { ::UnloadMusicStream(*this); }

    /**
     * 开始播放音乐
     */
    Music& Play() {
        ::PlayMusicStream(*this);
        return *this;
    }

    /**
     * 更新音乐流的缓冲区
     */
    Music& Update() {
        ::UpdateMusicStream(*this);
        return *this;
    }

    /**
     * 停止播放音乐
     */
    Music& Stop() {
        ::StopMusicStream(*this);
        return *this;
    }

    /**
     * 暂停播放音乐
     */
    Music& Pause() {
        ::PauseMusicStream(*this);
        return *this;
    }

    /**
     * 恢复播放音乐
     */
    Music& Resume() {
        ::ResumeMusicStream(*this);
        return *this;
    }

    /**
     * 将音乐定位到指定位置（以秒为单位）
     */
    Music& Seek(float position) {
        SeekMusicStream(*this, position);
        return *this;
    }

    /**
     * 检查音乐是否正在播放
     */
    [[nodiscard]] bool IsPlaying() const { return ::IsMusicStreamPlaying(*this); }

    /**
     * 设置音乐的音量
     */
    Music& SetVolume(float volume) {
        ::SetMusicVolume(*this, volume);
        return *this;
    }

    /**
     * 设置音乐的音调
     */
    Music& SetPitch(float pitch) {
        ::SetMusicPitch(*this, pitch);
        return *this;
    }

    /**
     * 设置音乐的声相（0.5 为中心）
     */
    Music& SetPan(float pan = 0.5f) {
        ::SetMusicPan(*this, pan);
        return *this;
    }

    /**
     * 获取音乐的总时长（以秒为单位）
     */
    [[nodiscard]] float GetTimeLength() const { return ::GetMusicTimeLength(*this); }

    /**
     * 获取当前播放的音乐时间（以秒为单位）
     */
    [[nodiscard]] float GetTimePlayed() const { return ::GetMusicTimePlayed(*this); }

    /**
     * 从文件加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    void Load(const std::string& fileName) {
        set(::LoadMusicStream(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException(TextFormat("未能从文件 %s 加载音乐", fileName.c_str()));
        }
    }

    /**
     * 从内存加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    void Load(const std::string& fileType, unsigned char* data, int dataSize) {
        set(::LoadMusicStreamFromMemory(fileType.c_str(), data, dataSize));
        if (!IsValid()) {
            throw RaylibException(TextFormat("未能从 %s 文件数据加载音乐", fileType.c_str()));
        }
    }

    /**
     * 检查音乐是否已加载
     *
     * @return 如果音乐已加载，则返回 true，否则返回 false。
     */
    bool IsValid() const { return ::IsMusicValid(*this); }
protected:
    void set(const ::Music& music) {
        stream = music.stream;
        frameCount = music.frameCount;
        looping = music.looping;
        ctxType = music.ctxType;
        ctxData = music.ctxData;
    }
};
} // namespace raylib

using RMusic = raylib::Music;

// #endif // RAYLIB_CPP_INCLUDE_MUSIC_HPP_