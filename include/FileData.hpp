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
class FileData {
public:
    FileData() = default;
    FileData(const FileData&) = delete;
    FileData(FileData&& other) noexcept : data(other.data), bytesRead(other.bytesRead) {
        other.data = nullptr;
        other.bytesRead = 0;
    }
    FileData& operator=(const FileData&) = delete;
    FileData& operator=(FileData&& other) noexcept {
        std::swap(data, other.data);
        std::swap(bytesRead, other.bytesRead);
        return *this;
    }
    ~FileData() { Unload(); }

    /**
     * 从文件名加载文件数据
     */
    explicit FileData(const std::string& fileName) { Load(fileName); }

    GETTER(const unsigned char*, Data, data)
    GETTER(int, BytesRead, bytesRead)

    /**
     * 从文件名加载文件数据
     */
    void Load(const std::string& fileName) { Load(fileName.c_str()); }

    /**
     * 从文件名加载文件数据
     */
    void Load(const char* fileName) {
        Unload();
        data = ::LoadFileData(fileName, &bytesRead);
    }

    /**
     * 卸载文件数据
     */
    void Unload() {
        if (data != nullptr) {
            ::UnloadFileData(data);
            data = nullptr;
            bytesRead = 0;
        }
    }
private:
    unsigned char* data{nullptr};
    int bytesRead{0};
};

} // namespace raylib

using RFileData = raylib::FileData;

// #endif // RAYLIB_CPP_INCLUDE_FILEDATA_HPP_