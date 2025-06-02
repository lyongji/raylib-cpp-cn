/*******************************************************************************************
 *
 *   raylib [shapes] example - collision area
 *
 *   This example has been created using raylib 2.5 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2013-2019 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#include <cmath> // NOLINT

int main() {
  // Initialization
  //---------------------------------------------------------
  const int 屏幕宽 = 800;
  const int 屏幕高 = 450;

  R窗口 窗口(屏幕宽, 屏幕高, "raylib [shapes] example - collision area");

  // Box A: Moving box
  R矩形 盒子A(10, GetScreenHeight() / 2 - 50, 200, 100);
  int 盒子A速度X = 4;

  // Box B: Mouse moved box
  R矩形 盒子B(GetScreenWidth() / 2 - 30, GetScreenHeight() / 2 - 30, 60, 60);

  R矩形 盒子碰撞(0); // Collision rectangle

  int 场景上界 = 40; // Top menu limits

  bool 暂停 = false; // Movement pause
  bool 碰撞 = false; // Collision detection

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------

  // Main game loop
  while (!窗口.检查是否已关闭()) { // Detect window close button or ESC key
    // Update
    //-----------------------------------------------------
    // Move box if not paused
    if (!暂停)
      盒子A.x += 盒子A速度X;

    // Bounce box on x screen limits
    if (((盒子A.x + 盒子A.width) >= GetScreenWidth()) || (盒子A.x <= 0))
      盒子A速度X *= -1;

    // Update player-controlled-box (box02)
    盒子B.x = GetMouseX() - 盒子B.width / 2;
    盒子B.y = GetMouseY() - 盒子B.height / 2;

    // Make sure Box B does not go out of move area limits
    if ((盒子B.x + 盒子B.width) >= GetScreenWidth())
      盒子B.x = GetScreenWidth() - 盒子B.width;
    else if (盒子B.x <= 0)
      盒子B.x = 0;

    if ((盒子B.y + 盒子B.height) >= GetScreenHeight())
      盒子B.y = GetScreenHeight() - 盒子B.height;
    else if (盒子B.y <= 场景上界)
      盒子B.y = 场景上界;

    // Check boxes collision
    碰撞 = 盒子A.检查碰撞(盒子B);

    // Get collision rectangle (only on collision)
    if (碰撞)
      盒子碰撞 = 盒子A.取碰撞区域(盒子B);

    // Pause Box A movement
    if (IsKeyPressed(KEY_SPACE))
      暂停 = !暂停;
    //-----------------------------------------------------

    // Draw
    //-----------------------------------------------------
    BeginDrawing();

    窗口.清屏(RAYWHITE);

    DrawRectangle(0, 0, 屏幕宽, 场景上界, 碰撞 ? RED : BLACK);

    盒子A.绘制(GOLD);
    盒子B.绘制(BLUE);

    if (碰撞) {
      // Draw collision area
      盒子碰撞.绘制(LIME);

      // Draw collision message
      raylib::绘制文本("COLLISION!",
                       GetScreenWidth() / 2 - MeasureText("COLLISION!", 20) / 2,
                       场景上界 / 2 - 10, 20, BLACK);

      // Draw collision area
      raylib::绘制文本(TextFormat("Collision Area: %i",
                                  (int)盒子碰撞.width * (int)盒子碰撞.height),
                       GetScreenWidth() / 2 - 100, 场景上界 + 10, 20, BLACK);
    }

    DrawFPS(10, 10);

    EndDrawing();
    //-----------------------------------------------------
  }

  return 0;
}
