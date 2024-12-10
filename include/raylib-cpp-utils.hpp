/**
 * raylib-cpp 的实用工具。
 */
// #ifndef RAYLIB_CPP_INCLUDE_RAYLIB_CPP_UTILS_HPP_
// #define RAYLIB_CPP_INCLUDE_RAYLIB_CPP_UTILS_HPP_
#pragma once

#ifndef GETTER
/**
 * 用于在属性之上构建 get 方法的实用工具。
 *
 * @param type 属性的类型。
 * @param method 方法的人类可读名称。
 * @param name 属性的机器可读名称。
 */
#define GETTER(type, method, name)                                  \
    /** 检索对象的 name 值。@return 对象的 name 值。 */ \
    type Get##method() const {                                      \
        return name;                                                \
    }
#endif

#ifndef GETTERSETTER
/**
 * 用于在属性之上构建 get 和 set 方法的实用工具。
 *
 * @param type 属性的类型。
 * @param method 方法的人类可读名称。
 * @param name 属性的机器可读名称。
 */
#define GETTERSETTER(type, method, name)                                       \
    GETTER(type, method, name)                                                 \
    /** 设置对象的 name 值。@param value 要设置为 name 的值。 */ \
    void Set##method(type value) {                                             \
        name = value;                                                          \
    }
#endif

// #endif // RAYLIB_CPP_INCLUDE_RAYLIB_CPP_UTILS_HPP_