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
class RaylibException : public std::runtime_error {
public:
    /**
     * 使用给定的消息构造一个运行时异常。
     *
     * @param message 提供给异常的消息。
     */
    explicit RaylibException(const std::string& message) noexcept : std::runtime_error(message) {
        // Nothing
    }

    /**
     * 将异常消息输出到 TraceLog()。
     *
     * @param logLevel 输出时使用的日志级别。
     */
    void TraceLog(int logLevel = LOG_ERROR) { ::TraceLog(logLevel, std::runtime_error::what()); }
};

} // namespace raylib

using RRaylibException = raylib::RaylibException;

// #endif // RAYLIB_CPP_INCLUDE_RAYLIBEXCEPTION_HPP_