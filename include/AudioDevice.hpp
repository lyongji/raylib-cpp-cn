// #ifndef RAYLIB_CPP_INCLUDE_AUDIODEVICE_HPP_
// #define RAYLIB_CPP_INCLUDE_AUDIODEVICE_HPP_
#pragma once

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 音频设备管理函数。
 */
class 音频设备 {
public:
    /**
     * 初始化音频设备和上下文。
     *
     * @param lateInit 是否推迟初始化上下文。
     *
     * @throws raylib::RaylibException 如果音频设备初始化失败，则抛出异常。
     */
    explicit 音频设备(bool 延迟初始化 = false) {
        if (!延迟初始化) {
            初始化();
        }
    }

    /**
     * 关闭音频设备和上下文。
     */
    ~音频设备() { 关闭(); }

    /**
     * 初始化音频设备和上下文。
     *
     * @throws raylib::RaylibException 如果音频设备初始化失败，则抛出异常。
     */
    static void 初始化() {
        ::InitAudioDevice();
        if (!是就绪()) {
            throw Raylib异常("音频设备初始化失败");
        }
    }

    /**
     * 关闭音频设备和上下文。
     */
    static void 关闭() { ::CloseAudioDevice(); }

    /**
     * 检查音频设备是否已成功初始化。
     */
    static bool 是就绪() { return ::IsAudioDeviceReady(); }

    /**
     * 设置主音量（监听器）。
     *
     * @param volume 要设置的音量。
     */
    音频设备& 设音量(float 音量) {
        ::SetMasterVolume(音量);
        return *this;
    }
};
} // namespace raylib

using R音频设备 = raylib::音频设备;

// #endif // RAYLIB_CPP_INCLUDE_AUDIODEVICE_HPP_
