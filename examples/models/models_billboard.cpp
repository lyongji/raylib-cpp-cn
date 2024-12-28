/*******************************************************************************************
 *
 *   raylib [models] example - Drawing billboards
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

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [models] example - drawing billboards");

    // Define the camera to look into our 3d world
    R相机 相机(RVector3(5.0, 4.0, 5.0), RVector3(0.0, 2.0, 0.0), RVector3(0.0, 1.0, 0.0), 45.0, CAMERA_PERSPECTIVE);

    R纹理2D 公告牌("resources/billboard.png"); // Our texture billboard
    RVector3 公告牌位置(0.0f, 2.0f, 0.0f); // Position where draw billboard

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        相机.更新(CAMERA_ORBITAL); // Update camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        窗口.开始绘制();
        {
            窗口.清屏(RAYWHITE);

            相机.开始3D模式();
            {
                DrawGrid(10, 1.0); // Draw a grid
                公告牌.绘制公告板(相机, 公告牌位置, 2.0);
            }
            相机.结束3D模式();

            DrawFPS(10, 10);
        }
        窗口.结束绘制();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
