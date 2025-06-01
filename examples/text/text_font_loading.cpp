/*******************************************************************************************
 *
 *   raylib [text] example - Font loading
 *
 *   raylib can load fonts from multiple file formats:
 *
 *     - TTF/OTF > Sprite font atlas is generated on loading, user can configure
 *                 some of the generation parameters (size, characters to
 *include)
 *     - BMFonts > Angel code font fileformat, sprite font image must be
 *provided together with the .fnt file, font generation cna not be configured
 *     - XNA Spritefont > Sprite font image, following XNA Spritefont
 *conventions, Characters in image must follow some spacing and order rules
 *
 *   This example has been created using raylib 2.6 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2016-2019 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
#include "raylib-cpp.hpp"
#include <string>

int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int 屏幕宽 = 800;
  const int 屏幕高 = 450;

  R窗口 窗口(屏幕宽, 屏幕高, "raylib [text] example - font loading");

  // Define characters to draw
  // NOTE: raylib supports UTF-8 encoding, following list is actually codified
  // as UTF8 internally
  std::string msg =
      "!\"#$%&'()*+,-./"
      "0123456789:;<=>?@ABCDEFGHI\nJKLMNOPQRSTUVWXYZ[]^_`"
      "abcdefghijklmn\nopqrstuvwxyz{|}~"
      "¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ\nÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷\nøùúûüýþÿ的";

  // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL
  // context is required)

  // BMFont (AngelCode) : Font data and image atlas have been generated using
  // external program
  R字体 fontBm("resources/pixantiqua.fnt");

  // TTF font : 字体 data and atlas are generated directly from TTF
  // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
  R字体 fontTtf("resources/pixantiqua.ttf", 32, nullptr, 250);

  bool useTtf = false;

  窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!窗口.是已关闭()) { // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    if (IsKeyDown(KEY_SPACE))
      useTtf = true;
    else
      useTtf = false;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
      窗口.清屏(RAYWHITE);

      raylib::绘制文本("Hold SPACE to use TTF generated font", 20, 20, 20,
                       LIGHTGRAY);

      if (!useTtf) {
        fontBm.绘制文本(msg, Vector2{20.0f, 100.0f}, fontBm.取字符基本大小(), 2,
                        MAROON);
        raylib::绘制文本("Using BMFont (Angelcode) imported", 20,
                         GetScreenHeight() - 30, 20, GRAY);
      } else {
        fontTtf.绘制文本(msg, Vector2{20.0f, 100.0f}, fontTtf.取字符基本大小(),
                         2, LIME);
        raylib::绘制文本("Using TTF font generated", 20, GetScreenHeight() - 30,
                         20, GRAY);
      }
    }

    //----------------------------------------------------------------------------------
  }

  return 0;
}
