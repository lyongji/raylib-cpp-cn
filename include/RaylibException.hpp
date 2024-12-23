// #ifndef RAYLIB_CPP_INCLUDE_RAYLIBEXCEPTION_HPP_
// #define RAYLIB_CPP_INCLUDE_RAYLIBEXCEPTION_HPP_
#pragma once

#include <stdexcept>
#include <string>

#include "./raylib.hpp"

namespace raylib {
/**
 * 用于大多数 raylib 相关异常的异常类。
 */
class Raylib异常 : public std::runtime_error {
public:
    /**
     * 使用给定的消息构造一个运行时异常。
     *
     * @param message 提供给异常的消息。
     */
    explicit Raylib异常(const std::string& 消息) noexcept : std::runtime_error(消息) {
        // Nothing
    }

    /**
     * 将异常消息输出到 TraceLog()。
     *
     * @param logLevel 输出时使用的日志级别。
     */
    void 跟踪日志(int 日志等级 = LOG_ERROR) { ::TraceLog(日志等级, std::runtime_error::what()); }
};

} // namespace raylib

using RRaylib异常 = raylib::Raylib异常;

// #endif // RAYLIB_CPP_INCLUDE_RAYLIBEXCEPTION_HPP_