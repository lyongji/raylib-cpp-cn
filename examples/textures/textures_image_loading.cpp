/*******************************************************************************************
*
*   raylib [textures] example - Image loading and texture creation
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib/raylib.hpp"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window w(screenWidth, screenHeight, "raylib [textures] example - image loading");
    raylib::Texture texture("resources/raylib_logo.png");
    raylib::Color background(RAYWHITE);
    raylib::Color textColor(LIGHTGRAY);

    // Main game loop
    while (!w.ShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            background.ClearBackground();

            texture.Draw(screenWidth / 2 - texture.getWidth() / 2, screenHeight / 2 - texture.getHeight() / 2);

            textColor.DrawText("this IS a texture loaded from an image!", 300, 370, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
