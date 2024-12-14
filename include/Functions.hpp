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
[[maybe_unused]] RLCPPAPI inline bool 是否有此文件(const std::string& 文件) {
    return ::FileExists(文件.c_str());
}

/**
 * 检查目录路径是否存在
 */
[[maybe_unused]] RLCPPAPI inline bool 是否有此目录(const std::string& 目录路径) {
    return ::DirectoryExists(目录路径.c_str());
}

/**
 * 检查文件扩展名（包括点：.png, .wav）
 */
[[maybe_unused]] RLCPPAPI inline bool 是否后缀名是文件的(const std::string& 文件名, const std::string& 后缀名) {
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
[[maybe_unused]] RLCPPAPI inline std::string GetDirectoryPath(const std::string& 文件路径) {
    return ::GetDirectoryPath(文件路径.c_str());
}

/**
 * 获取给定路径的上一级目录路径
 */
[[maybe_unused]] RLCPPAPI inline std::string GetPrevDirectoryPath(const std::string& dirPath) {
    return ::GetPrevDirectoryPath(dirPath.c_str());
}

/**
 * 获取当前工作目录
 */
[[maybe_unused]] RLCPPAPI inline std::string GetWorkingDirectory() {
    return ::GetWorkingDirectory();
}

/**
 * 获取目录路径中的文件名列表
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> LoadDirectoryFiles(const std::string& dirPath) {
    FilePathList files = ::LoadDirectoryFiles(dirPath.c_str());
    std::vector<std::string> output(files.paths, files.paths + files.count);
    ::UnloadDirectoryFiles(files);
    return output;
}

/**
 * 更改工作目录，成功返回 true
 */
[[maybe_unused]] RLCPPAPI inline bool ChangeDirectory(const std::string& dir) {
    return ::ChangeDirectory(dir.c_str());
}

/**
 * 获取拖放的文件名列表
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> LoadDroppedFiles() {
    if (!::IsFileDropped()) {
        return std::vector<std::string>();
    }
    FilePathList files = ::LoadDroppedFiles();
    std::vector<std::string> output(files.paths, files.paths + files.count);
    ::UnloadDroppedFiles(files);
    return output;
}

/**
 * 获取文件的修改时间（最后写入时间）
 */
[[maybe_unused]] RLCPPAPI inline long GetFileModTime(const std::string& fileName) { // NOLINT
    return ::GetFileModTime(fileName.c_str());
}

/**
 * 使用默认系统浏览器打开 URL（如果可用）
 */
[[maybe_unused]] RLCPPAPI inline void OpenURL(const std::string& url) {
    return ::OpenURL(url.c_str());
}

/**
 * 加载图像
 */
[[maybe_unused]] RLCPPAPI inline ::Image LoadImage(const std::string& fileName) {
    return ::LoadImage(fileName.c_str());
}

/**
 * 从 RAW 文件数据加载图像
 */
[[maybe_unused]] RLCPPAPI inline ::Image
LoadImageRaw(const std::string& fileName, int width, int height, int format, int headerSize) {
    return ::LoadImageRaw(fileName.c_str(), width, height, format, headerSize);
}

/**
 * 加载动画图像数据
 */
[[maybe_unused]] RLCPPAPI inline ::Image LoadImageAnim(const std::string& fileName, int* frames) {
    return ::LoadImageAnim(fileName.c_str(), frames);
}

/**
 * 从内存缓冲区加载图像，fileType 指的是扩展名，如 "png"
 */
[[maybe_unused]] RLCPPAPI inline ::Image
LoadImageFromMemory(const std::string& fileType, const unsigned char* fileData, int dataSize) {
    return ::LoadImageFromMemory(fileType.c_str(), fileData, dataSize);
}

/**
 * 将图像数据导出到文件
 */
[[maybe_unused]] RLCPPAPI inline bool ExportImage(const Image& image, const std::string& fileName) {
    return ::ExportImage(image, fileName.c_str());
}

/**
 * 将图像导出为代码文件（.h），定义一个字节数组
 */
[[maybe_unused]] RLCPPAPI inline bool ExportImageAsCode(const Image& image, const std::string& fileName) {
    return ::ExportImageAsCode(image, fileName.c_str());
}

/**
 * 使用默认字体绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void DrawText(const char* text, int posX, int posY, int fontSize, ::Color color) {
    ::DrawText(text, posX, posY, fontSize, color);
}

/**
 * 使用默认字体绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
DrawText(const std::string& text, int posX, int posY, int fontSize, ::Color color) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

/**
 * 使用字体和附加参数绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
DrawTextEx(const Font& font, char* text, Vector2 position, float fontSize, float spacing, ::Color tint) {
    ::DrawTextEx(font, text, position, fontSize, spacing, tint);
}

/**
 * 使用字体和附加参数绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void
DrawTextEx(const Font& font, const std::string& text, Vector2 position, float fontSize, float spacing, ::Color tint) {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
}

/**
 * 使用字体和高级参数（旋转）绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void DrawTextPro(
    const Font& font,
    const char* text,
    Vector2 position,
    Vector2 origin,
    float rotation,
    float fontSize,
    float spacing,
    ::Color tint) {
    ::DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint);
}

/**
 * 使用字体和高级参数（旋转）绘制文本
 */
[[maybe_unused]] RLCPPAPI inline void DrawTextPro(
    const Font& font,
    const std::string& text,
    Vector2 position,
    Vector2 origin,
    float rotation,
    float fontSize,
    float spacing,
    ::Color tint) {
    ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
}

/**
 * 从文件加载字体（文件名必须包含扩展名）
 */
[[maybe_unused]] RLCPPAPI inline ::Font LoadFont(const std::string& fileName) {
    return ::LoadFont(fileName.c_str());
}

/**
 * 从文件加载字体（文件名必须包含扩展名）
 */
[[maybe_unused]] RLCPPAPI inline ::Font
LoadFontEx(const std::string& fileName, int fontSize, int* fontChars, int charsCount) {
    return ::LoadFontEx(fileName.c_str(), fontSize, fontChars, charsCount);
}

/**
 * 测量默认字体的字符串宽度
 */
[[maybe_unused]] RLCPPAPI inline int MeasureText(const char* text, int fontSize) {
    return ::MeasureText(text, fontSize);
}

/**
 * 测量默认字体的字符串宽度
 */
[[maybe_unused]] RLCPPAPI inline int MeasureText(const std::string& text, int fontSize) {
    return ::MeasureText(text.c_str(), fontSize);
}

/**
 * 检查两个文本字符串是否相等
 */
[[maybe_unused]] RLCPPAPI inline bool TextIsEqual(const char* text1, const char* text2) {
    return ::TextIsEqual(text1, text2);
}

/**
 * 检查两个文本字符串是否相等
 */
[[maybe_unused]] RLCPPAPI inline bool TextIsEqual(const std::string& text1, const std::string& text2) {
    return ::TextIsEqual(text1.c_str(), text2.c_str());
}

/**
 * 获取文本长度，检查 '\0' 结尾
 */
[[maybe_unused]] RLCPPAPI inline unsigned int TextLength(const char* text) {
    return ::TextLength(text);
}

/**
 * 获取文本长度，检查 '\0' 结尾
 */
[[maybe_unused]] RLCPPAPI inline unsigned int TextLength(const std::string& text) {
    return ::TextLength(text.c_str());
}

/**
 * 获取子文本
 */
[[maybe_unused]] RLCPPAPI inline std::string TextSubtext(const std::string& text, int position, int length) {
    return ::TextSubtext(text.c_str(), position, length);
}

/**
 * 替换文本字符串
 */
[[maybe_unused]] RLCPPAPI std::string
TextReplace(const std::string& text, const std::string& replace, const std::string& by) {
    const char* input = text.c_str();
    char* output = ::TextReplace(const_cast<char*>(input), replace.c_str(), by.c_str());
    if (output != NULL) {
        std::string stringOutput(output);
        free(output);
        return stringOutput;
    }
    return "";
}

/**
 * 在指定位置插入文本
 */
[[maybe_unused]] RLCPPAPI std::string TextInsert(const std::string& text, const std::string& insert, int position) {
    char* output = ::TextInsert(text.c_str(), insert.c_str(), position);
    if (output != NULL) {
        std::string stringOutput(output);
        free(output);
        return stringOutput;
    }
    return "";
}

/**
 * 将文本拆分为多个字符串
 */
[[maybe_unused]] RLCPPAPI std::vector<std::string> TextSplit(const std::string& text, char delimiter) {
    int count;
    const char** split = ::TextSplit(text.c_str(), delimiter, &count);
    return std::vector<std::string>(split, split + count);
}

/**
 * 查找字符串中第一次出现的文本
 */
[[maybe_unused]] RLCPPAPI inline int TextFindIndex(const std::string& text, const std::string& find) {
    return ::TextFindIndex(text.c_str(), find.c_str());
}

/**
 * 获取大写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string TextToUpper(const std::string& text) {
    return ::TextToUpper(text.c_str());
}

/**
 * 获取小写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string TextToLower(const std::string& text) {
    return ::TextToLower(text.c_str());
}

/**
 * 获取 Pascal 大小写版本的字符串
 */
[[maybe_unused]] RLCPPAPI inline std::string TextToPascal(const std::string& text) {
    return ::TextToPascal(text.c_str());
}

/**
 * 从文本中获取整数值（不支持负值）
 */
[[maybe_unused]] RLCPPAPI inline int TextToInteger(const std::string& text) {
    return ::TextToInteger(text.c_str());
}

} // namespace raylib

// #endif // RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_