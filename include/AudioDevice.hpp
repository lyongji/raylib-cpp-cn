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
class AudioDevice {
public:
    /**
     * 初始化音频设备和上下文。
     *
     * @param lateInit 是否推迟初始化上下文。
     *
     * @throws raylib::RaylibException 如果音频设备初始化失败，则抛出异常。
     */
    explicit AudioDevice(bool lateInit = false) {
        if (!lateInit) {
            Init();
        }
    }

    /**
     * 关闭音频设备和上下文。
     */
    ~AudioDevice() { Close(); }

    /**
     * 初始化音频设备和上下文。
     *
     * @throws raylib::RaylibException 如果音频设备初始化失败，则抛出异常。
     */
    static void Init()  {
        ::InitAudioDevice();
        if (!IsReady()) {
            throw RaylibException("音频设备初始化失败");
        }
    }

    /**
     * 关闭音频设备和上下文。
     */
    static void Close() { ::CloseAudioDevice(); }

    /**
     * 检查音频设备是否已成功初始化。
     */
    static bool IsReady()  { return ::IsAudioDeviceReady(); }

    /**
     * 设置主音量（监听器）。
     *
     * @param volume 要设置的音量。
     */
    AudioDevice& SetVolume(float volume) {
        ::SetMasterVolume(volume);
        return *this;
    }
};
} // namespace raylib

using RAudioDevice = raylib::AudioDevice;

// #endif // RAYLIB_CPP_INCLUDE_AUDIODEVICE_HPP_
