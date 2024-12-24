/*******************************************************************************************
 *
 *   raylib [audio] example - Music playing (streaming)
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [audio] example - music playing (streaming)");

    R音频设备 音频驱动; // Initialize audio device

    R音乐流 音乐("resources/target.ogg");

    R文本 文本;

    R颜色 颜色(R颜色::浅灰());

    音乐.播放();
    float 游戏时间 = 0.0;
    bool 暂停 = false;

    窗口.设目标FPS(60);

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        音乐.更新(); // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (R键盘::是此键为按下(KEY_SPACE)) {
            音乐.停止();
            音乐.播放();
        }

        // Pause/Resume music playing
        if (R键盘::是此键为按下(KEY_P)) {
            暂停 = !暂停;

            if (暂停) {
                音乐.暂停();
            }
            else {
                音乐.恢复();
            }
        }

        // Get timePlayed scaled to bar dimensions (400 pixels)
        游戏时间 = 音乐.取当前播放时间点() / 音乐.取总时常() * 400;

        if (游戏时间 > 400) {
            音乐.停止();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        窗口.开始绘制();
        {
            窗口.清屏(RAYWHITE);

            // DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, R颜色::浅灰());
            文本.绘制("MUSIC SHOULD BE PLAYING!", 255, 150, 20, R颜色::浅灰());

            颜色.绘制矩形(200, 200, 400, 12);
            颜色 = R颜色::深褐();
            颜色.绘制矩形(200, 200, static_cast<int>(游戏时间), 12);
            颜色 = R颜色::灰();
            颜色.绘制矩形边框(200, 200, 400, 12);

            文本.绘制("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, R颜色::浅灰());
            文本.绘制("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, R颜色::浅灰());
        }
        窗口.结束绘制();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
