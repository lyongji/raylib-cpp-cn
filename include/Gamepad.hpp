// #ifndef RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
// #define RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
#pragma once

#include <string>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 输入相关函数：游戏手柄
 */
class 游戏手柄 {
public:
  游戏手柄(int 手柄编号 = 0) { 设(手柄编号); }
  int 编号;

  GETTERSETTER(int, 编号, 编号)

  游戏手柄 &operator=(const 游戏手柄 &手柄) {
    if (this != &手柄) {
      设(static_cast<int>(手柄));
    }
    return *this;
  }

  游戏手柄 &operator=(int 游戏手柄编号) {
    if (this->编号 != 游戏手柄编号) {
      设(游戏手柄编号);
    }
    return *this;
  }

  explicit operator int() const { return 编号; }

  /**
   * 检测游戏手柄是否可用
   */
  [[nodiscard]] bool 检查可用性() const { return ::IsGamepadAvailable(编号); }

  /**
   * 检测游戏手柄是否可用
   */
  static bool 检查可用性(int 编号) { return ::IsGamepadAvailable(编号); }

  /**
   * 返回游戏手柄的内部名称 ID
   */
  [[nodiscard]] std::string 取名称() const { return ::GetGamepadName(编号); }

  /**
   * 返回游戏手柄的内部名称 ID
   */
  explicit operator std::string() const { return 取名称(); }

  /**
   * 检测游戏手柄按钮是否被按下一次
   */
  [[nodiscard]] bool 是否按下一次(int 按钮) const {
    return ::IsGamepadButtonPressed(编号, 按钮);
  }

  /**
   * 检测游戏手柄按钮是否正在被按下
   */
  [[nodiscard]] bool 是否正在按下(int 按钮) const {
    return ::IsGamepadButtonDown(编号, 按钮);
  }

  /**
   * 检测游戏手柄按钮是否被释放一次
   */
  [[nodiscard]] bool 是否被释放一次(int 按钮) const {
    return ::IsGamepadButtonReleased(编号, 按钮);
  }

  /**
   * 检测游戏手柄按钮是否未被按下
   */
  [[nodiscard]] bool 是否未被按下(int 按钮) const {
    return ::IsGamepadButtonUp(编号, 按钮);
  }

  /**
   * 获取最后按下的游戏手柄按钮
   */
  static int 取最后按下的按钮() { return ::GetGamepadButtonPressed(); }

  /**
   * 返回游戏手柄的轴数量
   */
  [[nodiscard]] int 取轴数量() const { return ::GetGamepadAxisCount(编号); }

  /**
   * 返回游戏手柄轴的移动值
   */
  [[nodiscard]] float 取轴移动值(int 轴) const {
    return ::GetGamepadAxisMovement(编号, 轴);
  }

  static int 设映射(const std::string &映射) {
    return SetGamepadMappings(映射.c_str());
  }

  /**
   * 设置游戏手柄振动（两个电机的振动强度，持续时间以秒为单位）
   */
  void 设震动(float 左电机强度, float 右电机强度, float 持续时间) const {
    ::SetGamepadVibration(编号, 左电机强度, 右电机强度, 持续时间);
  }

protected:
  void 设(int 手柄编号) { 编号 = 手柄编号; }
};
} // namespace raylib

using R游戏手柄 = raylib::游戏手柄;

// #endif // RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_