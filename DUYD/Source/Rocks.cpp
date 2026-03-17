#include "Rocks.h"
#include <random>

Rocks::Rocks(int x, int y, int size)
{
    hImage[0] = LoadGraph("data/map/stone.png");
    hImage[1] = LoadGraph("data/sample/kyouka.png");
    hImage[2] = LoadGraph("data/sample/sanso.png");
    num = Random(0, 9);
    if (num == 9) {
        num = Random(0, 1);
    }
    y1 = y;
    x1 = x;
    size1 = size;
}

Rocks::~Rocks()
{
}

void Rocks::Update() {
}

void Rocks::Draw() {
    int screenX = x1 - (int)Camera::GetOffsetX();
    int screenY = y1 - (int)Camera::GetOffsetY();

    switch (num) {
    case 0:
        DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[1], 0);
        break;
    case 1:
        DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[2], 0);
        break;
    default:
        DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
        break;
    }
}

int Rocks::Random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}