/*******************************************************************************************
 *
 *   raylib [shapes] example - Draw raylib logo using basic shapes
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
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

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [shapes] example - raylib logo using shapes");
    R颜色 前景(0, 68, 130);
    R颜色 背景 = R颜色::浅灰();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        while (窗口.绘制中()) {
            窗口.清屏(背景);

            前景.绘制矩形(屏幕宽 / 2 - 128, 屏幕高 / 2 - 128, 256, 256);
            背景.绘制矩形(屏幕宽 / 2 - 112, 屏幕高 / 2 - 112, 224, 224);
            前景.绘制文本("raylib", 屏幕宽 / 2 - 44, 屏幕高 / 2 + 24, 50);
            前景.绘制文本("cpp", 屏幕宽 / 2 - 74, 屏幕高 / 2 + 54, 50);

            DrawText("this is NOT a texture!", 350, 370, 10, GRAY);
        }
        //----------------------------------------------------------------------------------
    }

    return 0;
}
