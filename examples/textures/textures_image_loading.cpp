/*******************************************************************************************
 *
 *   raylib [textures] example - Image loading and texture creation
 *
 *   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU
 *memory (VRAM)
 *
 *   This example has been created using raylib 1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "Color.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "raylib-cpp.hpp"

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  int 屏幕宽 = 800;
  int 屏幕高 = 450;

  raylib::窗口 窗口(屏幕宽, 屏幕高,
                    "raylib [textures] example - image loading");
  raylib::纹理 纹理("resources/raylib_logo.png");
  raylib::颜色 文本颜色 = R颜色::浅灰();

  // Main game loop
  while (!窗口.检查是否已关闭()) { // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    // Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
      窗口.清屏(R颜色::荧白());

      纹理.绘制(屏幕宽 / 2 - 纹理.取宽() / 2, 屏幕高 / 2 - 纹理.取高() / 2);

      文本颜色.绘制文本("this IS a texture loaded from an image!", 300, 370,
                        10);
    }

    //----------------------------------------------------------------------------------
  }

  return 0;
}
