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
  文件数据(const 文件数据 &) = delete;
  文件数据(文件数据 &&other) noexcept
      : 数据(other.数据), 读取的字节数(other.读取的字节数) {
    other.数据 = nullptr;
    other.读取的字节数 = 0;
  }
  文件数据 &operator=(const 文件数据 &) = delete;
  文件数据 &operator=(文件数据 &&other) noexcept {
    std::swap(数据, other.数据);
    std::swap(读取的字节数, other.读取的字节数);
    return *this;
  }
  ~文件数据() { 卸载(); }

  /**
   * 从文件名加载文件数据
   */
  explicit 文件数据(const std::string &文件名) { 加载(文件名); }

  GETTER(const unsigned char *, 数据, 数据)
  GETTER(int, 读取的字节数, 读取的字节数)

  /**
   * 从文件名加载文件数据
   */
  void 加载(const std::string &文件名) { 加载(文件名.c_str()); }

  /**
   * 从文件名加载文件数据
   */
  void 加载(const char *文件名) {
    卸载();
    数据 = ::LoadFileData(文件名, &读取的字节数);
  }

  /**
   * 卸载文件数据
   */
  void 卸载() {
    if (数据 != nullptr) {
      ::UnloadFileData(数据);
      数据 = nullptr;
      读取的字节数 = 0;
    }
  }

private:
  unsigned char *数据{nullptr};
  int 读取的字节数{0};
};

} // namespace raylib

using R文件数据 = raylib::文件数据;

// #endif // RAYLIB_CPP_INCLUDE_FILEDATA_HPP_