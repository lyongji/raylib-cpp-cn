/*******************************************************************************************
 *
 *   raylib [textures] example - Image loading and drawing on it
 *
 *   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
 *
 *   This example has been created using raylib 1.4 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2016 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib [textures] example - image drawing");
    R颜色 darkGray = DARKGRAY;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    R图像 猫("resources/cat.png"); // Load image in CPU memory (RAM)
    猫.裁剪(R矩形(100, 10, 280, 380)) // Crop an image piece
        .水平翻转() // Flip cropped image horizontally
        .调整尺寸(150, 200); // Resize flipped-cropped image

    R图像 鹦鹉("resources/parrots.png"); // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    鹦鹉.绘制(猫, {0, 0, static_cast<float>(猫.取宽()), static_cast<float>(猫.取高())}, {30, 40, 猫.取宽() * 1.5f, 猫.取高() * 1.5f});
    鹦鹉.裁剪( {0, 50, static_cast<float>(鹦鹉.取宽()),static_cast<float>( 鹦鹉.取高() - 100)}); // Crop resulting image

    // Load custom font for frawing on image
    raylib::字体 字体("resources/custom_jupiter_crash.png");

    // Draw over image using custom font
    鹦鹉.绘制文本(字体, "PARROTS & CAT", raylib::Vector2(300, 230), 字体.baseSize, -2);

    raylib::纹理2D texture(鹦鹉); // Image converted to texture, uploaded to GPU memory (VRAM)

    窗口.设目标FPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        窗口.开始绘制();
        {
            窗口.清屏(RAYWHITE);

            texture.绘制((屏幕宽 / 2 - texture.width / 2), 屏幕高 / 2 - texture.height / 2 - 40);
            darkGray.绘制矩形边框(
                屏幕宽 / 2 - texture.width / 2,
                屏幕高 / 2 - texture.height / 2 - 40,
                texture.width,
                texture.height);

            darkGray.绘制文本("We are drawing only one texture from various images composed!", 240, 350, 10);
            darkGray.绘制文本(
                "Source images have been cropped, scaled, flipped and copied one over the other.",
                190,
                370,
                10);
        }
        窗口.结束绘制();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
