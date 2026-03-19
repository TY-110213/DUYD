#include "Rocks.h"
#include <random>
#include "Game.h"

Rocks::Rocks(int x, int y, int size, int area)
{
    hImage[0] = LoadGraph("data/map/stone.png");
    hImage[1] = LoadGraph("data/map/oxygen_ore.png");
    hImage[2] = LoadGraph("data/map/reinforced_ore.png");
    hImage[3] = LoadGraph("data/map/stone_1.png");
    hImage[4] = LoadGraph("data/map/oxygen_ore_1.png");
    hImage[5] = LoadGraph("data/map/reinforced_ore_1.png");
    hImage[6] = LoadGraph("data/map/stone_2.png");
    hImage[7] = LoadGraph("data/map/oxygen_ore_2.png");
    hImage[8] = LoadGraph("data/map/reinforced_ore_2.png");
    hImage[9] = LoadGraph("data/map/stone_3.png");
    hImage[10] = LoadGraph("data/map/oxygen_ore_3.png");
    hImage[11] = LoadGraph("data/map/reinforced_ore_3.png");
    num = Random(0, 9);
    if (num == 9) {
        num = Random(0, 1);
    }
    y1 = y;
    x1 = x;
    size1 = size;
    area1 = area;
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
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[1], 0);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 0);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[7], 0);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[10], 0);
        }
        break;
    case 1:
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[2], 0);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[5], 0);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[8], 0);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[11], 0);
        }
        break;
    default:
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[3], 0);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 0);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[9], 0);
        }
        break;
    }
}

int Rocks::Random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}