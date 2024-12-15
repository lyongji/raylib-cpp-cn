/**
 * C++ 封装 raylib 的函数。
 */
// #ifndef RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_
// #define RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_
#pragma once

#include <string>
#include <vector>

#include "./raylib.hpp"

/**
 * 允许更改 raylib-cpp 全局函数的声明类型。默认为静态（static）。
 */
#ifndef RLCPPAPI
#define RLCPPAPI static
#endif

namespace raylib {

/**
 * 初始化窗口和 OpenGL 上下文
 */
[[maybe_unused]] RLCPPAPI inline void 初始化窗口(int 宽, int 高, const std::string& 标题 = "raylib-中文") {
    ::InitWindow(宽, 高, 标题.c_str());
}

/**
 * 设置窗口标题
 */
[[maybe_unused]] RLCPPAPI inline void 设窗口标题(const std::string& 标题) {
    ::SetWindowTitle(标题.c_str());
}

/**
 * 获取主显示器的可读名称（UTF-8 编码）
 */
[[maybe_unused]] RLCPPAPI inline std::string 取显示器名(int 显示器编号 = 0) {
    return ::GetMonitorName(显示器编号);
}

/**
 * 设置剪贴板文本内容
 */
[[maybe_unused]] RLCPPAPI inline void 设剪贴板文本(const std::string& 文本) {
    ::SetClipboardText(文本.c_str());
}

/**
 * 获取剪贴板文本内容
 */
[[maybe_unused]] RLCPPAPI inline std::string 取剪贴板文本() {
    return ::GetClipboardText();
}

/**
 * 截取当前屏幕的截图（保存为 .png 文件）
 */
[[maybe_unused]] RLCPPAPI inline void 截屏(const std::string& 文件名) {
    ::TakeScreenshot(文件名.c_str());
}

/**
 * 获取游戏手柄的内部名称 ID
 */
[[maybe_unused]] RLCPPAPI inline std::string 取游戏手柄名(int 手柄编号) {
    return ::GetGamepadName(手柄编号);
}

/**
 * 从文件加载文本数据（读取）
 */
[[maybe_unused]] RLCPPAPI std::string 加载文件文本(const std::string& 文件名) {
    char* 文本 = ::LoadFileText(文件名.c_str());
    std::string 输出(文本);
    ::UnloadFileText(文本);
    return 输出;
}

/**
 * 将文本数据保存到文件（写入）
 */
[[maybe_unused]] RLCPPAPI inline bool 存文件文本(const std::string& 文件名, const std::string& 文本) {
    return ::SaveFileText(文件名.c_str(), const_cast<char*>(文本.c_str()));
}

/**
 * 检查文件是否存在
 */
[[maybe_unused]] RLCPPAPI inline bool 是有此文件(const std::string& 文件) {
    return ::FileExists(文件.c_str());
}

/**
 * 检查目录路径是否存在
 */
[[maybe_unused]] RLCPPAPI inline bool 是有此目录(const std::string& 目录路径) {
    return ::DirectoryExists(目录路径.c_str());
}

/**
 * 检查文件扩展名（包括点：.png, .wav）
 */
[[maybe_unused]] RLCPPAPI inline bool 是此文件的后缀名(const std::string& 文件名, const std::string& 后缀名) {
    return ::IsFileExtension(文件名.c_str(), 后缀名.c_str());
}

/**
 * 获取文件名扩展名的指针（包括点：".png"）
 */
[[maybe_unused]] RLCPPAPI inline std::string 取文件后缀名(const std::string& 文件名) {
    return ::GetFileExtension(文件名.c_str());
}

/**
 * 获取路径字符串的文件名指针
 */
[[maybe_unused]] RLCPPAPI inline std::string 取文件名(const std::string& 文件路径) {
    return ::GetFileName(文件路径.c_str());
}

/**
 * 获取不带扩展名的文件名字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string 取无后缀的文件名(const std::string& 文件路径) {
    return ::GetFileNameWithoutExt(文件路径.c_str());
}

/**
 * 获取给定文件名的完整路径
 */
[[maybe_unused]] RLCPPAPI inline std::string 取文件的路径(const std::string& 文件路径) {
    return ::GetDirectoryPath(文件路径.c_str());
}

/**
 * 获取给定路径的上一级目录路径
 */
[[maybe_unused]] RLCPPAPI inline std::string 取上一级目录路径(const std::string& 目录路径) {
    return ::GetPrevDirectoryPath(目录路径.c_str());
}

/**
 * 获取当前工作目录
 */
[[maybe_unused]] RLCPPAPI inline std::string 取当前工作目录() {
    return ::GetWorkingDirectory();
}

/**
 * 获取目录路径中的文件名列表
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> 加载目录下的文件表(const std::string& 目录路径) {
    FilePathList 文件表 = ::LoadDirectoryFiles(目录路径.c_str());
    std::vector<std::string> 输出(文件表.paths, 文件表.paths + 文件表.count);
    ::UnloadDirectoryFiles(文件表);
    return 输出;
}

/**
 * 更改工作目录，成功返回 true
 */
[[maybe_unused]] RLCPPAPI inline bool 切换目录(const std::string& 目录) {
    return ::ChangeDirectory(目录.c_str());
}

/**
 * 获取拖放的文件名列表
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> 加载拖放文件() {
    if (!::IsFileDropped()) {
        return std::vector<std::string>();
    }
    FilePathList 文件表 = ::LoadDroppedFiles();
    std::vector<std::string> 输出(文件表.paths, 文件表.paths + 文件表.count);
    ::UnloadDroppedFiles(文件表);
    return 输出;
}

/**
 * 获取文件的修改时间（最后写入时间）
 */
[[maybe_unused]] RLCPPAPI inline long 取文件修改时间(const std::string& 文件名) { // NOLINT
    return ::GetFileModTime(文件名.c_str());
}

/**
 * 使用默认系统浏览器打开 URL（如果可用）
 */
[[maybe_unused]] RLCPPAPI inline void 打开URL(const std::string& url) {
    return ::OpenURL(url.c_str());
}

/**
 * 加载图像
 */
[[maybe_unused]] RLCPPAPI inline ::Image 加载图像(const std::string& 文件名) {
    return ::LoadImage(文件名.c_str());
}

/**
 * 从 RAW 文件数据加载图像
 */
[[maybe_unused]] RLCPPAPI inline ::Image
加载Raw图像(const std::string& 文件名, int 宽, int 高, int 格式, int 文件头大小) {
    return ::LoadImageRaw(文件名.c_str(), 宽, 高, 格式, 文件头大小);
}

/**
 * 加载动画图像数据
 */
[[maybe_unused]] RLCPPAPI inline ::Image 加载动画图像(const std::string& 文件名, int* 帧数) {
    return ::LoadImageAnim(文件名.c_str(), 帧数);
}

/**
 * 从内存缓冲区加载图像，文件类型 指的是扩展名，如 "png"
 */
[[maybe_unused]] RLCPPAPI inline ::Image
加载图像于内存中(const std::string& 文件类型, const unsigned char* 文件数据, int 数据大小) {
    return ::LoadImageFromMemory(文件类型.c_str(), 文件数据, 数据大小);
}

/**
 * 将图像数据导出到文件
 */
[[maybe_unused]] RLCPPAPI inline bool 导出图像(const Image& 图像, const std::string& 文件名) {
    return ::ExportImage(图像, 文件名.c_str());
}

/**
 * 将图像导出为代码文件（.h），定义一个字节数组
 */
[[maybe_unused]] RLCPPAPI inline bool 导出图像为代码(const Image& 图像, const std::string& 文件名) {
    return ::ExportImageAsCode(图像, 文件名.c_str());
}

/**
 * 使用默认字体绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void 绘制文本(const char* 文本, int 位置X, int 位置Y, int 字体大小, ::Color 颜色) {
    ::DrawText(文本, 位置X, 位置Y, 字体大小, 颜色);
}

/**
 * 使用默认字体绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
绘制文本(const std::string& 文本, int 位置X, int 位置Y, int 字体大小, ::Color 颜色) {
    ::DrawText(文本.c_str(), 位置X, 位置Y, 字体大小, 颜色);
}

/**
 * 使用字体和附加参数绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
绘制扩展文本(const Font& 字体, char* 文本, Vector2 位置, float 字体大小, float 间距, ::Color 色调) {
    ::DrawTextEx(字体, 文本, 位置, 字体大小, 间距, 色调);
}

/**
 * 使用字体和附加参数绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
绘制扩展文本(const Font& 字体, const std::string& 文本, Vector2 位置, float 字体大小, float 间距, ::Color 色调) {
    ::DrawTextEx(字体, 文本.c_str(), 位置, 字体大小, 间距, 色调);
}

/**
 * 使用字体和高级参数（旋转）绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void 绘制高级文本(
    const Font& 字体,
    const char* 文本,
    Vector2 位置,
    Vector2 原点,
    float 旋转,
    float 字体大小,
    float 间距,
    ::Color 色调) {
    ::DrawTextPro(字体, 文本, 位置, 原点, 旋转, 字体大小, 间距, 色调);
}

/**
 * 使用字体和高级参数（旋转）绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void 绘制高级文本(
    const Font& 字体,
    const std::string& 文本,
    Vector2 位置,
    Vector2 原点,
    float 旋转,
    float 字体大小,
    float 间距,
    ::Color 色调) {
    ::DrawTextPro(字体, 文本.c_str(), 位置, 原点, 旋转, 字体大小, 间距, 色调);
}

/**
 * 从文件加载字体（文件名必须包含扩展名）
 */
[[maybe_unused]] RLCPPAPI inline ::Font 加载字体(const std::string& 文件名) {
    return ::LoadFont(文件名.c_str());
}

/**
 * 从文件加载字体（文件名必须包含扩展名）
 */
[[maybe_unused]] RLCPPAPI inline ::Font
加载扩展字体(const std::string& 文件名, int 文件大小, int* 字体字符组, int 字符数量) {
    return ::LoadFontEx(文件名.c_str(), 文件大小, 字体字符组, 字符数量);
}

/**
 * 测量默认字体的字符串宽度
 */
[[maybe_unused]] RLCPPAPI inline int 测量文本宽度(const char* 文本, int 字体大小) {
    return ::MeasureText(文本, 字体大小);
}

/**
 * 测量默认字体的字符串宽度
 */
[[maybe_unused]] RLCPPAPI inline int 测量文本宽度(const std::string& 文本, int 字体大小) {
    return ::MeasureText(文本.c_str(), 字体大小);
}

/**
 * 检查两个文本字符串是否相等
 */
[[maybe_unused]] RLCPPAPI inline bool 是文本相等(const char* 文本1, const char* 文本2) {
    return ::TextIsEqual(文本1, 文本2);
}

/**
 * 检查两个文本字符串是否相等
 */
[[maybe_unused]] RLCPPAPI inline bool 是文本相等(const std::string& 文本1, const std::string& 文本2) {
    return ::TextIsEqual(文本1.c_str(), 文本2.c_str());
}

/**
 * 获取文本长度，检查 '\0' 结尾
 */
[[maybe_unused]] RLCPPAPI inline unsigned int 文本长度(const char* 文本) {
    return ::TextLength(文本);
}

/**
 * 获取文本长度，检查 '\0' 结尾
 */
[[maybe_unused]] RLCPPAPI inline unsigned int 文本长度(const std::string& 文本) {
    return ::TextLength(文本.c_str());
}

/**
 * 获取子文本
 */
[[maybe_unused]] RLCPPAPI inline std::string 提取子文本(const std::string& 文本, int 位置, int 长度) {
    return ::TextSubtext(文本.c_str(), 位置, 长度);
}

/**
 * 替换文本字符串
 */
[[maybe_unused]] RLCPPAPI std::string
替换文本(const std::string& 文本, const std::string& 被替换, const std::string& 为) {
    const char* input = 文本.c_str();
    char* 输出 = ::TextReplace(const_cast<char*>(input), 被替换.c_str(), 为.c_str());
    if (输出 != nullptr) {
        std::string 字符串输出(输出);
        free(输出);
        return 字符串输出;
    }
    return "";
}

/**
 * 在指定位置插入文本
 */
[[maybe_unused]] RLCPPAPI std::string 插入文本(const std::string& 文本, const std::string& 插入, int 位置) {
    char* 输出 = ::TextInsert(文本.c_str(), 插入.c_str(), 位置);
    if (输出 != nullptr) {
        std::string 字符串输出(输出);
        free(输出);
        return 字符串输出;
    }
    return "";
}

/**
 * 将文本拆分为多个字符串
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> 拆分文本(const std::string& 文本, char 分隔符) {
    int 数量;
    const char** 拆分结果 = ::TextSplit(文本.c_str(), 分隔符, &数量);
    return std::vector<std::string>(拆分结果, 拆分结果 + 数量);
}

/**
 * 查找字符串中第一次出现的文本
 */
[[maybe_unused]] RLCPPAPI inline int 查找文本索引(const std::string& 文本, const std::string& 查找内容) {
    return ::TextFindIndex(文本.c_str(), 查找内容.c_str());
}

/**
 * 获取大写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string 文本转大写(const std::string& 文本) {
    return ::TextToUpper(文本.c_str());
}

/**
 * 获取小写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string 文本转小写(const std::string& 文本) {
    return ::TextToLower(文本.c_str());
}

/**
 * 获取 Pascal 大小写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string 文本转首字母大写(const std::string& 文本) {
    return ::TextToPascal(文本.c_str());
}

/**
 * 从文本中获取整数值（不支持负值）
 */
[[maybe_unused]] RLCPPAPI inline int 文本转整数(const std::string& 文本) {
    return ::TextToInteger(文本.c_str());
}

} // namespace raylib

// #endif // RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_