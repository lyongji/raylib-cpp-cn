/*******************************************************************************************
 *
 *   raylib [text] example - Font filters
 *
 *   After font loading, font texture atlas filter could be configured for a softer
 *   display of the font when scaling it to different sizes, that way, it's not required
 *   to generate multiple fonts at multiple sizes (as long as the scaling is not very different)
 *
 *   This example has been created using raylib 1.3.0 (www.raylib.com)
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

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [text] example - font filters");

    // TTF Font loading with custom generation parameters
    R字体 字体("resources/KAISG.ttf", 96);

    // Generate mipmap levels to use trilinear filtering
    // NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
    字体.取纹理().取多级纹理();

    R文本 msg("Loaded Font", 字体.取基本大小(), BLACK, 字体);

    Vector2 字体位置 = {40.0f, 屏幕高 / 2.0f - 80.0f};
    Vector2 文本大小 = {0.0f, 0.0f};

    // Setup texture scaling filter
    字体.取纹理().设纹理过滤(TEXTURE_FILTER_POINT);
    int 当前字体过滤器 = 0; // TEXTURE_FILTER_POINT

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        msg.字体大小 += R鼠标::取滚轮移动值() * 4.0f;

        // Choose font texture filter method
        if (R键盘::是此键被按下(KEY_ONE)) {
            字体.取纹理().设纹理过滤(TEXTURE_FILTER_POINT);
            当前字体过滤器 = 0;
        }
        else if (R键盘::是此键被按下(KEY_TWO)) {
            字体.取纹理().设纹理过滤(TEXTURE_FILTER_BILINEAR);
            当前字体过滤器 = 1;
        }
        else if (R键盘::是此键被按下(KEY_THREE)) {
            // NOTE: Trilinear filter won't be noticed on 2D drawing
            字体.取纹理().设纹理过滤(TEXTURE_FILTER_TRILINEAR);
            当前字体过滤器 = 2;
        }

        文本大小 = msg.测量扩展();

        if (R键盘::是此键为按下(KEY_LEFT))
            字体位置.x -= 10;
        else if (R键盘::是此键为按下(KEY_RIGHT))
            字体位置.x += 10;

        // Load a dropped TTF file dynamically (at current fontSize)
        for (const auto& file : raylib::加载拖放文件()) {
            if (raylib::是此文件的后缀名(file, ".ttf")) {
                msg.字体 = 字体 = raylib::字体(file, 字体.取基本大小());
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        窗口.开始绘制();

        窗口.清屏(RAYWHITE);

        DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);
        DrawText("Use KEY_RIGHT and KEY_LEFT to move text", 20, 40, 10, GRAY);
        DrawText("Use 1, 2, 3 to change texture filter", 20, 60, 10, GRAY);
        DrawText("Drop a new TTF font for dynamic loading", 20, 80, 10, DARKGRAY);

        msg.绘制(字体位置);

        // TODO: It seems texSize measurement is not accurate due to chars offsets...
        // DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

        DrawRectangle(0, 屏幕高 - 80, 屏幕宽, 80, LIGHTGRAY);
        DrawText(TextFormat("Font size: %02.02f", msg.取字体大小()), 20, 屏幕高 - 50, 10, DARKGRAY);
        DrawText(TextFormat("Text size: [%02.02f, %02.02f]", 文本大小.x, 文本大小.y), 20, 屏幕高 - 30, 10, DARKGRAY);
        DrawText("CURRENT TEXTURE FILTER:", 250, 400, 20, GRAY);

        if (当前字体过滤器 == 0)
            DrawText("POINT", 570, 400, 20, BLACK);
        else if (当前字体过滤器 == 1)
            DrawText("BILINEAR", 570, 400, 20, BLACK);
        else if (当前字体过滤器 == 2)
            DrawText("TRILINEAR", 570, 400, 20, BLACK);

        窗口.结束绘制();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
