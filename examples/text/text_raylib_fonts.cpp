/*******************************************************************************************
 *
 *   raylib [text] example - raylib font loading and usage
 *
 *   NOTE: raylib is distributed with some free to use fonts (even for commercial pourposes!)
 *         To view details and credits for those fonts, check raylib license file
 *
 *   This example has been created using raylib 1.7 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2017 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include <array>
#include <vector>

#include "raylib-cpp.hpp"

#define MAX_FONTS 8

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int 屏幕宽 = 800;
    int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [text] example - raylib fonts");
    R颜色 文本颜色 = DARKGRAY;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    std::array<raylib::字体, MAX_FONTS> 字体组 = {
        raylib::字体("resources/fonts/alagard.png"),
        raylib::字体("resources/fonts/pixelplay.png"),
        raylib::字体("resources/fonts/mecha.png"),
        raylib::字体("resources/fonts/setback.png"),
        raylib::字体("resources/fonts/romulus.png"),
        raylib::字体("resources/fonts/pixantiqua.png"),
        raylib::字体("resources/fonts/alpha_beta.png"),
        raylib::字体("resources/fonts/jupiter_crash.png")};

    std::array<std::string, MAX_FONTS> messages = {
        "ALAGARD FONT designed by Hewett Tsoi",
        "PIXELPLAY FONT designed by Aleksander Shevchuk",
        "MECHA FONT designed by Captain Falcon",
        "SETBACK FONT designed by Brian Kent (AEnigma)",
        "ROMULUS FONT designed by Hewett Tsoi",
        "PIXANTIQUA FONT designed by Gerhard Grossmann",
        "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
        "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)"};

    std::array<int, MAX_FONTS> spacings = {2, 4, 8, 4, 3, 4, 4, 1};

    std::array<raylib::Vector2, MAX_FONTS> positions;

    for (int i = 0; i < 字体组.size(); i++) {
        auto size = 字体组[i].测量文本(messages[i], 字体组[i].baseSize * 2, spacings[i]);
        positions[i].x = 屏幕宽 / 2 - size.x / 2;
        positions[i].y = 60 + 字体组[i].baseSize + 45 * i;
    }

    // Small Y position corrections
    positions[3].y += 8;
    positions[4].y += 2;
    positions[7].y -= 8;

    std::array<raylib::颜色, MAX_FONTS> 颜色组 = {MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD, RED};
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
            窗口.清屏(RAYWHITE);

            文本颜色.绘制文本("free fonts included with raylib", 250, 20, 20);
            文本颜色.绘制线段(220, 50, 590, 50);

            for (int i = 0; i < 字体组.size(); i++) {
                字体组[i].绘制文本(messages[i], positions[i], 字体组[i].baseSize * 2, spacings[i], 颜色组[i]);
            }
        }

        //----------------------------------------------------------------------------------
    }

    return 0;
}
