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
  自动化事件列表(const ::AutomationEventList &自动化事件列表)
      : ::AutomationEventList(自动化事件列表) {}

  /**
   * 加载一个空的自动化事件列表。
   */
  自动化事件列表() { 设(::LoadAutomationEventList(0)); }

  /**
   * 从文件加载自动化事件列表。
   *
   * @param 文件名 要加载自动化事件列表的文件路径。
   */
  自动化事件列表(const char *文件名) { 加载文件(文件名); }

  自动化事件列表(const 自动化事件列表 &) = delete;

  自动化事件列表(自动化事件列表 &&other) noexcept {
    设(other);

    other.capacity = 0;
    other.count = 0;
    other.events = nullptr;
  }

  ~自动化事件列表() { 卸载资源(); }

  GETTER(unsigned int, 容量值, capacity)
  GETTER(unsigned int, 事件个数, count)
  GETTER(AutomationEvent *, 事件, events)

  自动化事件列表 &operator=(const ::AutomationEventList &other) {
    设(other);
    return *this;
  }

  自动化事件列表 &operator=(const 自动化事件列表 &) = delete;

  自动化事件列表 &operator=(自动化事件列表 &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    卸载资源();
    设(other);

    other.capacity = 0;
    other.count = 0;
    other.events = nullptr;

    return *this;
  }

  void 加载文件(const char *文件名路径) {
    卸载资源();
    设(::LoadAutomationEventList(文件名路径));
    if (!已有效()) {
      throw Raylib异常("自动化事件列表加载失败");
    }
  }

  void 卸载资源() {
    if (!已有效()) {
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
  bool 已有效() { return events != nullptr; }
  /// 将自动化事件列表导出到文件。
  bool 导出文件(const char *文件路径) {
    return ::ExportAutomationEventList(*this, 文件路径);
  }
  /// 设置当前自动化事件列表为活动的列表。
  void 设为活动项() { ::SetAutomationEventList(this); }

  /// 设置自动化事件的基础帧。
  void 设基础帧号(int 帧) {
    设为活动项();
    ::SetAutomationEventBaseFrame(帧);
  }
  /// 开始录制自动化事件。
  void 开始录制() {
    设为活动项();
    ::StartAutomationEventRecording();
  }
  /// 停止录制自动化事件。
  void 停止录制() {
    设为活动项();
    ::StopAutomationEventRecording();
  }
  /// 播放指定索引的自动化事件。
  void 播放事件(int 索引) {
    if (索引 < 0 || static_cast<unsigned int>(索引) >= this->count) {
      return;
    }

    设为活动项();
    ::PlayAutomationEvent(this->events[索引]);
  }

protected:
  void 设(const ::AutomationEventList &other) {
    capacity = other.capacity;
    count = other.count;
    events = other.events;
  }
};
} // namespace raylib

using R自动化事件列表 = raylib::自动化事件列表;

// #endif // RAYLIB_CPP_INCLUDE_AUTOMATIONEVENTLIST_HPP_