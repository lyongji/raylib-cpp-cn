/*******************************************************************************************
 *
 *   raylib [shaders] example - basic lighting
 *
 *   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
 *         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
 *
 *   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
 *
 *   Example originally created with raylib 3.0, last time updated with raylib 4.2
 *
 *   Example contributed by Chris Camacho (@codifies) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2019-2024 Chris Camacho (@codifies) and Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#include <array>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int 屏幕宽 = 800;
    const int 屏幕高 = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(屏幕宽, 屏幕高, "raylib [shaders] example - basic lighting");

    // Define the camera to look into our 3d world
    R相机 相机;
    相机.position = Vector3{2.0f, 4.0f, 6.0f}; // Camera position
    相机.target = Vector3{0.0f, 0.5f, 0.0f}; // Camera looking at point
    相机.up = Vector3{0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    相机.fovy = 45.0f; // Camera field-of-view Y
    相机.projection = CAMERA_PERSPECTIVE; // Camera projection type

    // Load basic lighting shader
    R着色器 着色器(
        TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get some required shader locations
    着色器.locs[SHADER_LOC_VECTOR_VIEW] = 着色器.取位置("viewPos");
    // NOTE: "matModel" location name is automatically assigned on shader loading,
    // no need to get the location again if using that uniform name
    // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

    // Ambient light level (some basic lighting)
    int ambientLoc = 着色器.取位置("ambient");
    std::array<float, 4> ambientValues = {0.1f, 0.1f, 0.1f, 1.0f};
    着色器.设变量(ambientLoc, ambientValues.data(), SHADER_UNIFORM_VEC4);

    // Create lights
    std::array<Light, MAX_LIGHTS> lights = {
        CreateLight(LIGHT_POINT, {-2, 1, -2}, Vector3Zero(), YELLOW, 着色器),
        CreateLight(LIGHT_POINT, {2, 1, 2}, Vector3Zero(), RED, 着色器),
        CreateLight(LIGHT_POINT, {-2, 1, 2}, Vector3Zero(), GREEN, 着色器),
        CreateLight(LIGHT_POINT, {2, 1, -2}, Vector3Zero(), BLUE, 着色器),
    };

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        相机.更新(CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        std::array<float, 3> cameraPos = {相机.position.x, 相机.position.y, 相机.position.z};
        SetShaderValue(着色器, 着色器.locs[SHADER_LOC_VECTOR_VIEW], cameraPos.data(), SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) {
            lights[0].enabled = !lights[0].enabled;
        }
        if (IsKeyPressed(KEY_R)) {
            lights[1].enabled = !lights[1].enabled;
        }
        if (IsKeyPressed(KEY_G)) {
            lights[2].enabled = !lights[2].enabled;
        }
        if (IsKeyPressed(KEY_B)) {
            lights[3].enabled = !lights[3].enabled;
        }

        // Update light values (actually, only enable/disable them)
        for (const auto& light : lights) UpdateLightValues(着色器, light);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(相机);

        BeginShaderMode(着色器);

        DrawPlane(Vector3Zero(), {10.0, 10.0}, WHITE);
        DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);

        EndShaderMode();

        // Draw spheres to show where the lights are
        for (const auto& light : lights) {
            if (light.enabled)
                DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
            else
                DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(light.color, 0.3f));
        }

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadShader(shader);   // Unload shader

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
