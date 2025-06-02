/*******************************************************************************************
 *
 *   raylib [audio] example - Sound loading and playing
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2014 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int 屏幕宽 = 800;
  const int 屏幕高 = 450;

  R窗口 窗口(屏幕宽, 屏幕高,
             "raylib [audio] example - sound loading and playing");

  R音频设备 音频驱动; // Initialize audio device
  R文本 文本;
  R音效 fxWav("resources/sound.wav");  // Load WAV audio file
  R音效 fxOgg("resources/target.ogg"); // Load OGG audio file

  窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!窗口.检查是否已关闭()) { // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    if (R键盘::是否正在按下(KEY_SPACE))
      fxWav.开始播放(); // Play WAV sound
    if (R键盘::是否正在按下(KEY_ENTER))
      fxOgg.开始播放(); // Play OGG sound
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
      窗口.清屏(RAYWHITE);

      文本.绘制("Press SPACE to PLAY the WAV sound!", 200, 180, 20,
                R颜色::浅灰());
      文本.绘制("Press ENTER to PLAY the OGG sound!", 200, 220, 20,
                R颜色::浅灰());
    }

    //----------------------------------------------------------------------------------
  }

  return 0;
}
