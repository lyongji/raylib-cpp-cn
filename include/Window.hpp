// #ifndef RAYLIB_CPP_INCLUDE_WINDOW_HPP_
// #define RAYLIB_CPP_INCLUDE_WINDOW_HPP_
#pragma once

#include <string>

#include "./RaylibException.hpp"
#include "./Vector2.hpp"
#include "./raylib.hpp"

namespace raylib {
/**
 * 窗口和图形设备函数
 */
class Window {
public:
    /**
     * 构建一个 Window 对象，但推迟初始化。确保手动调用 Init()。
     *
     * @see Init()
     */
    Window() = default;

    /**
     * 初始化窗口和 OpenGL 上下文。
     *
     * @param width 窗口的宽度
     * @param height 窗口的高度
     * @param title 窗口的标题
     * @param flags 初始化窗口前设置的 ConfigFlags。详见 SetConfigFlags。
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException 如果窗口初始化失败则抛出异常
     */
    Window(int width, int height, const std::string& title = "raylib", unsigned int flags = 0) {
        Init(width, height, title, flags);
    }

    /**
     * 关闭窗口并卸载 OpenGL 上下文
     */
    ~Window() { Close(); }

    /**
     * 初始化窗口
     *
     * @param width 窗口的宽度
     * @param height 窗口的高度
     * @param title 窗口的标题
     * @param flags 初始化窗口前设置的 ConfigFlags。详见 SetConfigFlags。
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException 如果窗口初始化失败则抛出异常
     */
    static void Init(int width = 800, int height = 450, const std::string& title = "raylib", unsigned int flags = 0) {
        if (flags != 0) {
            ::SetConfigFlags(flags);
        }
        ::InitWindow(width, height, title.c_str());
        if (!::IsWindowReady()) {
            throw RaylibException("Failed to create Window");
        }
    }

    /**
     * 检查是否按下 ESC 键或点击关闭图标
     */
    static bool ShouldClose() { return ::WindowShouldClose(); }

    /**
     * 设置自定义退出键（默认是 ESC）
     */
    static void SetExitKey(int key) { ::SetExitKey(key); }

    /**
     * 关闭窗口并卸载 OpenGL 上下文
     */
    static void Close() {
        if (::IsWindowReady()) {
            ::CloseWindow();
        }
    }

    /**
     * 检查光标是否在当前屏幕上
     */
    static bool IsCursorOnScreen() { return ::IsCursorOnScreen(); }

    /**
     * 检查窗口是否当前处于全屏模式
     */
    static bool IsFullscreen() { return ::IsWindowFullscreen(); }

    /**
     * 检查窗口是否当前隐藏
     */
    static bool IsHidden() { return ::IsWindowHidden(); }

    /**
     * 检查窗口是否当前最小化
     */
    static bool IsMinimized() { return ::IsWindowMinimized(); }

    /**
     * 检查窗口是否当前最大化
     */
    static bool IsMaximized() { return ::IsWindowMaximized(); }

    /**
     * 检查窗口是否当前聚焦
     */
    static bool IsFocused() { return ::IsWindowFocused(); }

    /**
     * 检查窗口是否在上一个帧中被调整大小
     */
    static bool IsResized() { return ::IsWindowResized(); }

    /**
     * 检查是否启用了特定的窗口标志
     */
    static bool IsState(unsigned int flag) { return ::IsWindowState(flag); }

    /**
     * 使用标志设置窗口配置状态
     */
    Window& SetState(unsigned int flag) {
        ::SetWindowState(flag);
        return *this;
    }

    /**
     * 清除窗口配置状态标志
     */
    Window& ClearState(unsigned int flag) {
        ::ClearWindowState(flag);
        return *this;
    }

    /**
     * 用给定的颜色清除窗口背景
     */
    Window& ClearBackground(const ::Color& color = BLACK) {
        ::ClearBackground(color);
        return *this;
    }

    /**
     * 切换窗口状态：全屏/窗口化
     */
    Window& ToggleFullscreen() {
        ::ToggleFullscreen();
        return *this;
    }

    /**
     * 设置应用程序是否应为全屏模式
     */
    Window& SetFullscreen(bool fullscreen) {
        if (fullscreen) {
            if (!IsFullscreen()) {
                ToggleFullscreen();
            }
        }
        else {
            if (IsFullscreen()) {
                ToggleFullscreen();
            }
        }

        return *this;
    }

    /**
     * 切换窗口状态：无边框/窗口化
     */
    Window& ToggleBorderless() {
        ::ToggleBorderlessWindowed();
        return *this;
    }

    /**
     * 设置窗口状态：最大化（仅限 PLATFORM_DESKTOP）
     */
    Window& Maximize() {
        ::MaximizeWindow();
        return *this;
    }

    /**
     * 设置窗口状态：最小化（仅限 PLATFORM_DESKTOP）
     */
    Window& Minimize() {
        ::MinimizeWindow();
        return *this;
    }

    /**
     * 设置窗口状态：恢复到正常大小（仅限 PLATFORM_DESKTOP）
     */
    Window& Restore() {
        ::RestoreWindow();
        return *this;
    }

    /**
     * 设置窗口图标
     */
    Window& SetIcon(const ::Image& image) {
        ::SetWindowIcon(image);
        return *this;
    }

    /**
     * 设置窗口图标（多个图像，RGBA 32 位，仅限 PLATFORM_DESKTOP）
     */
    Window& SetIcons(Image* images, int count) {
        ::SetWindowIcons(images, count);
        return *this;
    }

    /**
     * 设置窗口标题
     */
    Window& SetTitle(const std::string& title) {
        ::SetWindowTitle(title.c_str());
        return *this;
    }

    /**
     * 设置窗口在屏幕上的位置
     */
    Window& SetPosition(int x, int y) {
        ::SetWindowPosition(x, y);
        return *this;
    }

    /**
     * 设置窗口在屏幕上的位置
     */
    Window& SetPosition(const ::Vector2& position) {
        return SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * 设置当前窗口的显示器
     */
    Window& SetMonitor(int monitor) {
        ::SetWindowMonitor(monitor);
        return *this;
    }

    /**
     * 设置窗口的最小尺寸
     */
    Window& SetMinSize(int width, int height) {
        ::SetWindowMinSize(width, height);
        return *this;
    }

    /**
     * 设置窗口的最小尺寸
     */
    Window& SetMinSize(const ::Vector2& size) {
        ::SetWindowMinSize(static_cast<int>(size.x), static_cast<int>(size.y));
        return *this;
    }

    /**
     * 设置窗口的尺寸
     */
    Window& SetSize(int width, int height) {
        ::SetWindowSize(width, height);
        return *this;
    }

    /**
     * 设置窗口的不透明度 [0.0f..1.0f]（仅限 PLATFORM_DESKTOP）
     */
    Window& SetOpacity(float opacity) {
        ::SetWindowOpacity(opacity);
        return *this;
    }

    /**
     * 设置窗口聚焦（仅限 PLATFORM_DESKTOP）
     */
    Window& SetFocused() {
        ::SetWindowFocused();
        return *this;
    }

    /**
     * 设置窗口的尺寸
     */
    Window& SetSize(const ::Vector2& size) { return SetSize(static_cast<int>(size.x), static_cast<int>(size.y)); }

    /**
     * 获取屏幕的宽度和高度
     */
    static Vector2 GetSize() { return {static_cast<float>(GetWidth()), static_cast<float>(GetHeight())}; }

    /**
     * 获取窗口的句柄
     */
    static void* GetHandle() { return ::GetWindowHandle(); }

    /**
     * 设置画布（帧缓冲区）开始绘制
     */
    Window& BeginDrawing() {
        ::BeginDrawing();
        return *this;
    }

    /**
     * 结束画布绘制并交换缓冲区（双缓冲）
     */
    Window& EndDrawing() {
        ::EndDrawing();
        return *this;
    }

    /**
     * 获取当前屏幕宽度
     */
    static int GetWidth() { return ::GetScreenWidth(); }

    /**
     * 获取当前屏幕高度
     */
    static int GetHeight() { return ::GetScreenHeight(); }

    /**
     * 获取当前渲染宽度（考虑 HiDPI）
     */
    static int GetRenderWidth() { return ::GetRenderWidth(); }

    /**
     * 获取当前渲染高度（考虑 HiDPI）
     */
    static int GetRenderHeight() { return ::GetRenderHeight(); }

    /**
     * 获取窗口在显示器上的位置 XY
     */
    static Vector2 GetPosition() { return ::GetWindowPosition(); }

    /*
     * 获取当前窗口监视器
     */
    static int GetMonitor() { return ::GetCurrentMonitor(); }

    /**
     * 获取窗口的缩放 DPI 因子
     */
    static Vector2 GetScaleDPI() { return ::GetWindowScaleDPI(); }

    /**
     * 设置剪贴板文本内容
     */
    static void SetClipboardText(const std::string& text) { ::SetClipboardText(text.c_str()); }

    /**
     * 获取剪贴板文本内容
     */
    static std::string GetClipboardText() { return ::GetClipboardText(); }

    /**
     * 设置目标 FPS（最大值）
     */
    Window& SetTargetFPS(int fps) {
        ::SetTargetFPS(fps);
        return *this;
    }

    /**
     * 返回当前 FPS
     */
    static int GetFPS() { return ::GetFPS(); }

    /**
     * 绘制当前 FPS
     */
    static void DrawFPS(int posX = 10, int posY = 10) { ::DrawFPS(posX, posY); }

    /**
     * 返回上一帧绘制的时间（秒）
     */
    static float GetFrameTime() { return ::GetFrameTime(); }

    /**
     * 返回自 InitWindow() 以来的时间（秒）
     */
    static double GetTime() { return ::GetTime(); }

    /**
     * 检查窗口是否已成功初始化
     */
    static bool IsReady() { return ::IsWindowReady(); }

    /**
     * 设置 raylib 的配置标志
     *
     * @param flags 要应用的 ConfigFlags
     *
     * @see ::SetConfigFlags
     */
    static void SetConfigFlags(unsigned int flags) { ::SetConfigFlags(flags); }

    /**
     * Alternates between calling `BeginDrawing()` and `EndDrawing()`.
     *
     * @code
     * while (window.Drawing()) {
     *     DrawRectangle();
     * }
     * @endcode
     *
     * @return True if we're within the `BeginDrawing()` scope.
     */
    bool Drawing() {
        if (m_drawing) {
            EndDrawing();
            m_drawing = false;
        }
        else {
            BeginDrawing();
            m_drawing = true;
        }

        return m_drawing;
    }
protected:
    /**
     * Handles the internal drawing state for calling either `BeginDrawing()` or `EndDrawing()` from the `Drawing()`
     * function.
     *
     * @see Drawing()
     */
    bool m_drawing = false;
};
} // namespace raylib

using RWindow = raylib::Window;

// #endif // RAYLIB_CPP_INCLUDE_WINDOW_HPP_