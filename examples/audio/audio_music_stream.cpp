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
    const int screenWidth = 800;
    const int screenHeight = 450;

    R窗口 window(screenWidth, screenHeight, "raylib [audio] example - music playing (streaming)");

    raylib::音频设备 audio; // Initialize audio device

    R音乐流 music("resources/target.ogg");

    music.播放();
    float timePlayed = 0.0f;
    bool pause = false;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.是可以关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        music.更新(); // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (raylib::键盘::是此键为按下(KEY_SPACE)) {
            music.停止();
            music.播放();
        }

        // Pause/Resume music playing
        if (raylib::键盘::是此键为按下(KEY_P)) {
            pause = !pause;

            if (pause) {
                music.暂停();
            }
            else {
                music.恢复();
            }
        }

        // Get timePlayed scaled to bar dimensions (400 pixels)
        timePlayed = music.取当前播放时间点() / music.取总时常() * 400;

        if (timePlayed > 400) music.停止();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            window.清除背景(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, LIGHTGRAY);

            DrawRectangle(200, 200, 400, 12, LIGHTGRAY);
            DrawRectangle(200, 200, static_cast<int>(timePlayed), 12, MAROON);
            DrawRectangleLines(200, 200, 400, 12, GRAY);

            DrawText("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, LIGHTGRAY);
            DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, LIGHTGRAY);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
