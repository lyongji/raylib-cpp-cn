// #ifndef RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_
// #define RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * VR 立体配置函数，用于 VR 模拟器
 */
class VrStereoConfig : public ::VrStereoConfig {
public:
    VrStereoConfig(const ::VrDeviceInfo& info) { Load(info); }

    /**
     * 加载 VR 立体配置，用于 VR 模拟器的设备参数
     */
    void Load(const ::VrDeviceInfo& info) { set(LoadVrStereoConfig(info)); }

    /**
     * 卸载 VR 立体配置
     */
    ~VrStereoConfig() { Unload(); }

    /**
     * 开始立体渲染
     */
    VrStereoConfig& BeginMode() {
        ::BeginVrStereoMode(*this);
        return *this;
    }

    /**
     * 结束立体渲染
     */
    VrStereoConfig& EndMode() {
        ::EndVrStereoMode();
        return *this;
    }

    /**
     * 卸载 VR 立体配置
     */
    void Unload() { ::UnloadVrStereoConfig(*this); }
protected:
    void set(const ::VrStereoConfig& config) {
        projection[0] = config.projection[0];
        projection[1] = config.projection[1];
        viewOffset[0] = config.viewOffset[0];
        viewOffset[1] = config.viewOffset[1];
        leftLensCenter[0] = config.leftLensCenter[0];
        leftLensCenter[1] = config.leftLensCenter[1];
        rightLensCenter[0] = config.rightLensCenter[0];
        rightLensCenter[1] = config.rightLensCenter[1];
        leftScreenCenter[0] = config.leftScreenCenter[0];
        leftScreenCenter[1] = config.leftScreenCenter[1];
        rightScreenCenter[0] = config.rightScreenCenter[0];
        rightScreenCenter[1] = config.rightScreenCenter[1];
        scale[0] = config.scale[0];
        scale[1] = config.scale[1];
        scaleIn[0] = config.scaleIn[0];
        scaleIn[1] = config.scaleIn[1];
    }
};
} // namespace raylib

using RVrStereoConfig = raylib::VrStereoConfig;

// #endif // RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_