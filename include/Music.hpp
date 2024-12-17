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
class 音乐流 : public ::Music {
public:
    音乐流(
        ::AudioStream 音频流 = {nullptr, nullptr, 0, 0, 0},
        unsigned int 帧数 = 0,
        bool 循环 = false,
        int 环境类型 = 0,
        void* 环境数据 = nullptr)
        : ::Music{音频流, 帧数, 循环, 环境类型, 环境数据} {}

    音乐流(const ::Music& 音乐) { 设(音乐); }

    /**
     * 从文件加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    音乐流(const std::string& 文件名) { 加载(文件名); }

    /**
     * 从内存加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    音乐流(const std::string& 文件类型, unsigned char* 数据, int 数据大小) { 加载(文件类型, 数据, 数据大小); }

    音乐流(const 音乐流&) = delete;

    音乐流(音乐流&& other) {
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
    ~音乐流() { 卸载(); }

    GETTER(::AudioStream, 音频流, stream)
    GETTER(unsigned int, 帧数, frameCount)
    GETTERSETTER(bool, 循环, looping)
    GETTER(int, 环境类型, ctxType)
    GETTER(void*, 环境数据, ctxData)

    音乐流& operator=(const ::Music& 音乐) {
        设(音乐);
        return *this;
    }

    音乐流& operator=(const 音乐流&) = delete;

    音乐流& operator=(音乐流&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

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
    void 卸载() { ::UnloadMusicStream(*this); }

    /**
     * 开始播放音乐
     */
    音乐流& 播放() {
        ::PlayMusicStream(*this);
        return *this;
    }

    /**
     * 更新音乐流的缓冲区
     */
    音乐流& 更新() {
        ::UpdateMusicStream(*this);
        return *this;
    }

    /**
     * 停止播放音乐
     */
    音乐流& 停止() {
        ::StopMusicStream(*this);
        return *this;
    }

    /**
     * 暂停播放音乐
     */
    音乐流& 暂停() {
        ::PauseMusicStream(*this);
        return *this;
    }

    /**
     * 恢复播放音乐
     */
    音乐流& 恢复() {
        ::ResumeMusicStream(*this);
        return *this;
    }

    /**
     * 将音乐定位到指定位置（以秒为单位）
     */
    音乐流& 跳转(float 位置) {
        SeekMusicStream(*this, 位置);
        return *this;
    }

    /**
     * 检查音乐是否正在播放
     */
    bool 是播放中() const { return ::IsMusicStreamPlaying(*this); }

    /**
     * 设置音乐的音量
     */
    音乐流& 设音量(float volume) {
        ::SetMusicVolume(*this, volume);
        return *this;
    }

    /**
     * 设置音乐的音调
     */
    音乐流& 设音调(float 音调值) {
        ::SetMusicPitch(*this, 音调值);
        return *this;
    }

    /**
     * 设置音乐的声相（0.5 为中心）声道平衡 左声道<=>右声道
     */
    音乐流& 设声相(float 声相 = 0.5f) {
        ::SetMusicPan(*this, 声相);
        return *this;
    }

    /**
     * 获取音乐的总时长（以秒为单位）
     */
    float 取总时常() const { return ::GetMusicTimeLength(*this); }

    /**
     * 获取当前播放的音乐时间（以秒为单位）
     */
    float 取当前播放时间点() const { return ::GetMusicTimePlayed(*this); }

    /**
     * 从文件加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    void 加载(const std::string& 文件名) {
        设(::LoadMusicStream(文件名.c_str()));
        if (!是有效()) {
            throw Raylib异常(TextFormat("未能从文件 %s 加载音乐", 文件名.c_str()));
        }
    }

    /**
     * 从内存加载音乐流
     *
     * @throws raylib::RaylibException 如果音乐加载失败，则抛出异常。
     */
    void 加载(const std::string& 文件类型, unsigned char* 数据, int 数据大小) {
        设(::LoadMusicStreamFromMemory(文件类型.c_str(), 数据, 数据大小));
        if (!是有效()) {
            throw Raylib异常(TextFormat("未能从 %s 文件数据加载音乐", 文件类型.c_str()));
        }
    }

    /**
     * 检查音乐是否已加载
     *
     * @return 如果音乐已加载，则返回 true，否则返回 false。
     */
    bool 是有效() const { return ::IsMusicValid(*this); }
protected:
    void 设(const ::Music& music) {
        stream = music.stream;
        frameCount = music.frameCount;
        looping = music.looping;
        ctxType = music.ctxType;
        ctxData = music.ctxData;
    }
};
} // namespace raylib

using R音乐流 = raylib::音乐流;

// #endif // RAYLIB_CPP_INCLUDE_MUSIC_HPP_