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
class FileText {
public:
    FileText() = default;
    FileText(const FileText&) = delete;
    FileText(FileText&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }
    FileText& operator=(const FileText&) = delete;
    FileText& operator=(FileText&& other) noexcept {
        std::swap(data, other.data);
        std::swap(length, other.length);
        return *this;
    }
    ~FileText() { Unload(); }

    /**
     * 从文件名加载文件文本
     */
    explicit FileText(const std::string& fileName) { Load(fileName); }

    GETTER(const char*, Data, data)
    GETTER(unsigned int, Length, length)

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
    void Load(const std::string& fileName) { Load(fileName.c_str()); }

    /**
     * 从文件名加载文件文本
     */
    void Load(const char* fileName) {
        data = ::LoadFileText(fileName);
        length = ::TextLength(data);
    }

    /**
     * 卸载文件文本
     */
    void Unload() {
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

using RFileText = raylib::FileText;

// #endif // RAYLIB_CPP_INCLUDE_FILETEXT_HPP_