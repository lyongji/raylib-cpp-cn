/*******************************************************************************************
 *
 *   raylib [core] example - Windows drop files
 *
 *   This example only works on platforms that support drag & drop (Windows,
 *Linux, OSX, Html5?)
 *
 *   This example has been created using raylib-cpp (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2020 Rob Loach (@RobLoach)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

int main() {
  // Initialization
  int 屏幕宽 = 800;
  int 屏幕高 = 450;
  R颜色 文本颜色 = R颜色::浅灰();

  R窗口 窗口(屏幕宽, 屏幕高, "raylib [core] example - drop files",
             FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);

  std::vector<std::string> 拖放文件;

  窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!窗口.是已关闭()) { // Detect window close button or ESC key
    // Update
    //----------------------------------------------------------------------------------
    if (IsFileDropped()) {
      拖放文件 = raylib::加载拖放文件列表();
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    while (窗口.绘制中()) {
      窗口.清屏(RAYWHITE);
      // Check if there are files to process.
      if (拖放文件.empty()) {
        raylib::绘制文本("Drop your files to this window!", 100, 40, 20,
                         文本颜色.透明度(0.5));
      } else {
        raylib::绘制文本("Dropped files:", 100, 40, 20, 文本颜色.透明度(0.3));

        // Iterate through all the dropped files.
        for (int i = 0; i < (int)拖放文件.size(); i++) {
          if (i % 2 == 0) {
            文本颜色.绘制矩形(0, 85 + 40 * i, 屏幕宽, 40);
          } else {
            文本颜色.绘制矩形(0, 85 + 40 * i, 屏幕宽, 40);
          }
          // Display the path to the dropped file.

          raylib::绘制文本(拖放文件[i].c_str(), 120, 100 + 40 * i, 10,
                           R颜色::灰());
        }
        raylib::绘制文本("Drop new files...", 100,
                         110 + 40 * (int)拖放文件.size(), 20, R颜色::深灰());
      }
    }

    //----------------------------------------------------------------------------------
  }

  return 0;
}
