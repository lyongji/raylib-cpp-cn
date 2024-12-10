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
class AutomationEventList : public ::AutomationEventList {
public:
    AutomationEventList(const ::AutomationEventList& automationEventList) { set(automationEventList); }

    /**
     * 加载一个空的自动化事件列表。
     */
    AutomationEventList() { set(::LoadAutomationEventList(0)); }

    /**
     * 从文件加载自动化事件列表。
     *
     * @param fileName 要加载自动化事件列表的文件路径。
     */
    AutomationEventList(const char* fileName) { Load(fileName); }

    AutomationEventList(const AutomationEventList&) = delete;

    AutomationEventList(AutomationEventList&& other) {
        set(other);

        other.capacity = 0;
        other.count = 0;
        other.events = nullptr;
    }

    ~AutomationEventList() { Unload(); }

    GETTER(unsigned int, Capacity, capacity)
    GETTER(unsigned int, Count, count)
    GETTER(AutomationEvent*, Events, events)

    AutomationEventList& operator=(const ::AutomationEventList& other) {
        set(other);
        return *this;
    }

    AutomationEventList& operator=(const AutomationEventList&) = delete;

    AutomationEventList& operator=(AutomationEventList&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

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
    void Load(const char* fileName) {
        Unload();
        set(::LoadAutomationEventList(fileName));
        if (!IsValid()) {
            throw RaylibException("自动化事件列表加载失败");
        }
    }

    /**
     * 更新音频流缓冲区数据
     */
    void Unload() {
        if (!IsValid()) {
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

    bool IsValid() { return events != nullptr; }

    bool Export(const char* fileName) { return ::ExportAutomationEventList(*this, fileName); }

    void Set() { ::SetAutomationEventList(this); }

    void SetBaseFrame(int frame) {
        Set();
        ::SetAutomationEventBaseFrame(frame);
    }

    void StartRecording() {
        Set();
        ::StartAutomationEventRecording();
    }

    void StopRecording() {
        Set();
        ::StopAutomationEventRecording();
    }

    void Play(int index) {
        if (index < 0 || static_cast<unsigned int>(index) >= this->count) {
            return;
        }

        Set();
        ::PlayAutomationEvent(this->events[index]);
    }
protected:
    void set(const ::AutomationEventList& other) {
        capacity = other.capacity;
        count = other.count;
        events = other.events;
    }
};
} // namespace raylib

using RAutomationEventList = raylib::AutomationEventList;

// #endif // RAYLIB_CPP_INCLUDE_AUTOMATIONEVENTLIST_HPP_