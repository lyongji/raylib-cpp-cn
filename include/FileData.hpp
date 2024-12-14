// #ifndef RAYLIB_CPP_INCLUDE_FILEDATA_HPP_
// #define RAYLIB_CPP_INCLUDE_FILEDATA_HPP_
#pragma once

#include <string>
#include <utility>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"

namespace raylib {

/**
 * 文件数据类，用于加载和管理文件数据
 */
class 文件数据 {
public:
    文件数据() = default;
    文件数据(const 文件数据&) = delete;
    文件数据(文件数据&& other) noexcept : data(other.data), bytesRead(other.bytesRead) {
        other.data = nullptr;
        other.bytesRead = 0;
    }
    文件数据& operator=(const 文件数据&) = delete;
    文件数据& operator=(文件数据&& other) noexcept {
        std::swap(data, other.data);
        std::swap(bytesRead, other.bytesRead);
        return *this;
    }
    ~文件数据() { 卸载(); }

    /**
     * 从文件名加载文件数据
     */
    explicit 文件数据(const std::string& 文件名) { 加载(文件名); }

    GETTER(const unsigned char*, 数据, data)
    GETTER(int, 字节读取数, bytesRead)

    /**
     * 从文件名加载文件数据
     */
    void 加载(const std::string& 文件名) { 加载(文件名.c_str()); }

    /**
     * 从文件名加载文件数据
     */
    void 加载(const char* 文件名) { data = ::LoadFileData(文件名, &bytesRead); }

    /**
     * 卸载文件数据
     */
    void 卸载() {
        if (data != nullptr) {
            ::UnloadFileData(data);
            data = nullptr;
        }
    }
private:
    unsigned char* data{nullptr};
    int bytesRead{0};
};

} // namespace raylib

using R文件数据 = raylib::文件数据;

// #endif // RAYLIB_CPP_INCLUDE_FILEDATA_HPP_