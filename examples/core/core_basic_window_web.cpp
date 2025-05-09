/*******************************************************************************************
 *
 *   raylib-cpp [core] example - Basic window (adapted for HTML5 platform)
 *
 *   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
 *   As you will notice, code structure is slightly diferent to the other examples...
 *   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int 屏幕宽 = 800;
int 屏幕高 = 450;
R窗口 窗口;
R文本 文本;
//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void 帧绘制更新(); // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    窗口.初始化(屏幕宽, 屏幕高, "raylib-cpp [core] example - basic window");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(帧绘制更新, 0, 1);
#else
    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) // Detect window close button or ESC key
    {
        帧绘制更新();
    }
#endif

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void 帧绘制更新() {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
        窗口.清屏(R颜色::白烟());

        文本.绘制("Congrats! You created your first raylib-cpp window!", 190, 200, 20, LIGHTGRAY);
    }
    //----------------------------------------------------------------------------------
}
