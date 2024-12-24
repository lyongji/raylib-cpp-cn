// #ifndef RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_
// #define RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_
#pragma once

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * VR 立体配置函数，用于 VR 模拟器
 */
class VR立体配置 : public ::VrStereoConfig {
public:
    VR立体配置(const ::VrDeviceInfo& 信息) { 加载(信息); }

    /**
     * 加载 VR 立体配置，用于 VR 模拟器的设备参数
     */
    void 加载(const ::VrDeviceInfo& 信息) { set(LoadVrStereoConfig(信息)); }

    /**
     * 卸载 VR 立体配置
     */
    ~VR立体配置() { 卸载(); }

    /**
     * 开始立体渲染
     */
    VR立体配置& 开始() {
        ::BeginVrStereoMode(*this);
        return *this;
    }

    /**
     * 结束立体渲染
     */
    VR立体配置& 结束() {
        ::EndVrStereoMode();
        return *this;
    }

    /**
     * 卸载 VR 立体配置
     */
    void 卸载() { ::UnloadVrStereoConfig(*this); }
protected:
    void set(const ::VrStereoConfig& 配置) {
        projection[0] = 配置.projection[0];
        projection[1] = 配置.projection[1];
        viewOffset[0] = 配置.viewOffset[0];
        viewOffset[1] = 配置.viewOffset[1];
        leftLensCenter[0] = 配置.leftLensCenter[0];
        leftLensCenter[1] = 配置.leftLensCenter[1];
        rightLensCenter[0] = 配置.rightLensCenter[0];
        rightLensCenter[1] = 配置.rightLensCenter[1];
        leftScreenCenter[0] = 配置.leftScreenCenter[0];
        leftScreenCenter[1] = 配置.leftScreenCenter[1];
        rightScreenCenter[0] = 配置.rightScreenCenter[0];
        rightScreenCenter[1] = 配置.rightScreenCenter[1];
        scale[0] = 配置.scale[0];
        scale[1] = 配置.scale[1];
        scaleIn[0] = 配置.scaleIn[0];
        scaleIn[1] = 配置.scaleIn[1];
    }
};
} // namespace raylib

using RVR立体配置 = raylib::VR立体配置;

// #endif // RAYLIB_CPP_INCLUDE_VRSTEREOCONFIG_HPP_