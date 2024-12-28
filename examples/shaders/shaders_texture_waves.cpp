/*******************************************************************************************
 *
 *   raylib [shaders] example - Texture Waves
 *
 *   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
 *         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
 *
 *   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
 *         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
 *         raylib comes with shaders ready for both versions, check raylib/shaders install folder
 *
 *   This example has been created using raylib 2.5 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Copyright (c) 2019 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    R窗口 窗口(屏幕宽, 屏幕高, "raylib-cpp [shaders] example - texture waves");

    // Load texture texture to apply shaders
    R纹理2D 纹理("resources/space.png");

    // Load shader and setup location points and values
    R着色器 着色器(0, TextFormat("resources/shaders/glsl%i/wave.fs", GLSL_VERSION));

    int secondsLoc = 着色器.取位置("secondes");
    int freqXLoc = 着色器.取位置("freqX");
    int freqYLoc = 着色器.取位置("freqY");
    int ampXLoc = 着色器.取位置("ampX");
    int ampYLoc = 着色器.取位置("ampY");
    int speedXLoc = 着色器.取位置("speedX");
    int speedYLoc = 着色器.取位置("speedY");

    // Shader uniform values that can be updated at any time
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = {(float)窗口.取宽度(), (float)窗口.取高度()};
    着色器.设变量(着色器.取位置("size"), &screenSize, SHADER_UNIFORM_VEC2);
    着色器.设变量(freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    着色器.设变量(freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    着色器.设变量(ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    着色器.设变量(ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    着色器.设变量(speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    着色器.设变量(speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    float seconds = 0.0f;

    窗口.设目标FPS(60); // Set our game to run at 60 frames-per-second
    // -------------------------------------------------------------------------------------------------------------

    // Main game loop
    while (!窗口.是已关闭()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        seconds += GetFrameTime();

        着色器.设变量(secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        着色器.开始();

        纹理.绘制(0, 0, WHITE);
        纹理.绘制(纹理.取宽(), 0, WHITE);

        EndShaderMode();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
