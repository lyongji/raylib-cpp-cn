/*******************************************************************************************
 *
 *   raylib [core] example - World to screen
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
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

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    R相机 相机(Vector3(10.0, 10.0, 10.0), Vector3(), Vector3(0.0, 1.0, 0.0), 45.0, CAMERA_PERSPECTIVE);

    Vector3 盒子位置{0.0, 1.0, 0.0};
    Vector2 盒子屏幕位置;

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.检查是否已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        相机.更新(CAMERA_THIRD_PERSON); // Update camera

        // Calculate cube screen space position (with a little offset to be in top)
        盒子屏幕位置 = GetWorldToScreen({盒子位置.x, (盒子位置.y + 2.5f), 盒子位置.z}, 相机);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        while (窗口.绘制中()) {
            窗口.清屏(RAYWHITE);

            相机.启用3D模式();
            {
                DrawCube(盒子位置, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(盒子位置, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);
            }
            相机.禁用3D模式();

            raylib::绘制文本(
                "Enemy: 100 / 100",
                (盒子屏幕位置.x - MeasureText("Enemy: 100/100", 20) / 2),
                盒子屏幕位置.y,
                20,
                BLACK);
            raylib::绘制文本(
                "Text is always on top of the cube",
                (屏幕宽 - MeasureText("Text is always on top of the cube", 20)) / 2,
                25,
                20,
                GRAY);
        }

        //----------------------------------------------------------------------------------
    }

    return 0;
}
