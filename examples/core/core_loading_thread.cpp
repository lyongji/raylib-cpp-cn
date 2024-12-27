/*******************************************************************************
 *
 *   raylib example - loading thread
 *
 *   This example has been created using raylib-cpp (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license
 *   (View raylib.h for details)
 *
 *   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
 *   Copyright (c) 2021 Paul Keir (University of the West of Scotland)
 *
 *******************************************************************************/

#include <atomic> // C++ atomic data types
#include <chrono> // For: chrono::steady_clock::now()
#include <system_error> // May be thrown by thread c'tor
#include <thread> // C++11 standard library threads

#include "raylib-cpp.hpp"

// Using C++ std::atomic_bool (aka. std::atomic<bool>) for synchronization.
// n.b. A plain built-in type can't be used for inter-thread synchronization
std::atomic_bool dataLoaded{false};
static void 加载数据线程(); // Loading data thread function declaration
static int dataProgress = 0; // Data progress accumulator

int main() {
    // Initialization
    //--------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - loading thread");
    R颜色 颜色;
    std::thread 线程Id; // 加载数据线程id

    enum 状态 {
        等待,
        加载,
        完成
    };
    状态 当前状态 = 状态::等待;
    int framesCounter = 0;

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------
        switch (当前状态) {
            case 等待:
                if (R键盘::是此键为按下(KEY_ENTER)) {
                    try {
                        线程Id = std::thread(加载数据线程);
                        TraceLog(LOG_INFO, "Loading thread initialized successfully");
                    } catch (std::system_error& e) {
                        TraceLog(LOG_ERROR, "Error: %s", e.what());
                    }

                    当前状态 = 状态::加载;
                }
                break;

            case 加载:
                framesCounter++;
                if (dataLoaded.load()) {
                    framesCounter = 0;
                    当前状态 = 状态::完成;
                }
                break;

            case 完成:
                if (R键盘::是此键为按下(KEY_ENTER)) {
                    // 重置再启动
                    dataLoaded = false;
                    dataProgress = 0;
                    当前状态 = 状态::等待;
                }
                break;

            default: break;
        }
        //----------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------
        窗口.开始绘制();
        {
            窗口.清屏(RAYWHITE);

            switch (当前状态) {
                case 等待: raylib::绘制文本("PRESS ENTER to START LOADING DATA", 150, 170, 20, DARKGRAY); break;

                case 加载:
                    颜色 = R颜色::天蓝();
                    颜色.绘制矩形(150, 200, dataProgress, 60);
                    if ((framesCounter / 15) % 2) raylib::绘制文本("LOADING DATA...", 240, 210, 40, DARKBLUE);
                    break;

                case 完成:
                    颜色 = R颜色::柠檬绿();
                    颜色.绘制矩形(150, 200, 500, 60);
                    raylib::绘制文本("DATA LOADED!", 250, 210, 40, GREEN);
                    break;
            }
            颜色 = R颜色::深灰();
            颜色.绘制矩形边框(150, 200, 500, 60);
        }

        窗口.结束绘制();
        //----------------------------------------------------------------------
    }

    if (线程Id.joinable()) // The user might quit without creating a thread.
        线程Id.join(); // Good etiquette, but may take a second.

    return 0;
}

// Loading data thread function definition
static void 加载数据线程() {
    using namespace std::chrono;
    int timeCounter = 0; // Time counted in ms

    auto prevTime = steady_clock::now();

    // We simulate data loading with a time counter for 5 seconds
    while (timeCounter < 5000) {
        auto currentTime = steady_clock::now() - prevTime;
        timeCounter = duration_cast<milliseconds>(currentTime).count();

        // We accumulate time over a global variable to be used in
        // main thread as a progress bar
        dataProgress = timeCounter / 10;
    }

    // When data has finished loading, we set global variable
    dataLoaded = true;
}
