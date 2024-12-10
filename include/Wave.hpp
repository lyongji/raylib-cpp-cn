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
class Wave : public ::Wave {
public:
    Wave(const ::Wave& wave) { set(wave); }

    Wave(
        unsigned int frameCount = 0,
        unsigned int sampleRate = 0,
        unsigned int sampleSize = 0,
        unsigned int channels = 0,
        void* data = nullptr)
        : ::Wave{frameCount, sampleRate, sampleSize, channels, data} {
        // 无操作
    }

    /**
     * 从文件加载波形数据
     *
     * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
     */
    Wave(const std::string& fileName) { Load(fileName); }

    /**
     * 从内存缓冲区加载波形数据，fileType 指文件扩展名，例如 "wav"
     *
     * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
     */
    Wave(const std::string& fileType, const unsigned char* fileData, int dataSize) {
        Load(fileType, fileData, dataSize);
    }

    Wave(const Wave& other) { set(other.Copy()); }

    Wave(Wave&& other) {
        set(other);

        other.frameCount = 0;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
        other.data = nullptr;
    }

    /**
     * 卸载波形数据
     */
    ~Wave() { Unload(); }

    GETTER(unsigned int, FrameCount, frameCount)
    GETTER(unsigned int, SampleRate, sampleRate)
    GETTER(unsigned int, SampleSize, sampleSize)
    GETTER(unsigned int, Channels, channels)
    GETTER(void*, Data, data)

    Wave& operator=(const ::Wave& wave) {
        set(wave);
        return *this;
    }

    Wave& operator=(const Wave& other) {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other.Copy());

        return *this;
    }

    Wave& operator=(Wave&& other) noexcept {
        if (this != &other) {
            return *this;
        }

        Unload();
        set(other);

        other.frameCount = 0;
        other.sampleRate = 0;
        other.sampleSize = 0;
        other.channels = 0;
        other.data = nullptr;

        return *this;
    }

    /**
     * 复制波形数据到新的波形
     */
    ::Wave Copy() const { return ::WaveCopy(*this); }

    /**
     * 裁剪波形数据到定义的样本范围
     */
    Wave& Crop(int initSample, int finalSample) {
        ::WaveCrop(this, initSample, finalSample);
        return *this;
    }

    /**
     * 将波形数据转换为所需格式
     */
    Wave& Format(int SampleRate, int SampleSize, int Channels = 2) {
        ::WaveFormat(this, SampleRate, SampleSize, Channels);
        return *this;
    }

    /**
     * 从波形加载样本数据为浮点数数组
     */
    float* LoadSamples() { return ::LoadWaveSamples(*this); }

    /**
     * 卸载通过 LoadWaveSamples() 加载的样本数据
     */
    static void UnloadSamples(float* samples) { ::UnloadWaveSamples(samples); }

    /**
     * 将波形数据导出到文件，成功返回 true
     */
    bool Export(const std::string& fileName) {
        // TODO(RobLoach): 错误时抛出异常
        return ::ExportWave(*this, fileName.c_str());
    }

    /**
     * 将波形样本数据导出为代码 (.h)，成功返回 true
     */
    bool ExportAsCode(const std::string& fileName) {
        // TODO(RobLoach): 错误时抛出异常
        return ::ExportWaveAsCode(*this, fileName.c_str());
    }

    /**
     * 卸载波形数据
     */
    void Unload() {
        // 防止多次调用 UnloadWave()
        if (data != nullptr) {
            ::UnloadWave(*this);
            data = nullptr;
        }
    }

    /**
     * 从波形数据加载声音
     */
    ::Sound LoadSound() { return ::LoadSoundFromWave(*this); }

    /**
     * 从波形数据加载声音
     */
    operator ::Sound() { return LoadSound(); }

    /**
     * 从文件加载波形数据
     *
     * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
     */
    void Load(const std::string& fileName) {
        set(::LoadWave(fileName.c_str()));
        if (!IsValid()) {
            throw RaylibException("Failed to load Wave from file: " + fileName);
        }
    }

    /**
     * 从内存缓冲区加载波形数据，fileType 指文件扩展名，例如 "wav"
     *
     * @throws raylib::RaylibException 如果加载 Wave 失败则抛出异常
     */
    void Load(const std::string& fileType, const unsigned char* fileData, int dataSize) {
        set(::LoadWaveFromMemory(fileType.c_str(), fileData, dataSize));
        if (!IsValid()) {
            throw RaylibException("Failed to load Wave from file data of type: " + fileType);
        }
    }

    /**
     * 检索波形数据是否已加载
     *
     * @return 波形数据是否已加载的布尔值
     */
    bool IsValid() const { return ::IsWaveValid(*this); }
protected:
    void set(const ::Wave& wave) {
        frameCount = wave.frameCount;
        sampleRate = wave.sampleRate;
        sampleSize = wave.sampleSize;
        channels = wave.channels;
        data = wave.data;
    }
};

} // namespace raylib

using RWave = raylib::Wave;

// #endif // RAYLIB_CPP_INCLUDE_WAVE_HPP_