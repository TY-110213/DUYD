#include "Camera.h"
#include "DxLib.h"

float Camera::x = 0.0f;
float Camera::y = 0.0f;

void Camera::Update(float targetX, float targetY) {
    int screenW, screenH;
    GetScreenState(&screenW, &screenH, nullptr);

    x = targetX - screenW / 2.0f;
    y = targetY - screenH / 2.0f;
}

float Camera::GetOffsetX() {
    return x;
}

float Camera::GetOffsetY() {
    return y;
}