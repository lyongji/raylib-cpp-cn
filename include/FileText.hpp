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
    文件文本(文件文本&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }
    文件文本& operator=(const 文件文本&) = delete;
    文件文本& operator=(文件文本&& other) noexcept {
        std::swap(data, other.data);
        std::swap(length, other.length);
        return *this;
    }
    ~文件文本() { 卸载(); }

    /**
     * 从文件名加载文件文本
     */
    explicit 文件文本(const std::string& 文件名) { 加载(文件名); }

    GETTER(const char*, 数据, data)
    GETTER(unsigned int, 长度, length)

    /**
     * 返回 C 风格的字符串
     */
    [[nodiscard]] const char* c_str() const { return data; }

    /**
     * 返回字符串形式的文本内容
     */
    [[nodiscard]] std::string ToString() const { return data; }

    /**
     * 显式转换为 std::string
     */
    explicit operator std::string() const { return data; }

    /**
     * 从文件名加载文件文本
     */
    void 加载(const std::string& 文件名) { 加载(文件名.c_str()); }

    /**
     * 从文件名加载文件文本
     */
    void 加载(const char* 文件名) {
        data = ::LoadFileText(文件名);
        length = ::TextLength(data);
    }

    /**
     * 卸载文件文本
     */
    void 卸载() {
        if (data != nullptr) {
            ::UnloadFileText(data);
            data = nullptr;
            length = 0;
        }
    }
private:
    char* data{nullptr};
    unsigned int length{0};
};

} // namespace raylib

using RFileText = raylib::文件文本;

// #endif // RAYLIB_CPP_INCLUDE_FILETEXT_HPP_