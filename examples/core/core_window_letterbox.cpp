/*******************************************************************************************
 *
 *   raylib [core] example - window scale letterbox (and virtual mouse)
 *
 *   Example originally created with raylib 2.5, last time updated with
 *raylib 4.0
 *
 *   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria
 *(@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an
 *OSI-certified, BSD-like license that allows static linking with closed source
 *software
 *
 *   Copyright (c) 2019-2023 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"
#include "raymath.hpp" // Required for: Vector2Clamp()
#include <array>
#include <format>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  const int 窗口宽 = 800;
  const int 窗口高 = 450;

  // Enable config flags for resizable window and vertical synchro
  R窗口 窗口(窗口宽, 窗口高, "raylib [core] example - window scale letterbox",
             FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  窗口.设最小尺寸(320, 240);

  int 游戏屏幕宽 = 640;
  int 游戏屏幕高 = 480;

  // Render texture initialization, used to hold the rendering result so we can
  // easily resize it
  R渲染纹理2D 渲染目标(游戏屏幕宽, 游戏屏幕高);
  渲染目标.取颜色纹理().设纹理过滤模式(
      TEXTURE_FILTER_BILINEAR); // Texture scale filter to use
  std::array<R颜色, 10> 颜色组;
  for (auto &i : 颜色组) {
    i = R颜色{(unsigned char)GetRandomValue(100, 250),
              (unsigned char)GetRandomValue(50, 150),
              (unsigned char)GetRandomValue(10, 100), 255};
  }

  窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!窗口.检查是否已关闭()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // Compute required framebuffer scaling
    float 尺寸 = MIN((float)GetScreenWidth() / 游戏屏幕宽,
                     (float)GetScreenHeight() / 游戏屏幕高);

    if (R键盘::是否正在按下(KEY_SPACE)) {
      // Recalculate random colors for the bars
      for (auto &i : 颜色组) {
        i = R颜色{(unsigned char)GetRandomValue(100, 250),
                  (unsigned char)GetRandomValue(50, 150),
                  (unsigned char)GetRandomValue(10, 100), 255};
      }
    }

    // Update virtual mouse (clamped mouse value behind game screen)
    raylib::Vector2 鼠标 = R鼠标::取位置();
    raylib::Vector2 虚拟鼠标(
        (鼠标.x - (GetScreenWidth() - (游戏屏幕宽 * 尺寸)) * 0.5f) / 尺寸,
        (鼠标.y - (GetScreenHeight() - (游戏屏幕高 * 尺寸)) * 0.5f) / 尺寸);
    虚拟鼠标 = 虚拟鼠标.限制(raylib::Vector2::零向量(),
                             raylib::Vector2(游戏屏幕宽, 游戏屏幕高));

    // Apply the same transformation as the virtual mouse to the real mouse
    // (i.e. to work with raygui) SetMouseOffset(-(GetScreenWidth() -
    // (gameScreenWidth*scale))*0.5f, -(GetScreenHeight() -
    // (gameScreenHeight*scale))*0.5f);
    // SetMouseScale(1/scale, 1/scale);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    // Draw everything in the render texture, note this will not be rendered on
    // screen, yet
    渲染目标.开始绘制();
    窗口.清屏(RAYWHITE); // Clear render texture background color

    for (int i = 0; i < 10; i++)
      DrawRectangle(0, (游戏屏幕高 / 10) * i, 游戏屏幕宽, 游戏屏幕高 / 10,
                    颜色组[i]);

    raylib::绘制文本("If executed inside a window,\nyou can resize the "
                     "window,\nand see the screen scaling!",
                     10, 25, 20, WHITE);
    raylib::绘制文本(
        std::format("Default Mouse: [%i , %i]", (int)鼠标.x, (int)鼠标.y), 350,
        25, 20, GREEN);
    raylib::绘制文本(std::format("Virtual Mouse: [%i , %i]", (int)虚拟鼠标.x,
                                 (int)虚拟鼠标.y),
                     350, 55, 20, YELLOW);
    渲染目标.结束绘制();

    while (窗口.绘制中()) {
      窗口.清屏(BLACK); // Clear screen background

      // Draw render texture to screen, properly scaled
      渲染目标.取颜色纹理().绘制(
          R矩形(0.0f, 0.0f, 渲染目标.texture.width, -渲染目标.texture.height),
          R矩形((GetScreenWidth() - (游戏屏幕宽 * 尺寸)) * 0.5F,
                (GetScreenHeight() - (游戏屏幕高 * 尺寸)) * 0.5F,
                游戏屏幕宽 * 尺寸, 游戏屏幕高 * 尺寸),
          RVector2::零向量(), 0.0f, WHITE);
    }
    //--------------------------------------------------------------------------------------
  }

  return 0;
}