/*******************************************************************************************
 *
 *   raylib [text] example - Font loading and usage
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2014 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include <string>

#include "raylib-cpp.hpp"

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    raylib::窗口 窗口(屏幕宽, 屏幕高, "raylib [text] example - sprite fonts usage");

    std::string msg1 = "THIS IS A custom SPRITE FONT...";
    std::string msg2 = "...and this is ANOTHER CUSTOM font...";
    std::string msg3 = "...and a THIRD one! GREAT! :D";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    raylib::字体 font1("resources/custom_mecha.png"); // Font loading
    raylib::字体 font2("resources/custom_alagard.png"); // Font loading
    raylib::字体 font3("resources/custom_jupiter_crash.png"); // Font loading

    raylib::Vector2 fontPosition1(
        屏幕宽 / 2 - MeasureTextEx(font1, msg1.c_str(), font1.baseSize, -3).x / 2,
        屏幕高 / 2 - font1.baseSize / 2 - 80);

    raylib::Vector2 fontPosition2(
        屏幕宽 / 2 - MeasureTextEx(font2, msg2.c_str(), font2.baseSize, -2).x / 2,
        屏幕高 / 2 - font2.baseSize / 2 - 10);

    raylib::Vector2 fontPosition3(
        屏幕宽 / 2 - MeasureTextEx(font3, msg3.c_str(), font3.baseSize, 2).x / 2,
        屏幕高 / 2 - font3.baseSize / 2 + 50);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables here...
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            窗口.清屏(RAYWHITE);

            font1.绘制文本(msg1, fontPosition1, font1.baseSize, -3);
            font2.绘制文本(msg2, fontPosition2, font2.baseSize, -2);
            font3.绘制文本(msg3, fontPosition3, font3.baseSize, 2);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
