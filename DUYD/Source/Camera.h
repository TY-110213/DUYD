#pragma once

class Camera {
public:
    static float x;
    static float y;

    static void Update(float targetX, float targetY);
    static float GetOffsetX();
    static float GetOffsetY();
};