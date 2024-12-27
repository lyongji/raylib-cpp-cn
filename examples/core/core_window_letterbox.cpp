/*******************************************************************************************
 *
 *   raylib [core] example - window scale letterbox (and virtual mouse)
 *
 *   Example originally created with raylib 2.5, last time updated with raylib 4.0
 *
 *   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2019-2023 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib-cpp.hpp"

#include "raymath.hpp" // Required for: Vector2Clamp()

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    const int ���ڿ� = 800;
    const int ���ڸ� = 450;

    // Enable config flags for resizable window and vertical synchro
    R���� ����(
        ���ڿ�,
        ���ڸ�,
        "raylib [core] example - window scale letterbox",
        FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    ����.����С�ߴ�(320, 240);

    int ��Ϸ��Ļ�� = 640;
    int ��Ϸ��Ļ�� = 480;

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    R��Ⱦ����2D ��ȾĿ��(��Ϸ��Ļ��, ��Ϸ��Ļ��);
    ��ȾĿ��.ȡ����().���������(TEXTURE_FILTER_BILINEAR); // Texture scale filter to use

    R��ɫ ��ɫ��[10];
    for (int i = 0; i < 10; i++) {
        ��ɫ��[i] = {
            (unsigned char)GetRandomValue(100, 250),
            (unsigned char)GetRandomValue(50, 150),
            (unsigned char)GetRandomValue(10, 100),
            255};
    }

    ����.��Ŀ��FPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!����.���ѹر�()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Compute required framebuffer scaling
        float �ߴ� = MIN((float)GetScreenWidth() / ��Ϸ��Ļ��, (float)GetScreenHeight() / ��Ϸ��Ļ��);

        if (R����::�Ǵ˼�Ϊ����(KEY_SPACE)) {
            // Recalculate random colors for the bars
            for (int i = 0; i < 10; i++) {
                ��ɫ��[i] = {
                    (unsigned char)GetRandomValue(100, 250),
                    (unsigned char)GetRandomValue(50, 150),
                    (unsigned char)GetRandomValue(10, 100),
                    255};
            }
        }

        // Update virtual mouse (clamped mouse value behind game screen)
        raylib::Vector2 ��� = R���::ȡλ��();
        raylib::Vector2 �������(
            (���.x - (GetScreenWidth() - (��Ϸ��Ļ�� * �ߴ�)) * 0.5f) / �ߴ�,
            (���.y - (GetScreenHeight() - (��Ϸ��Ļ�� * �ߴ�)) * 0.5f) / �ߴ�);
        ������� = �������.����(raylib::Vector2::����(), raylib::Vector2(��Ϸ��Ļ��, ��Ϸ��Ļ��));

        // Apply the same transformation as the virtual mouse to the real mouse (i.e. to work with raygui)
        // SetMouseOffset(-(GetScreenWidth() - (gameScreenWidth*scale))*0.5f, -(GetScreenHeight() -
        // (gameScreenHeight*scale))*0.5f);
        //SetMouseScale(1/scale, 1/scale);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        ��ȾĿ��.��ʼ();
        ����.����(RAYWHITE); // Clear render texture background color

        for (int i = 0; i < 10; i++) DrawRectangle(0, (��Ϸ��Ļ�� / 10) * i, ��Ϸ��Ļ��, ��Ϸ��Ļ�� / 10, ��ɫ��[i]);

        raylib::�����ı�(
            "If executed inside a window,\nyou can resize the window,\nand see the screen scaling!",
            10,
            25,
            20,
            WHITE);
        raylib::�����ı�(TextFormat("Default Mouse: [%i , %i]", (int)���.x, (int)���.y), 350, 25, 20, GREEN);
        raylib::�����ı�(TextFormat("Virtual Mouse: [%i , %i]", (int)�������.x, (int)�������.y), 350, 55, 20, YELLOW);
        ��ȾĿ��.����();

        ����.��ʼ����();
        ����.����(BLACK); // Clear screen background

        // Draw render texture to screen, properly scaled
        ��ȾĿ��.ȡ����().����(
            R����(0.0f, 0.0f, ��ȾĿ��.texture.width, -��ȾĿ��.texture.height),
            R����(
                (GetScreenWidth() - (��Ϸ��Ļ�� * �ߴ�)) * 0.5f,
                (GetScreenHeight() - (��Ϸ��Ļ�� * �ߴ�)) * 0.5f,
                ��Ϸ��Ļ�� * �ߴ�,
                ��Ϸ��Ļ�� * �ߴ�),
            RVector2::����(),
            0.0f,
            WHITE);
        ����.��������();
        //--------------------------------------------------------------------------------------
    }
    
    return 0;
}