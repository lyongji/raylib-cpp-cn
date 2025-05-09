/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
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
    int 屏幕宽 = 800;
    int 屏幕高 = 450;
    R颜色 文本颜色 = R颜色::浅灰();
    R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - basic window");

    窗口.设目标FPS(60);
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
            文本颜色.绘制文本("Congrats! You created your first window!", 190, 200, 20);
        }

        //----------------------------------------------------------------------------------
    }

    return 0;
}
