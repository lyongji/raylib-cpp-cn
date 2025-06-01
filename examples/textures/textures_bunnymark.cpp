/*******************************************************************************************
 *
 *   raylib [textures] example - Bunnymark
 *
 *   This example has been created using raylib 1.6 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2014-2019 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include <list>

#include "raylib-cpp.hpp"

// This is the maximum amount of elements (quads) per batch
// NOTE: This value is defined in [rlgl] module and can be changed there
#define MAX_BATCH_ELEMENTS 8192

class 兔子 {
public:
  兔子() {
    position = GetMousePosition();
    speed.x = static_cast<float>(GetRandomValue(-250, 250)) / 60.0f;
    speed.y = static_cast<float>(GetRandomValue(-250, 250)) / 60.0f;
    color = R颜色(GetRandomValue(50, 240), GetRandomValue(80, 240),
                  GetRandomValue(100, 240));
  }

  void 更新(const raylib::纹理2D &texBunny) {
    position.x += speed.x;
    position.y += speed.y;

    if (((position.x + texBunny.width / 2) > GetScreenWidth()) ||
        ((position.x + texBunny.width / 2) < 0))
      speed.x *= -1;
    if (((position.y + texBunny.height / 2) > GetScreenHeight()) ||
        ((position.y + texBunny.height / 2 - 40) < 0))
      speed.y *= -1;
  }

  Vector2 position;
  Vector2 speed;
  Color color;
};

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int 屏幕宽 = 800;
  const int 屏幕高 = 450;

  R窗口 窗口(屏幕宽, 屏幕高, "raylib [textures] example - bunnymark");

  // Load bunny texture
  R纹理2D texBunny("resources/wabbit_alpha.png");

  std::list<兔子> bunnies;

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!窗口.是已关闭()) { // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    if (R鼠标::是否正在按下(MOUSE_LEFT_BUTTON)) {
      // Create more bunnies
      for (int i = 0; i < 100; i++) {
        bunnies.emplace_back();
      }
    }

    // Update bunnies

    for (兔子 &bunny : bunnies) {
      bunny.更新(texBunny);
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
      窗口.清屏(RAYWHITE);

      for (兔子 &bunny : bunnies) {
        // NOTE: When internal batch buffer limit is reached
        // (MAX_BATCH_ELEMENTS), a draw call is launched and buffer starts being
        // filled again; before issuing a draw call, updated vertex data from
        // internal CPU buffer is send to GPU... Process of sending data is
        // costly and it could happen that GPU data has not been completely
        // processed for drawing while new data is tried to be sent (updating
        // current in-use buffers) it could generates a stall and consequently a
        // frame drop, limiting the number of drawn bunnies
        texBunny.绘制(bunny.position, bunny.color);
      }

      DrawRectangle(0, 0, 屏幕宽, 40, BLACK);
      raylib::绘制文本(TextFormat("bunnies: %i", bunnies.size()), 120, 10, 20,
                       GREEN);
      raylib::绘制文本(TextFormat("batched draw calls: %i",
                                  1 + bunnies.size() / MAX_BATCH_ELEMENTS),
                       320, 10, 20, MAROON);

      窗口.绘制FPS(10, 10);
    }

    //----------------------------------------------------------------------------------
  }

  return 0;
}
