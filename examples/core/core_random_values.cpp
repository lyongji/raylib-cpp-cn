/*******************************************************************************************
 *
 *   raylib [core] example - Generate random values
 *
 *   This example has been created using raylib 1.1 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2014 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - generate random values");

    int 帧计数器 = 0; // Variable used to count frames

    int 随机值 = GetRandomValue(-8, 5); // Get a random integer number between -8 and 5 (both included)

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        帧计数器++;

        // Every two seconds (120 frames) a new random value is generated
        if (((帧计数器 / 120) % 2) == 1) {
            随机值 = GetRandomValue(-8, 5);
            帧计数器 = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        while (窗口.绘制中()) {
            窗口.清屏(RAYWHITE);

            raylib::绘制文本("Every 2 seconds a new random value is generated:", 130, 100, 20, MAROON);

            raylib::绘制文本(TextFormat("%i", 随机值), 360, 180, 80, LIGHTGRAY);
        }

        //----------------------------------------------------------------------------------
    }

    return 0;
}
