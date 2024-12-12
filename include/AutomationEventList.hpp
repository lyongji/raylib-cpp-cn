// #ifndef RAYLIB_CPP_INCLUDE_AUTOMATIONEVENTLIST_HPP_
// #define RAYLIB_CPP_INCLUDE_AUTOMATIONEVENTLIST_HPP_
#pragma once

#include "./RaylibException.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 自动化事件列表管理函数
 */
class 自动化事件列表 : public ::AutomationEventList {
public:
    自动化事件列表(const ::AutomationEventList& 自动化事件列表) { 设(自动化事件列表); }

    /**
     * 加载一个空的自动化事件列表。
     */
    自动化事件列表() { 设(::LoadAutomationEventList(0)); }

    /**
     * 从文件加载自动化事件列表。
     *
     * @param fileName 要加载自动化事件列表的文件路径。
     */
    自动化事件列表(const char* 文件名) { 加载(文件名); }

    自动化事件列表(const 自动化事件列表&) = delete;

    自动化事件列表(自动化事件列表&& other) {
        设(other);

        other.capacity = 0;
        other.count = 0;
        other.events = nullptr;
    }

    ~自动化事件列表() { 卸载(); }

    GETTER(unsigned int, 容量值, capacity)
    GETTER(unsigned int, 事件数, count)
    GETTER(AutomationEvent*, 事件, events)

    自动化事件列表& operator=(const ::AutomationEventList& other) {
        设(other);
        return *this;
    }

    自动化事件列表& operator=(const 自动化事件列表&) = delete;

    自动化事件列表& operator=(自动化事件列表&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        卸载();
        设(other);

        other.capacity = 0;
        other.count = 0;
        other.events = nullptr;

        return *this;
    }

    /**
     * 加载音频流（用于流式传输原始音频 PCM 数据）
     *
     * @throws raylib::RaylibException 如果自动化事件列表加载失败，则抛出异常。
     */
    void 加载(const char* 文件名) {
        卸载();
        设(::LoadAutomationEventList(文件名));
        if (!是有效()) {
            throw RaylibException("自动化事件列表加载失败");
        }
    }

    /**
     * 更新音频流缓冲区数据
     */
    void 卸载() {
        if (!是有效()) {
            return;
        }

// UnloadAutomationEventList() 函数的签名在 raylib 5.0 版本中有所变化。
#if RAYLIB_VERSION_MAJOR == 5
#if RAYLIB_VERSION_MINOR == 0
        ::UnloadAutomationEventList(this);
#elif RAYLIB_VERSION_MINOR >= 1
        ::UnloadAutomationEventList(*this);
#endif
#else
        ::UnloadAutomationEventList(*this);
#endif
    }
    /// 检查自动化事件列表是否有效。
    bool 是有效() { return events != nullptr; }
    /// 将自动化事件列表导出到文件。
    bool 导出(const char* 文件名) { return ::ExportAutomationEventList(*this, 文件名); }
    /// 设置当前自动化事件列表为活动的列表。
    void 设() { ::SetAutomationEventList(this); }

    /// 设置自动化事件的基础帧。
    void 设基础帧(int 帧) {
        设();
        ::SetAutomationEventBaseFrame(帧);
    }
    /// 开始录制自动化事件。
    void 开始录制() {
        设();
        ::StartAutomationEventRecording();
    }
    /// 停止录制自动化事件。
    void 停止录制() {
        设();
        ::StopAutomationEventRecording();
    }
    /// 播放指定索引的自动化事件。
    void 播放(int 索引) {
        if (索引 < 0 || static_cast<unsigned int>(索引) >= this->count) {
            return;
        }

        设();
        ::PlayAutomationEvent(this->events[索引]);
    }
protected:
    void 设(const ::AutomationEventList& other) {
        capacity = other.capacity;
        count = other.count;
        events = other.events;
    }
};
} // namespace raylib

using R自动化事件列表 = raylib::自动化事件列表;

// #endif // RAYLIB_CPP_INCLUDE_AUTOMATIONEVENTLIST_HPP_