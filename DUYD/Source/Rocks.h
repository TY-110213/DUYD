#pragma once
#include "../Library/GameObject.h"
#include "Camera.h"

class Rocks : public GameObject {
public:
    Rocks(int x, int y, int size);
    ~Rocks();
    void Update() override;
    void Draw()   override;

    int GetX() const { return x1; }
    int GetY() const { return y1; }

private:
    int x1 = 0;
    int y1 = 0;
    int size1 = 0;
    int hImage[3];
    int num = 0;
    int Random(int min, int max);
};