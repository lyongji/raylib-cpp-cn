/*******************************************************************************************
 *
 *   raylib [core] example - Mouse input
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

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - mouse input");

    raylib::Vector2 球位置(-100.0, -100.0);
    R颜色 球颜色{R颜色::深蓝()};
    R颜色 文本颜色{R颜色::深灰()};

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        球位置 = R鼠标::取位置();

        if (R鼠标::是此按钮为按下(MOUSE_LEFT_BUTTON))
            球颜色 = R颜色::褐色();
        else if (R鼠标::是此按钮为按下(MOUSE_MIDDLE_BUTTON))
            球颜色 = R颜色::柠檬绿();
        else if (R鼠标::是此按钮为按下(MOUSE_RIGHT_BUTTON))
            球颜色 = R颜色::深蓝();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        while (窗口.绘制中()) {
            窗口.清屏(R颜色::浅灰());

            球位置.绘制圆形(40, 球颜色);

            文本颜色.绘制文本("move ball with mouse and click mouse button to change color", 10, 10, 20);
        }

        //----------------------------------------------------------------------------------
    }

    return 0;
}
