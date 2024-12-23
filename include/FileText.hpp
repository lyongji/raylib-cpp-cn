// #ifndef RAYLIB_CPP_INCLUDE_FILETEXT_HPP_
// #define RAYLIB_CPP_INCLUDE_FILETEXT_HPP_
#pragma once

#include <string>
#include <utility>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {

/**
 * 文件文本类，用于加载和管理文件文本内容
 */
class 文件文本 {
public:
    文件文本() = default;
    文件文本(const 文件文本&) = delete;
    文件文本(文件文本&& other) noexcept : 数据(other.数据), 长度(other.长度) {
        other.数据 = nullptr;
        other.长度 = 0;
    }
    文件文本& operator=(const 文件文本&) = delete;
    文件文本& operator=(文件文本&& other) noexcept {
        std::swap(数据, other.数据);
        std::swap(长度, other.长度);
        return *this;
    }
    ~文件文本() { 卸载(); }

    /**
     * 从文件名加载文件文本
     */
    explicit 文件文本(const std::string& 文件名) { 加载(文件名); }

    GETTER(const char*, 数据, 数据)
    GETTER(unsigned int, 长度, 长度)

    /**
     * 返回 C 风格的字符串
     */
    [[nodiscard]] const char* c_str() const { return 数据; }

    /**
     * 返回字符串形式的文本内容
     */
    [[nodiscard]] std::string 转String() const { return 数据; }

    /**
     * 显式转换为 std::string
     */
    explicit operator std::string() const { return 数据; }

    /**
     * 从文件名加载文件文本
     */
    void 加载(const std::string& 文件名) { 加载(文件名.c_str()); }

    /**
     * 从文件名加载文件文本
     */
    void 加载(const char* 文件名) {
        数据 = ::LoadFileText(文件名);
        长度 = ::TextLength(数据);
    }

    /**
     * 卸载文件文本
     */
    void 卸载() {
        if (数据 != nullptr) {
            ::UnloadFileText(数据);
            数据 = nullptr;
            长度 = 0;
        }
    }
private:
    char* 数据{nullptr};
    unsigned int 长度{0};
};

} // namespace raylib

using R文件文本 = raylib::文件文本;

// #endif // RAYLIB_CPP_INCLUDE_FILETEXT_HPP_