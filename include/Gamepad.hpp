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
class Gamepad {
public:
    Gamepad(int gamepadNumber = 0) { set(gamepadNumber); }
    int number;

    GETTERSETTER(int, Number, number)

    Gamepad& operator=(const Gamepad& gamepad) {
        if (this != &gamepad) {
            set(static_cast<int>(gamepad));
        }
        return *this;
    }

    Gamepad& operator=(int gamepadNumber) {
        if (this->number != gamepadNumber) {
            set(gamepadNumber);
        }
        return *this;
    }

    explicit operator int() const { return number; }

    /**
     * 检测游戏手柄是否可用
     */
    [[nodiscard]] bool IsAvailable() const { return ::IsGamepadAvailable(number); }

    /**
     * 检测游戏手柄是否可用
     */
    static bool IsAvailable(int number) { return ::IsGamepadAvailable(number); }

    /**
     * 返回游戏手柄的内部名称 ID
     */
    [[nodiscard]] std::string GetName() const { return ::GetGamepadName(number); }

    /**
     * 返回游戏手柄的内部名称 ID
     */
    explicit operator std::string() const { return GetName(); }

    /**
     * 检测游戏手柄按钮是否被按下一次
     */
    [[nodiscard]] bool IsButtonPressed(int button) const { return ::IsGamepadButtonPressed(number, button); }

    /**
     * 检测游戏手柄按钮是否正在被按下
     */
    [[nodiscard]] bool IsButtonDown(int button) const { return ::IsGamepadButtonDown(number, button); }

    /**
     * 检测游戏手柄按钮是否被释放一次
     */
    [[nodiscard]] bool IsButtonReleased(int button) const { return ::IsGamepadButtonReleased(number, button); }

    /**
     * 检测游戏手柄按钮是否未被按下
     */
    [[nodiscard]] bool IsButtonUp(int button) const { return ::IsGamepadButtonUp(number, button); }

    /**
     * 获取最后按下的游戏手柄按钮
     */
    static int GetButtonPressed() { return ::GetGamepadButtonPressed(); }

    /**
     * 返回游戏手柄的轴数量
     */
    [[nodiscard]] int GetAxisCount() const { return ::GetGamepadAxisCount(number); }

    /**
     * 返回游戏手柄轴的移动值
     */
    [[nodiscard]] float GetAxisMovement(int axis) const { return ::GetGamepadAxisMovement(number, axis); }

    static int SetMappings(const std::string& mappings) { return SetGamepadMappings(mappings.c_str()); }

    /**
     * 设置游戏手柄振动（两个电机的振动强度，持续时间以秒为单位）
     */
    void SetVibration(float leftMotor, float rightMotor, float duration) const {
        ::SetGamepadVibration(number, leftMotor, rightMotor, duration);
    }
protected:
    void set(int gamepadNumber) { number = gamepadNumber; }
};
} // namespace raylib

using RGamepad = raylib::Gamepad;

// #endif // RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_