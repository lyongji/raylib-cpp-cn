/*******************************************************************************************
 *
 *   raylib [models] example - first person maze
 *
 *   This example has been created using raylib 2.5 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2019 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    raylib::窗口 窗口(屏幕宽, 屏幕高, "raylib [models] example - first person maze");

    // Define the camera to look into our 3d world
    R相机 相机({0.2f, 0.4f, 0.2f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f);

    R图像 立方图("resources/cubicmap.png"); // Load cubicmap image (RAM)
    R纹理 cubicmap(立方图); // Convert image to texture to display (VRAM)
    R非托管网格 网格 =
        R非托管网格::立方体贴图(立方图, Vector3{1.0f, 1.0f, 1.0f}); // Use MeshUnmanaged, Mesh will be handled by Model
    R模型 模型(网格);

    // NOTE: By default each cube is mapped to one part of texture atlas
    R纹理 纹理("resources/cubicmap_atlas.png"); // Load map texture
    模型.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = 纹理; // Set map diffuse texture

    // Get map image data to be used for collision detection
    Color* 像素图 = 立方图.加载颜色();

    立方图.卸载(); // Unload image from RAM

    RVector3 映射位置(-16.0f, 0.0f, -8.0f); // Set model position
    RVector3 玩家坐标(相机.position); // Set player position

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        raylib::Vector3 旧机位(相机.position); // Store old camera position

        相机.更新(CAMERA_FIRST_PERSON); // Update camera

        // Check player collision (we simplify to 2D collision detection)
        raylib::Vector2 玩家位置(相机.position.x, 相机.position.z);
        float 玩家半径 = 0.1f; // Collision radius (player is modelled as a cilinder for collision)

        int 玩家单元X = static_cast<int>(玩家位置.x - 映射位置.x + 0.5f);
        int 玩家单元Y = static_cast<int>(玩家位置.y - 映射位置.z + 0.5f);

        // Out-of-limits security check
        if (玩家单元X < 0)
            玩家单元X = 0;
        else if (玩家单元X >= cubicmap.width)
            玩家单元X = cubicmap.width - 1;

        if (玩家单元Y < 0)
            玩家单元Y = 0;
        else if (玩家单元Y >= cubicmap.height)
            玩家单元Y = cubicmap.height - 1;

        // Check map collisions using image data and player position
        // TODO: Improvement: Just check player surrounding cells for collision
        for (int y = 0; y < cubicmap.height; y++) {
            for (int x = 0; x < cubicmap.width; x++) {
                if ((像素图[y * cubicmap.width + x].r == 255) && // Collision: white pixel, only check R channel
                    (玩家位置
                         .是圆在碰撞(玩家半径, {映射位置.x - 0.5f + x * 1.0f, 映射位置.z - 0.5f + y * 1.0f}, 1.0f))) {
                    // Collision detected, reset camera position
                    相机.position = 旧机位;
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        while (窗口.绘制中()) {
            窗口.清屏(RAYWHITE);

            相机.开始3D模式();
            {
                模型.绘制(映射位置); // Draw maze map
                // playerPosition.DrawCube((Vector3){ 0.2f, 0.4f, 0.2f }, RED);  // Draw player
            }
            相机.结束3D模式();

            cubicmap
                .绘制(Vector2{static_cast<float>(GetScreenWidth() - cubicmap.width * 4 - 20), 20}, 0.0f, 4.0f, WHITE);
            DrawRectangleLines(
                GetScreenWidth() - cubicmap.width * 4 - 20,
                20,
                cubicmap.width * 4,
                cubicmap.height * 4,
                GREEN);

            // Draw player position radar
            DrawRectangle(GetScreenWidth() - cubicmap.width * 4 - 20 + 玩家单元X * 4, 20 + 玩家单元Y * 4, 4, 4, RED);

            DrawFPS(10, 10);
        }

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadImageColors(像素图); // Unload color array

    //----------------------------------------------------------------------------------

    return 0;
}
