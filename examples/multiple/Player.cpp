#include "Player.hpp"
#include "raylib-cpp.hpp"

Player::Player() {
    位置 = Rectangle{GetScreenWidth() / 2.0f - 50, GetScreenHeight() / 2.0f - 50, 100, 100};
    速度 = 3;
}

void Player::绘制() {
    位置.绘制(RED);
}

void Player::更新() {
    if (R键盘::是此键为按下(KEY_UP)) {
        位置.y -= (float)速度;
    }
    if (R键盘::是此键为按下(KEY_DOWN)) {
        位置.y += (float)速度;
    }
    if (R键盘::是此键为按下(KEY_RIGHT)) {
        位置.x += (float)速度;
    }
    if (R键盘::是此键为按下(KEY_LEFT)) {
        位置.x -= (float)速度;
    }
}
